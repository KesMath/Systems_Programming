#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

const int BLOCK_SIZE = 512;
typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    if(argc != 2){
        printf("Usage: ./recover IMAGE\n");
        return 1;   
    }

    FILE *file = fopen(argv[1], "r");

    if(file == NULL){
        printf("Unable to open file. Exiting...\n");
        return 1;
    }

    // create an array buffer (optionally on the heap) 512 in length, each of 1 byte
    // the multiplier is not needed but it helps to show that each index of this buffer is one byte/ 8 bits long
    BYTE *buffer = malloc(sizeof(BYTE) * BLOCK_SIZE);

    //read in 512 bytes at a time until memory card returns 0 bytes
    while(fread(buffer, BLOCK_SIZE, 1, file) != 0){
        
    }
    
    // check JPEG byte signature of 0xff 0xd8 0xff 0xe0 -> 0xef

    // if chunk or block is jpeg signature, write that to a new file and keep on writing those bytes
    // until another 512 byte block containing 4 byte JPEG signature appears... then you will close out that file
    // and write to a new jpeg file until another signature is detected
    free(buffer);

}