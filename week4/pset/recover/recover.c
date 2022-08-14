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
    char *filename = malloc(sizeof(char) * 8);
    // need to capture and save first photo as 0th one!
    int jpeg_cout = -1;

    // read in 512 bytes at a time until memory card returns 0 bytes
    while(fread(buffer, 1, BLOCK_SIZE, memory_card_file) == BLOCK_SIZE){
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
            // Recall that JPEGs are stored back to back in memory card which implies
            // that we keep on appending those 512 bytes to a new file until first 4 bytes of a new 512 block contains JPEG sig! 
            fread(buffer, BLOCK_SIZE, 1, memory_card_file);
            while(buffer[0] != 0xff && buffer[1] != 0xd8 && buffer[2] != 0xff && 
                !(buffer[3] == 0xe0 || buffer[3] == 0xe1 || buffer[3] == 0xe2 || buffer[3] == 0xe3 ||
                  buffer[3] == 0xe4 || buffer[3] == 0xe5 || buffer[3] == 0xe6 || buffer[3] == 0xe7 ||
                  buffer[3] == 0xe8 || buffer[3] == 0xe9 || buffer[3] == 0xea || buffer[3] == 0xeb ||
                  buffer[3] == 0xec || buffer[3] == 0xed || buffer[3] == 0xee || buffer[3] == 0xef)){
                fwrite(buffer, BLOCK_SIZE, 1, newFile);
                //read in 512 bytes of memory_card into buffer again to keep buffer refreshed
                fread(buffer, BLOCK_SIZE, 1, memory_card_file);
            }
            // getting to this line means a new jpeg signature was found ... hence we close out file and jump back to outer loop conditional
            fclose(newFile);

            // rewind file pointer back 512 bytes so first "IF" condition above can be satisfied
            // if don't rewind, while condition above will essentially read in new 512 bytes into buffer,
            // essentially skipping the buffer with the JPEG header, thereby affecting file integrity!
            // hence we need to retard the file pointer for the sake of loop continuity

            // Reference of negative offsets to move file pointer backwards
            // https://www.oreilly.com/library/view/c-in-a/0596006977/re96.html
            fseek(memory_card_file, (-1) * BLOCK_SIZE, SEEK_CUR);
        }
    }
    
    fclose(memory_card_file);
    free(buffer);
    free(filename);

}