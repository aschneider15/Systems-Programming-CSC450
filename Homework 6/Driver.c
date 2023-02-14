/*
Programmer: Aidan Schneider
Client: Prof. Yiming Liao - Systems Programming CSC450
Requirements:
Use the system call introduced in textbook Chapter 2 File I/O, create a program in C

    read all characters in genesis.txt
    count how many characters are there in the genesis.txt
    generate a copy of genesis.txt, and write to a new file named genesis_copy.txt

Submit a screenshot of the number of characters as the output and use ls (in Linux) or dir (in Windows) command to list out all the files after you compile and execute your code.
Deadline: Wendesday Feb 15, 2023
*/
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
//first, some set-up is required:

    char * originalFilepath = "genesis.txt";
    char * newFilepath = "genesis_copy.txt"; //create filepath for copy of genesis

    char * buffer;
    char * tempbuffer[1000];
    //buffers for reading in
    //bigger buffers mean faster performance, but more memory used

    int fd; //file descriptor
    fd = open(originalFilepath, O_RDONLY);
    //fd now contains the descriptor of genesis.txt
    
//now to figure out the size of the original file (in bytes):

    int size = 0; //size of file (will be updated)
    int readRet;//a place to put our read-in data

    while ((readRet = read(fd, tempbuffer, 1000)) > 0){
            size = size + readRet;
        }
    printf("There are %d bytes in genesis.txt", size);

//knowing the size of the original file, we can read the whole thing

    buffer = (char *)malloc(size); //allocate memory for the final buffer

    lseek(fd, 0, SEEK_SET); //gets us back to beginning of file
    readRet = read(fd, buffer, size); //puts the contents of "genesis.txt" into readRet again
    if (readRet <= 0){//if there is nothing to read, something has gone wrong
        perror("Read Error");
    }
    readRet = close(fd);//close the file

//write all the bytes we've read to the new file

    fd = creat(newFilepath, 0644);//create the new file
    int writeRet;//place to put the written bytes
    if ((writeRet = write(fd, buffer, size)) < 0){ //if nothing to write, throw error
        perror("Write error.");
    }

    close(fd);
    free(buffer);
    
    return 0;
}
//(read)->data will be in the buffer
//open() sample.txt
//read()
//char [] as buffer
//length of the the buffer
//count until read return 0
//close() sample.txt

//create a new file
//open mode set to create, previllege to 0644

//write to the new file
//write buffer into the new file
//close()