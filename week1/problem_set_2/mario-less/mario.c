#include <cs50.h>
#include <stdio.h>

void print_right_aligned_pyramid_ascii_art(char, int);

int main(void) 
{
    int height;
    do{
        height = get_int("Height: ");
    }
    while(height < 1 || height > 8);
    print_right_aligned_pyramid_ascii_art('#', height);
}

void print_right_aligned_pyramid_ascii_art(char ch, int height){
   // prints char in a right-aligned pyramid formation
   // for example: height = 4 yields:
   //   #
   //  ##
   // ###
   //####
    for(int i = 1; i <= height; i++){
        for(int j = 0; j < i; j++){
            printf("%c", ch);
        }
        printf("\n");
    }
}