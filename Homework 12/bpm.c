#include <stdlib.h>
#include <stdio.h>

unsigned int bitsToInt(char * bits);

int main(){
    FILE * inputStream, * outputStream;
    inputStream = fopen("vader.bmp", "rb");
    outputStream = fopen("vader_mirrored.bmp", "wb");

    char intBuf[4];
    char pixBuf[3];

    //read the width, height and size from header
    //note that the header is the first 54 bytes of the file
    int sizePos, heightPos, widthPos, bppPos, bitmapPos;
    sizePos = 2;
    heightPos = 22;
    widthPos = 18;
    bppPos = 0x001C;
    bitmapPos = 55;
    unsigned int size, height, width, bpp;

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

    fseek(inputStream, bppPos, SEEK_SET);
    fread(intBuf, 4, 1, inputStream);
    bpp = bitsToInt(intBuf);


    printf("File size is %d bits\n", size);
    printf("File width is %d px\n", width);
    printf("File height is %d px\n", height);
    printf("There are %d bits per pixel\n", bpp);

    char row[width * 3];
    int heightOffset = 0;
    fseek(outputStream, bitmapPos, SEEK_SET);
    int pixelcounter = 0;

    while(heightOffset < height){
        for(int i = (width*3) - 3; i > 0; i--) {
                fseek(inputStream, bitmapPos + i + (3*width*heightOffset), SEEK_SET);
                fread(pixBuf, sizeof(char) * 3, 1, inputStream);
                
                for(int i = 0; i < 3; i++) {
                    row[pixelcounter] = pixBuf[0+i];
                    pixelcounter++;
                }
                //printf("I read one line!\n");
            }
        fwrite(row, 3, width, outputStream);//writes entire row to output stream
        heightOffset++;
        printf("===columns finished: %n===\n", heightOffset);
    }
    
    /*
    Create an int array of size[width]
    Read each pixel into the width array until end of array is met
    
    do the same thing, except write each pixel to the new file (row by row) 
        starting from the back and working your way toward [0].

    */
    fclose(inputStream);
    fclose(outputStream);
    return 0;
}


unsigned int bitsToInt(char * bits){ //argument is 8 bit * 4 array
    //bits = char[4]{'A', 'B', 'C', 'D'};
    return (unsigned char)bits[0] | ((unsigned char)bits[1] << 8) | ((unsigned char)bits[2] << 16) | ((unsigned char)bits[3] << 24);
}