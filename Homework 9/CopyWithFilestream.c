//use filestream to make a copy of a text file
#include <stdio.h>
#include <stdlib.h>

int getFileSize(char * filePath);

int main() {
    char * path = "genesis.txt";
    char * newpath = "genesis_copy.txt";
    FILE * inputStream = fopen(path, "r"); 
    FILE * outputStream = fopen(newpath, "w");

    int fileSize = getFileSize(path);
    printf("the input file is %d bytes in size.", fileSize);
    
    char * buf = malloc(fileSize);

    if( fread(buf, 1, fileSize, inputStream) > 0) {
        fwrite(buf, 1, fileSize, outputStream);
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