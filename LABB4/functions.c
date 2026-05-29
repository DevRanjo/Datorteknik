#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

//_______________________________________The task 1:_______________________________________________________
/*uses a character array of size b = 16 bytes to implement a read buffer.
• If the buffer is empty, the function buf_in should read in b byte from the file and put
them in the buffer.
• Every time this function is called, this function should return the next byte of the file.
• Your function should take care the end of the file (and return EOF if we reach the end
of the file)
Test your function.
In short, once we have opened the file in binary mode, we can just have a loop to read all
the file, byte per byte, until we reach EOF*/

#define byte_size 64

int buf_in(int fd, char arr[]){  //read_bytes amount of bytes to read
    static int byte_amount = 0;   //static to not reset each function call
    static int position = 0;
    
    //read each char until we reach a current empty buffer
    if(position >= byte_amount){  
        byte_amount = read(fd, arr, byte_size); //read 16 bytes
        //int byte_amount = byte amount refilled in buffer

        position = 0; //reset position to not increase forever

        if(byte_amount == 0){ //if bytes not read -> end of file reached
            return EOF;
        }
    }
    return arr[position++]; //return current read char
}

void check_until_eof(int fd, char arr[]){
    char c;
   
    while((c = buf_in(fd, arr)) != EOF){
       //read one byte at a time until end of file reached 
        printf("%c", c);
    }

    printf("\n");
    return;
}

//________________________________________Task 2:______________________________________________
/*In this taks we will, in a similar way as the previous task, write a function doing buffered
writes to a file. Do not use any C functions from the standard library having a buffer in
your code! You need to write two functions:
    • buf_out In a similar way as buf_in, this function has a buffer of size b = 16. This
    function take a byte as parameter and put in the buffer. 
    If the buffer is full, the
    contents of the buffer are writing to the file before putting the byte given as parameter
    into the buffer.

    • buf_flush This function, with no parameter, is just writing the content of the buffer
    to the file.*/


static int position = 0;

int buf_out(int fd2, char arr[], char input){ 

    arr[position++] = input; 

    if(position >= byte_size){ //if buffer is full aka 16 bytes or more then write
        int written_bytes = write(fd2, arr, byte_size);    
        position = 0; //reset position in arr

        if(written_bytes == 0){ //if 0 no bytes written
            return 0;
        }
        if(written_bytes == -1){ //if -1 error occured
            return -1; 
        }
 
    }
    return 1;
}

static char arr[byte_size]; //byte_size = 16
static int fd2; 

int buf_flush(){ //writes immediate current buffer result if buffer is not empty
    
    if(position > 0){
        int bytes_written = write(fd2, arr, position);
        position = 0;
        if(bytes_written == -1){
            printf("[FAIL]  flush failed\n");
            return -1;
        }
    }
    return 1;
}

void example_filled_buffer_output(){
    //Only writes out each time when each 16 bytes get filled in the arr
    buf_out(fd2, arr, 'H');
    buf_out(fd2, arr, 'E');
    buf_out(fd2, arr, 'L');
    buf_out(fd2, arr, 'L');
    buf_out(fd2, arr, 'O');
    buf_out(fd2, arr, 'H');
    buf_out(fd2, arr, 'E');
    buf_out(fd2, arr, 'L');
    buf_out(fd2, arr, 'L');
    buf_out(fd2, arr, 'O');
    buf_out(fd2, arr, 'H');
    buf_out(fd2, arr, 'E');
    buf_out(fd2, arr, 'L');
    buf_out(fd2, arr, 'L');
    buf_out(fd2, arr, 'O');
    buf_out(fd2, arr, '6');
    return;
}

void example_not_filled_buffer_output(){   
    //This part doesn't get printed out since buffer is reset and not full
    buf_out(fd2, arr, 'N');
    buf_out(fd2, arr, 'O');
    buf_out(fd2, arr, 'T');
    buf_out(fd2, arr, 'S');
    buf_out(fd2, arr, 'E');
    buf_out(fd2, arr, 'E');
    buf_out(fd2, arr, 'N');
    return;
}

/*___________________________________________TASK 3__________________________________________________________
Write a C main program which uses your buffered input/output functions for copying a file.
The filenames (source and destination) should be provided as the command line arguments
    • Use the command diff to ensure the copy is the same file as the source one
    • Use the C timing API to measure the time for reading and the time for writing (and
    show the average per byte
    • Compares times you got with your C functions and with a non-buffered version of your
    function.
    • Make a comparison with files of different sizes, and use buffer of size 16, 32 and 64
*/

//calculates average seconds per byte
double calculate_time(clock_t start, clock_t end, int total_byte_amount_file){
    double time_diff = (double) (end - start) / CLOCKS_PER_SEC;

    if(total_byte_amount_file <= 0){
        printf("[FAIL]  total amount of bytes invalid\n");
        return -1.0;
    }
    time_diff = time_diff / (double) total_byte_amount_file;
    return time_diff; 
}

double throughput(clock_t start, clock_t end, int total_bytes){
    double throughput = (double) (end - start) / CLOCKS_PER_SEC;
    if(throughput <= 0){
        printf("[FAIL]  total amount of bytes invalid\n");
        return -1.0;
    }
    throughput = (double) (total_bytes) / (1000000.0*throughput); //Mbps (Mega bytes per second)
    return throughput;
}

double calculate_latency(clock_t start, clock_t end, int bits){
    double latency = (double) ((end - start)*100000000.0) /CLOCKS_PER_SEC; //nanoseconds
    if(bits <= 0){
        printf("[FAIL] total amount of bytes invalid\n");
        return -1.0;
    }
    latency =  latency / (double) bits; //nanoseconds per bit
    return latency;
}

void calc_results(clock_t start, clock_t end, int total_bytes){
    double t = throughput(start, end, total_bytes);
    printf("Throughput: %lf Mbps\n", t);
    double l = calculate_latency(start, end, total_bytes*8); //calculate average nanoseconds per bit (8bits=1byte)
    printf("Latency: %lf nanoseconds per bit\n\n", l);
    return; 
}


int read_non_buf(int fd){  //read_bytes amount of bytes to read
    unsigned char c;

    int byte_amount = read(fd, &c, 1); //read 1 char at a time

    if(byte_amount == 0){ //if bytes not read -> end of file reached
        return EOF;
    }
    else if(byte_amount < 0){
        return EOF;
    }

    return c; //return current read char
}

int write_non_buf(int fd2, char input){
     
    int written_bytes = write(fd2, &input, 1);    //write one char at a time

    if(written_bytes == 0){
        return 0;       //no bytes written
    }
    else if(written_bytes < 0){
        return -1;      //error
    }
    else{
        return 1;
    }
}

void copy_file(){

    /*___________________________________BUFFERED READ___________________________________________________*/
    clock_t start, end;
    int source = open("source.txt", O_RDONLY);
    if(source == -1){
        perror("[FAIL]  Source file open failure\n");
        exit(1);
    }
    
    //read process calculation - buffered version
    int c;
    int total_byte_amount_file = 0;
    int total_bytes = 0;
    int count;

    total_byte_amount_file = 0;
    
    start = clock();
    for(int i=0; i<100; i++){           //rewrite from the same file 100 times
        total_byte_amount_file = 0;
        while((c = buf_in(source, arr)) != EOF){
            total_byte_amount_file++;
            total_bytes++;
        };
        lseek(source, 0, SEEK_SET); // like rewind but syscall SEEK_SET <- to begininning of file 
    }
    end = clock();
    
    printf("Buffered read results:\n");
    calc_results(start, end, total_bytes); //throughput and latency

    if(lseek(source, 0, SEEK_SET)==-1){
        perror("lseek");
        return;
    } // lseek is a system call that is used to change the location of the read/write pointer of a file descriptor.

    if(close(source) == -1){
        perror("Close source failed\n");
        exit(1);
    }
    /*____________________________________Non buffered read__________________________________________________*/

    int source2 = open("source.txt", O_RDONLY);
    if(source2 == -1){
        perror("[FAIL]  Source file open failure\n");
        exit(1);
    }

    int read_bytes = 0;

    start = clock();

    for(int i=0; i<100; i++){               //read file 100 times
        while((c = read_non_buf(source2)) != EOF){
            read_bytes++;
        };
        lseek(source2, 0, SEEK_SET); 
    }
    end = clock();

    assert(total_bytes == read_bytes); //both reads (buff and non buff) total byte amounts should be same
    
    printf("Non buffered read:\n");
    calc_results(start, end, read_bytes); 
    
    /*______________________________________Buffered write___________________________________________________*/
    
    int destination = open("destination.txt", O_WRONLY | O_CREAT);
    if(destination == -1){
        perror("[FAIL]  Destination file failes to create/open/write\n");
        exit(1);
    }
    

    //calculate the write process - buffered version
    int check_eof;
    total_bytes = 0;
    int check_total_bytes_file = 0;

    //read file
    FILE* read_source = fopen("source.txt", "r");
    if(read_source == NULL){
        perror("[FAIL]  fopen failed\n");
        exit(1);
    }
   
    start = clock();
    int i;
    for(i = 0; i < 100; i++){   //read from file 100 times to write of 100 times
        check_total_bytes_file = 0;
        while((c = fgetc(read_source)) != EOF){

            check_eof = buf_out(destination, arr, c);
            if(check_eof == -1){
                printf("[FAIL] read buff error occured\n");
                break; 
            }
            if(check_eof == 0){
                printf("[PASS] eof write reached\n");
                break; 
            }
            total_bytes++;
            check_total_bytes_file++;
        }
        rewind(read_source);    //realign ptr to start of file again
    }

    fd2 = destination; //global variable 
    buf_flush();
    end = clock(); 
   

    assert(check_total_bytes_file == total_byte_amount_file);
    //both source and destination should have same byte file size

    assert(total_bytes > total_byte_amount_file); //all bytes read should be greater than all bytes in one file
    assert(total_bytes != 0);
    assert(total_byte_amount_file != 0);
    
    printf("Buffered write:\n");
    calc_results(start, end, total_bytes);

    /*_______________________________Non buffered write____________________________________________________*/

    
    rewind(read_source);
    start = clock();

    for(i = 0; i < 100; i++){
        while((c = fgetc(read_source)) != EOF){

            check_eof = write_non_buf(destination, c);
            if(check_eof == -1){
                printf("[FAIL] read buff error occured\n");
                break; 
            }
            if(check_eof == 0){
                printf("[PASS] eof write reached\n");
                break; 
            }
            
        }
        rewind(read_source);    //realign ptr to start of file again
    }
    end = clock();

    printf("Non buffered write:\n");
    calc_results(start, end, total_bytes); 

    /*____________________________________End________________________________________________*/
    fclose(read_source);
    /*if(close(source) == -1){
        perror("Close source failed\n");
        exit(1);
    }*/
    if(close(source2) == -1){
        perror("Close source failed\n");
        exit(1);
    }
    if(close(destination) == -1){
        perror("Close destination failed\n");
        exit(1);
    }
    return; 
}



int main(){
    
    /*______________________________________TASK 1___________________________________________________*/
    
    //open file with (I/O) system call open()

    int fd = open("exampletext.txt", O_RDONLY); //file descriptor - read only 
    if(fd == -1){ //fd returns as -1 upon failure 
        perror("File open failure\n");
        exit(1);
    }

    printf("Task 1:\n");
    //calls buf_in the while loop in function below repeatedly
    check_until_eof(fd, arr);
    printf("\n");


    /*______________________________TASK 2_______________________________________________________________*/
<<<<<<< HEAD

    printf("Task 2\n");
    fd2 = open("writeInFile.txt", O_WRONLY | O_CREAT); //file descriptor - write or create only 
=======
    
    fd2 = open("writeInFile.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644); //file descriptor - write or create only 
>>>>>>> f90642000face3bff181b2d819cb005bf697a1fd
    if(fd2 == -1){ //fd returns as -1 upon failure 
        perror("File 2 creation or open failure\n");
        exit(1);
    }

    //writing out 16 bytes worth of char in file (gives HELLOHELLOHELLO6)
    example_filled_buffer_output();

    //not filled buffer -> not writing out anything in file -> only stored in buffer
    example_not_filled_buffer_output();

    //prints out current buffer (above) even though its not filled (in file gives: NOTSEEN)
    buf_flush(); 
    printf("success\n\n");

    /*________________________________TASK 3_____________________________________________________________*/
    printf("Task 3:\n\n");
    copy_file();

    /*____________________________________________________________________________________________________*/

    //close system call 
    if(close(fd) == -1){
        perror("Close fd failed\n");
        exit(1);
    }
    /*if(close(fd2) == -1){
        perror("Close fd2 failed\n");
        exit(1);
    }*/
    printf("\nEnd of program\n");
    return 0; 
}