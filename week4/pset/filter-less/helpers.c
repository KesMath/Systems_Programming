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

BYTE return_smaller_value(double a, BYTE b){
    if(a > b){
        return b;
    }
    return (BYTE) a;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            double sephiaRed   = round((.393 * image[i][j].rgbtRed) + (.769 * image[i][j].rgbtGreen) + (.189 * image[i][j].rgbtBlue));
            double sephiaGreen = round((.349 * image[i][j].rgbtRed) + (.686 * image[i][j].rgbtGreen) + (.168 * image[i][j].rgbtBlue));
            double sephiaBlue  = round((.272 * image[i][j].rgbtRed) + (.534 * image[i][j].rgbtGreen) + (.131 * image[i][j].rgbtBlue));

            image[i][j].rgbtRed   = return_smaller_value(sephiaRed, MAX_8_BIT_VALUE);
            image[i][j].rgbtGreen = return_smaller_value(sephiaGreen, MAX_8_BIT_VALUE);
            image[i][j].rgbtBlue  = return_smaller_value(sephiaBlue, MAX_8_BIT_VALUE);              
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

// helper functions that checks if unit movement in all directions is valid
bool left_pixel_exists(int height, int width){
    if(width - 1 < 0){
        return false;
    }
    return true;
}

bool right_pixel_exists(int height, int width){
    if(width + 1 == width){
        return false;
    }
    return true;

}

bool above_pixel_exists(int height, int width){
    if(height - 1 < 0){
        return false;
    }
    return true;
}


bool below_pixel_exists(int height, int width){
    if(height + 1 == height){
        return false;
    }
    return true;
}

bool bottom_right_pixel_exists(int height, int width){
    if(height + 1 == height && width + 1 == width){
        return false;
    } 
    return true; 
}

bool bottom_left_pixel_exists(int height, int width){
    if(height + 1 == height && width - 1 < 0){
        return false;
    } 
    return true;
}

bool upper_left_pixel_exists(int height, int width){
    if(height - 1 < 0 && width - 1 < 0){
        return false;
    } 
    return true;
}

bool upper_right_pixel_exists(int height, int width){
    if(height - 1 < 0 && width + 1 == width){
        return false;
    } 
    return true;
}


// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //TODO: blurring algorithm must work on the ORIGINAL values of the image ... this current implementation will take averages on mutated values!!
    // operate on a copy and mutate the original!
     
    double red = 0;
    double green = 0;
    double blue = 0;
    int valid_pixel_cout = 1;
    
    
    //RGBTRIPLE copyImage[height][width] = *image;

    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            if(left_pixel_exists(height, width)){
                red += image[i][j - 1].rgbtRed;
                blue += image[i][j - 1].rgbtBlue;
                green += image[i][j - 1].rgbtGreen;
                valid_pixel_cout++;
            }

            if(right_pixel_exists(height, width)){
                red += image[i][j + 1].rgbtRed;
                blue += image[i][j + 1].rgbtBlue;
                green += image[i][j + 1].rgbtGreen;
                valid_pixel_cout++;
            }

            if(above_pixel_exists(height, width)){
                red += image[i - 1][j].rgbtRed;
                blue += image[i - 1][j].rgbtBlue;
                green += image[i - 1][j].rgbtGreen;
                valid_pixel_cout++;
            }

            if(below_pixel_exists(height, width)){
                red += image[i + 1][j].rgbtRed;
                blue += image[i + 1][j].rgbtBlue;
                green += image[i + 1][j].rgbtGreen;
                valid_pixel_cout++;
            }

            if(bottom_right_pixel_exists(height, width)){
                red += image[i + 1][j + 1].rgbtRed;
                blue += image[i + 1][j + 1].rgbtBlue;
                green += image[i + 1][j + 1].rgbtGreen;
                valid_pixel_cout++;
            }

            if(bottom_left_pixel_exists(height, width)){
                red += image[i + 1][j - 1].rgbtRed;
                blue += image[i + 1][j - 1].rgbtBlue;
                green += image[i + 1][j - 1].rgbtGreen;
                valid_pixel_cout++;
            }

            if(upper_left_pixel_exists(height, width)){
                red += image[i - 1][j - 1].rgbtRed;
                blue += image[i - 1][j - 1].rgbtBlue;
                green += image[i - 1][j - 1].rgbtGreen;
                valid_pixel_cout++;
            }

            if(upper_right_pixel_exists(height, width)){
                red += image[i - 1][j + 1].rgbtRed;
                blue += image[i - 1][j + 1].rgbtBlue;
                green += image[i - 1][j + 1].rgbtGreen;
                valid_pixel_cout++;
            }

            // including current pixel in average too!
            red += image[i][j].rgbtRed;
            blue += image[i][j].rgbtBlue;
            green += image[i][j].rgbtGreen;

            image[i][j].rgbtRed = (BYTE) round(red / valid_pixel_cout);
            image[i][j].rgbtBlue = (BYTE) round(blue / valid_pixel_cout);
            image[i][j].rgbtGreen = (BYTE) round(green / valid_pixel_cout);

            //resetting values for next pixel
            red = 0;
            blue = 0;
            green = 0;
            valid_pixel_cout = 1;
        }
    }

    return;
}
