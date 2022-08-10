#include "helpers.h"
#include <math.h>
#include <stdbool.h>

const int MAX_8_BIT_VALUE = 255;
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            //take average of all 3 colors to get the intensity of gray for that pixel and set all pixels to that average
            double grayscale_intensity = round(image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed / 3);
            image[i][j].rgbtBlue  = (BYTE) grayscale_intensity;
            image[i][j].rgbtGreen = (BYTE) grayscale_intensity;
            image[i][j].rgbtRed   = (BYTE) grayscale_intensity;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            double sephiaRed   = round((.393 * image[i][j].rgbtRed) + (.769 * image[i][j].rgbtGreen) + (.189 * image[i][j].rgbtBlue));
            double sephiaGreen = round((.349 * image[i][j].rgbtRed) + (.686 * image[i][j].rgbtGreen) + (.168 * image[i][j].rgbtBlue));
            double sephiaBlue  = round((.272 * image[i][j].rgbtRed) + (.534 * image[i][j].rgbtGreen) + (.131 * image[i][j].rgbtBlue));

            if(sephiaRed > MAX_8_BIT_VALUE){
                sephiaRed = MAX_8_BIT_VALUE;
            }
            if(sephiaGreen > MAX_8_BIT_VALUE){
                sephiaGreen = MAX_8_BIT_VALUE;
            }
            if(sephiaBlue > MAX_8_BIT_VALUE){
                sephiaBlue = MAX_8_BIT_VALUE;
            }

            image[i][j].rgbtRed   = (BYTE) sephiaRed;
            image[i][j].rgbtGreen = (BYTE) sephiaGreen;
            image[i][j].rgbtBlue  = (BYTE) sephiaBlue;               
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int midpoint = (int) floor(width / 2);
    for(int i = 0; i < height; i++){
        for(int j = 0, k = width - 1; j < midpoint; j++, k--){
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][k];
            image[i][k] = temp;             
        }
    }
    return;
}


bool left_pixel_exists(int height, int width){
    if(width - 1 < 0){
        return false;
    }
    return true;
}

bool right_pixel_exists(int height, int width){

}

bool above_pixel_exists(int height, int width){

}


bool below_pixel_exists(int height, int width){

}

bool bottom_right_pixel_exists(int height, int width){

}

bool bottom_left_pixel_exists(int height, int width){

}

bool upper_left_pixel_exists(int height, int width){

}

bool upper_right_pixel_exists(int height, int width){

}


// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){

        }
    }
    return;
    return;
}
