#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

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

#define byte_size 16

int buf_in(int fd, char arr[]){  //read_bytes amount of bytes to read
    static int byte_amount = 0;   //static to not reset each function call
    static int position = 0;
    
    //read each char until we reach a current empty buffer
    if(position >= byte_amount){  
        byte_amount = read(fd, arr, byte_size); //read 16 bytes
        //int byte_amount = byte amount refilled in buffer

        position = 0; //reset position to not increase forever

        if(byte_amount == 0){ //if bytes not read -> end of file reached
            printf("EOF\n");
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
void buf_out(int fd2, char arr[], char input){ 

    arr[position++] = input; 

    if(position >= byte_size){ //if buffer is full aka 16 bytes or more then write
        write(fd2, arr, byte_size);    
        position = 0; //reset position in arr
    }
    return;
}

static char arr[byte_size]; //byte_size = 16
static int fd2; 

void buf_flush(){ //writes immediate current buffer result if buffer is not empty
    
    if(position > 0){
        write(fd2, arr, position);
        position = 0;
    }
    return;
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

    /*______________________________TASK 2_______________________________________________________________*/
    
    fd2 = open("writeInFile.txt", O_WRONLY | O_CREAT); //file descriptor - write or create only 
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


    //close system call 
    if(close(fd) == -1){
        perror("Close failed\n");
        exit(1);
    }
    if(close(fd2) == -1){
        perror("Close failed\n");
        exit(1);
    }

    return 0; 
}