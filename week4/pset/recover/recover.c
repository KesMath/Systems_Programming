#include <stdio.h>
#include <stdlib.h>
 
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

}