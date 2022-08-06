// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    // TODO: Copy header from input file to output file

    // creates array of size 44 on stack ... we can optionally save it on the heap with malloc()
    // what's the benefit of saving it on the heap or stack?
    uint8_t header_buffer[HEADER_SIZE];

    // fread() is gonna move filepointer 8 bits/ 1 byte at a time, 44 times and copy results into header_buffer
    // it returns number of items read ... in this case that's 44 bytes 
    size_t bytes_read = fread(header_buffer, sizeof(uint8_t), HEADER_SIZE, input);

    if(bytes_read != HEADER_SIZE){
        printf("Was not able to read all %i bytes successfully", HEADER_SIZE);
        return 1;
    }
    
    // fwrite() going to ingest that buffer, 8 bits/ 1 byte at a time, and write that to output file, 44 times
    // it returns number of items written ... in this case that's 44 bytes
    size_t bytes_written = fwrite(header_buffer, sizeof(uint8_t), HEADER_SIZE, output);

    if(bytes_written != HEADER_SIZE){
        printf("Was not able to write all %i bytes successfully", HEADER_SIZE);
        return 1;
    }

    // TODO: Read samples from input file and write updated data to output file
    int16_t audio_sample;

    // reading 16 bits / 2 bytes one at a time until fread() returns 0 bytes read meaning end of file!
    while(fread(&audio_sample, sizeof(int16_t), 1, input) == 1){
        audio_sample *= factor;
        fwrite(&audio_sample, sizeof(int16_t), 1, output);
    }

    // Close files
    fclose(input);
    fclose(output);
}