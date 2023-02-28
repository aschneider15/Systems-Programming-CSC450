//use filestream to make a copy of a text file
#include <stdio.h>
#include <stdlib.h>

int getFileSize(char * filePath);

int main() {
    char * path = "genesis.txt";
    char * newpath = "genesis_reversed.txt";
    FILE * inputStream = fopen(path, "r"); 
    FILE * outputStream = fopen(newpath, "w");

    int fileSize = getFileSize(path);
    printf("the input file is %d bytes in size.", fileSize);
    
    char * buf = malloc(fileSize);

    for(int i = 0; i < fileSize; i++) {
        fseek(inputStream, -i -1, SEEK_END);//start at end, decrement for each char
        if( fread(buf, 1, 1, inputStream) > 0) {//read one char at a time
            fseek(outputStream, i, SEEK_SET);//start at beginning, increment for each char
            fwrite(buf, 1, 1, outputStream);//write one char at a time
        }
    }

    fclose(inputStream);
    fclose(outputStream);
    free(buf);

    return 0;
}

int getFileSize(char * filepath) {
    FILE * stream = fopen(filepath, "r");
    fseek(stream, 0, SEEK_END);
    int ret;
    ret = ftell(stream);
    fclose(stream);
    return ret;
}