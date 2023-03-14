#include <stdlib.h>
#include <stdio.h>
#include <string.h>

unsigned int bitsToInt(char * bits);
void rotate(char * path, char * newPath, int mode);

int main(){
    rotate("vader.bmp", "vader_rot_0.bmp", 0);
    rotate("vader.bmp", "vader_rot_90.bmp", 1);
    rotate("vader.bmp", "vader_rot_180.bmp", 2);
    rotate("vader.bmp", "vader_rot_270.bmp", 3);
    rotate("vader.bmp", "anakin.bmp", 4);
    return 0;
}

void rotate(char * path, char * newPath, int mode){
    char error;
    FILE * inputStream, * outputStream;
    inputStream = fopen(path, "rb");
    outputStream = fopen(newPath, "wb");

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
/*
    if(mode == 1 || mode == 3) {
        for(int i = 0; i < 4; i++) {
            writeBuffer[widthPos + i] = readBuffer[heightPos + i];
            writeBuffer[heightPos + i] = readBuffer[widthPos + i];
        }
    }
*/
    for(unsigned int y = 0; y < height; y++) {
        for(unsigned int x = 0; x < width; x++) {
            int oldPixel = y * width + x;
            int newPixel;
            switch(mode) {
                case 0: //0 degree rot
                    newPixel = y * width + x;
                    break;
                case 1: //90 degree rot
                    newPixel = x * width + y;
                    break;
                case 2: //180 degree rot
                    newPixel = (width * height) - ((width * y) + x);
                    break;
                case 3: //270 degree rot
                    error = 1;
                    break;
                default:
                    error = 2; //printf("Error: Invalid Mode\n");
                    break;
            }
            //mirrored: int newPixel = y * width + (width - x - 1);
            //90 degree rotation: int newPixel = x * width + y;
            //180 degree rotation: int newPixel = (width * height) - ((width * y) + x);
            //int newPixel = (width * height) - ();
            for(int i = 0; i < 3; i++) {
                int oldIndex, newIndex;
                oldIndex = 54 + oldPixel * 3 + i;
                newIndex = 54 + newPixel * 3 + i;
                writeBuffer[newIndex] = readBuffer[oldIndex];
            }
        }
    }

    switch(error) {
            case 1:
                printf("ERROR: 270 degree rotation has not been implemented yet.\n");
                break;
            case 2:
                printf("ERROR: invalid mode.");
                break;
            default:
                break;
        }

    fwrite(writeBuffer, size, 1, outputStream);

    fclose(inputStream);
    fclose(outputStream);
    free(readBuffer);
    free(writeBuffer);
}

unsigned int bitsToInt(char * bits){ //argument is 8 bit * 4 array
    //bits = char[4]{'A', 'B', 'C', 'D'};
    return (unsigned char)bits[0] | ((unsigned char)bits[1] << 8) | ((unsigned char)bits[2] << 16) | ((unsigned char)bits[3] << 24);
}