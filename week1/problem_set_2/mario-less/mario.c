#include <cs50.h>
#include <stdio.h>

void print_right_aligned_pyramid_ascii_art(char, int);

int main(void) 
{
    int height;
    do{
        int height = get_int("Height: ");
    }
    while(height < 1 && height > 8);
    print_right_aligned_pyramid_ascii_art('#', height);
}

void print_right_aligned_pyramid_ascii_art(char ch, int height){
   // prints char in right-aligned pyramid
   // for example: height = 4 yields:
   //   #
   //  ##
   // ###
   //####
}