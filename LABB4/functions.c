#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

//The task:
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
    static int bytes_in_buff = 0;   
    static int position = 0;
    
    //read each char until we reach a current empty buffer
    if(position >= bytes_in_buff){  
        bytes_in_buff = read(fd, arr, byte_size);

        position = 0; //reset position to not increase forever

        if(bytes_in_buff == 0){ //if bytes not read -> end of file reached
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

int main(){
    
    char arr[byte_size]; //byte_size = 16
    
    //open file with (I/O) system call open()
    int fd = open("exampletext.txt", O_RDONLY); //file descriptor - read only 

    if(fd == -1){ //fd returns as -1 upon failure 
        perror("File open failure\n");
        exit(1);
    }

    //calls buf_in the while loop in function below
    check_until_eof(fd, arr);

    //close system call 
    if(close(fd) == -1){
        perror("Close failed\n");
        exit(1);
    }

    return 0; 
}