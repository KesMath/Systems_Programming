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

    FILE *memory_card_file = fopen(argv[1], "r");

    if(memory_card_file == NULL){
        printf("Unable to open file. Exiting...\n");
        return 1;
    }

    // create an array buffer (optionally on the heap) 512 in length, each of 1 byte
    // the multiplier is not needed but it helps to show that each 'index' of this buffer is one byte/ 8 bits long
    BYTE *buffer = malloc(sizeof(BYTE) * BLOCK_SIZE);
    char *filename = "000.jpg";
    // need to capture and save first photo as 0th one!
    int jpeg_cout = -1;

    // read in 512 bytes at a time until memory card returns 0 bytes
    while(fread(buffer, BLOCK_SIZE, 1, memory_card_file) != 0){
        // check first 4 bytes to determine JPEG signature
        if(buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && 
        (buffer[3] == 0xe0 || buffer[3] == 0xe1 || buffer[3] == 0xe2 || buffer[3] == 0xe3 ||
         buffer[3] == 0xe4 || buffer[3] == 0xe5 || buffer[3] == 0xe6 || buffer[3] == 0xe7 ||
         buffer[3] == 0xe8 || buffer[3] == 0xe9 || buffer[3] == 0xea || buffer[3] == 0xeb ||
         buffer[3] == 0xec || buffer[3] == 0xed || buffer[3] == 0xee || buffer[3] == 0xef)){

            // create new file
            jpeg_cout++;
            sprintf(filename, "%03i.jpg", jpeg_cout);
            FILE *newFile = fopen(filename, "w");
            fwrite(buffer, BLOCK_SIZE, 1, newFile);

            // keep writing to that file until another jpeg signature is found!
            // Recall that JPEGs are stored back to back in memory card
            fread(buffer, BLOCK_SIZE, 1, memory_card_file);
            while(buffer[0] != 0xff && buffer[1] != 0xd8 && buffer[2] != 0xff && 
                !(buffer[3] == 0xe0 || buffer[3] == 0xe1 || buffer[3] == 0xe2 || buffer[3] == 0xe3 ||
                  buffer[3] == 0xe4 || buffer[3] == 0xe5 || buffer[3] == 0xe6 || buffer[3] == 0xe7 ||
                  buffer[3] == 0xe8 || buffer[3] == 0xe9 || buffer[3] == 0xea || buffer[3] == 0xeb ||
                  buffer[3] == 0xec || buffer[3] == 0xed || buffer[3] == 0xee || buffer[3] == 0xef)){
                fwrite(buffer, BLOCK_SIZE, 1, newFile);
                //read in 512 bytes of memory into buffer again after writing previous buffer into new file
                fread(buffer, BLOCK_SIZE, 1, memory_card_file);
            }
            // getting to this line means a new jpeg signature was found ... hence we close out file and jump back to outer loop conditional
            fclose(newFile);
        }
    }
    
    fclose(memory_card_file);
    free(buffer);

}