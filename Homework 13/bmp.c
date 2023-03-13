#include <stdlib.h>
#include <stdio.h>

unsigned int bitsToInt(char * bits);

int main(){
    FILE * inputStream, * outputStream;
    inputStream = fopen("vader.bmp", "rb");
    outputStream = fopen("vader_mirrored.bmp", "wb");

    char intBuf[4];

    //read the width, height and size from header;
    int sizePos, heightPos, widthPos;
    sizePos = 2;
    heightPos = 22;
    widthPos = 18;
    unsigned int size, height, width;

    //move the file pointer to the pos
    fseek(inputStream, sizePos, SEEK_SET);
    //read 4 bytes out into buf;
    fread(intBuf, 4, 1, inputStream);
    size = bitsToInt(intBuf);

    fseek(inputStream, heightPos, SEEK_SET);
    fread(intBuf, 4, 1, inputStream);
    height = bitsToInt(intBuf);

    fseek(inputStream, widthPos, SEEK_SET);
    fread(intBuf, 4, 1, inputStream);
    width = bitsToInt(intBuf);

    char * readBuffer;
    char * writeBuffer;
    readBuffer = malloc(size);
    writeBuffer = malloc(size);

    fseek(inputStream, 0, SEEK_SET);
    fread(readBuffer, size, 1, inputStream);

    for(int i = 0; i < 54; i++) {//write the header
        writeBuffer[i] = readBuffer[i];
    }
    for(int y = 0; y < height; y++) {
        for(int x = 0; x < width; x++) {
            int oldPixel = y * width + x;
            //0 degree rotation: int newPixel = y * width + (width - x - 1);
            //180 degree rotation: int newPixel = (width * height) - ((width * y) + x);
            int newPixel = (width * height) - ((width * y) + x);
            for(int i = 0; i < 3; i++) {
                int oldIndex, newIndex;
                oldIndex = 54 + oldPixel * 3 + i;
                newIndex = 54 + newPixel * 3 + i;
                writeBuffer[newIndex] = readBuffer[oldIndex];
            }
        }
    }

    fwrite(writeBuffer, size, 1, outputStream);

    fclose(inputStream);
    fclose(outputStream);
    free(readBuffer);
    free(writeBuffer);

    return 0;
}


unsigned int bitsToInt(char * bits){ //argument is 8 bit * 4 array
    //bits = char[4]{'A', 'B', 'C', 'D'};
    return (unsigned char)bits[0] | ((unsigned char)bits[1] << 8) | ((unsigned char)bits[2] << 16) | ((unsigned char)bits[3] << 24);
}