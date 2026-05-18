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

int buf_in(int fd){  //read_bytes amount of bytes to read

    //static = värdena sparas efter varje funktionsanrop

    static char buffer[16]; // buffer array som 16 bytes sparas i åt gången
    static int pos = 0; // vilken position i buffern vi är just nu
    static int bytes_in_buffer = 0; // hur många bytes som lästes in från filen

    if (pos >= bytes_in_buffer){ // är buffern slut? läs isåfall in 16 nya bytes
        bytes_in_buffer = read(fd, buffer, 16); // läs 16 bytes in i buffern

        if(bytes_in_buffer <= 0){
            return EOF;
        }

        pos = 0;
    }

    return buffer[pos++]; // returnerar nästa byte


}
/* void check_until_eof(int fd, char* arr){
    char* head = arr;
   
    while(arr!= head+16){
        buf_in(fd, arr, 1); //read one byte at a time
        arr += 1;
    }
    
    printf("EOF\n");
    return;
} */

int main(){

    int fd = open("exampletext.txt", O_RDONLY);

    if(fd < 0){
        perror("couldn't open file");
        return 1;
    }

    int c;



    /* loopa igenom filen och hämta ett tecken i taget från bufferten
    skriver sen ut det tills EOF nås */
    while((c=buf_in(fd)) != EOF){
        printf("%c",c);
    }

    close(fd);

    return 0;


/*     char* arr = malloc(16);
    
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
    return 0;  */
}