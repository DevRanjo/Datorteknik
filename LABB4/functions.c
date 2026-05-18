#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

/*uses a character array of size b = 16 bytes to implement a read buffer.
• If the buffer is empty, the function buf_in should read in b byte from the file and put
them in the buffer.
• Every time this function is called, this function should return the next byte of the file.
• Your function should take care the end of the file (and return EOF if we reach the end
of the file)
Test your function.
In short, one we have opened the file in binary mode, we can just have a loop to read all
the file, byte per byte, until we reach EOF*/

void buf_in(int fd, char* arr, int byte_size){ //byte size will be 18
    printf("%c\n", arr+1);
    //read byte 
    //next byte
    if(eof){
        printf("EOF\n");
        return;
    }
    printf("%d")
    return;
}

int main(){
    char* arr = malloc(16);
    
    //exit system call
    if(arr==NULL){
        perror("Allocation failed\n");
        exit(1);
    }

    int fd = open("exampletext.txt", O_RDONLY); //file descriptor - read only 
    read()

    close()

    free(arr);
    return 0; 
}