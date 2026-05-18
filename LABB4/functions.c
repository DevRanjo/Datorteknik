#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

/*uses a character array of size b = 16 bytes to implement a read buffer.
• If the buffer is empty, the function buf_in should read in b byte from the file and put
them in the buffer.
• Every time this function is called, this function should return the next byte of the file.
• Your function should take care the end of the file (and return EOF if we reach the end
of the file)
Test your function.
In short, once we have opened the file in binary mode, we can just have a loop to read all
the file, byte per byte, until we reach EOF*/

void buf_in(int fd, char* arr, int read_bytes){  //read_bytes amount of bytes to read
    int r;

    //read byte 
    r = read(fd, arr, read_bytes);
    
    arr[r] = '\0';
	printf("Those bytes are as follows: %s\n", arr);
    return;
}
void check_until_eof(int fd, char* arr){
    char* head = arr;
   
    while(arr!= head+16){
        buf_in(fd, arr, 1); //read one byte at a time
        arr += 1;
    }
    
    printf("EOF\n");
    return;
}

int main(){
    char* arr = malloc(16);
    
    //exit system call
    if(arr==NULL){
        perror("Allocation failed\n");
        exit(0);
    }

    int fd = open("exampletext.txt", O_RDONLY); //file descriptor - read only 
    if(fd == -1){ //fd returns as -1 upon failure 
        perror("File open failure\n");
        exit(0);
    }
    check_until_eof(fd, arr);

    if(close(fd) == -1){
        perror("Close failed\n");
        exit(0);
    }


    free(arr);
    return 0; 
}