/*
Programmer: Aidan Schneider
Client: Prof. Yiming Liao - Systems Programming CSC450
Requirements:
    Create a program in C, use system calls in chapter 2, split genesis.txt into two files in equal size. 
    First one is named "genesis_part_1.txt", the other one named "genesis_part_2.txt".    
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

    char * tempbuffer[1000];
    //buffers for reading in
    //bigger buffers mean faster performance, but more memory used

    int fd; //file descriptor
    fd = open(originalFilepath, O_RDONLY);
    //fd now contains the descriptor of genesis.txt
    
//now to figure out the size of the original file (in bytes):

    int size = 0; //size of file (will be updated)
    int readRet;//a place to put our read-in data

    while ((readRet = read(fd, tempbuffer, 100)) > 0){
            size = size + readRet;
        }
    printf("There are %d bytes in genesis.txt", size);

//knowing the size of the original file, we can read the whole thing

    int halfSize = size/2;
    char buffer1 [halfSize];//create buffer for first half
    char buffer2 [size - halfSize];//second half
    
    lseek(fd, 0, SEEK_SET); //gets us back to beginning of file
    readRet = read(fd, buffer1, halfSize); //read first half
    if (readRet <= 0){//if there is nothing to read, something has gone wrong
        perror("Read Error");
    }
    readRet = read(fd, buffer2, size - halfSize);
    readRet = close(fd);//close the file

//write all the bytes we've read to the new file

    fd = creat("genesis_copy-1_of_2.txt", 0644);//create frist
    int writeRet;//write first half
    if ((writeRet = write(fd, buffer1, halfSize)) < 0){ //if nothing to write, throw error
        perror("Write error.");
    }

    fd = creat("genesis_copy-2_of_2.txt", 0644); //create second

    if((writeRet = write(fd, buffer2, size - halfSize)) < 0){ //write second half
        perror("Write error.");
    }
    close(fd);
    
    return 0;
}
//create two file, sample_1.txt and sample_2.txt
//sample_1 contains first 1180/2 = 590bytes from sample.txt
//smaple_2 contains second 590 bytes from sample.txt

//the beginning spot of the buffer
//call write() twice, 
//first time write first 590bytes from buffer to sample_1.txt
//second time from second 590 bytes to the new sample_2.txt
//truncate can be used in making the first 590 bytes