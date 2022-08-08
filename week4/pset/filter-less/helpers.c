#include "helpers.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            //take average of all 3 colors to get the intensity of gray for that pixel and set all pixels to that average
            int grayscale_intensity = image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed / 3;
            image[i][j].rgbtBlue = grayscale_intensity;
            image[i][j].rgbtGreen = grayscale_intensity;
            image[i][j].rgbtRed = grayscale_intensity;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}
