#include "helpers.h"
#include <math.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for(int indexHeight = 0; indexHeight < height; indexHeight++) {

        for(int indexWidth = 0; indexWidth < width; indexWidth++) {

            int average = roundf((image[indexHeight][indexWidth].rgbtRed + image[indexHeight][indexWidth].rgbtGreen + image[indexHeight][indexWidth].rgbtBlue) / 3.0);

            image[indexHeight][indexWidth].rgbtRed = average;
            image[indexHeight][indexWidth].rgbtGreen = average;
            image[indexHeight][indexWidth].rgbtBlue = average;
        }
    }

    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for(int indexHeight = 0; indexHeight < height; indexHeight++) {

        for(int indexWidth = 0; indexWidth < width; indexWidth++) {

            int sepiaRed = (int) (image[indexHeight][indexWidth].rgbtRed * 0.393 + image[indexHeight][indexWidth].rgbtGreen * 0.769 + image[indexHeight][indexWidth].rgbtBlue * 0.189);
            if (sepiaRed > 255){
                sepiaRed = 255;
            }

            int sepiaGreen = (int) (image[indexHeight][indexWidth].rgbtRed * 0.349 + image[indexHeight][indexWidth].rgbtGreen * 0.686 + image[indexHeight][indexWidth].rgbtBlue * 0.168);
            if (sepiaGreen > 255){
                sepiaGreen = 255;
            }

            int sepiaBlue = (int) (image[indexHeight][indexWidth].rgbtRed * 0.272 + image[indexHeight][indexWidth].rgbtGreen * 0.534 + image[indexHeight][indexWidth].rgbtBlue * 0.131);
            if (sepiaBlue > 255){
                sepiaBlue = 255;
            }

            image[indexHeight][indexWidth].rgbtRed = sepiaGreen;
            image[indexHeight][indexWidth].rgbtGreen = sepiaGreen;
            image[indexHeight][indexWidth].rgbtBlue = sepiaBlue;
        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for(int indexHeight = 0; indexHeight < height; indexHeight++) {

        for(int indexWidth = 0; indexWidth < width / 2; indexWidth++) {

            RGBTRIPLE temporary = image[indexHeight][indexWidth];
            RGBTRIPLE temporaryBackwards = image[indexHeight][width - indexWidth - 1];

            image[indexHeight][width - indexWidth - 1] = temporary;
            image[indexHeight][indexWidth] = temporaryBackwards;
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];

    for(int indexHeight = 0; indexHeight < height; indexHeight++) {

        for(int indexWidth = 0; indexWidth < width; indexWidth++) {

            copy[indexHeight][indexWidth] = image[indexHeight][indexWidth];
        }
    }

    for(int indexHeight = 0; indexHeight < height; indexHeight++) {

        for(int indexWidth = 0; indexWidth < width; indexWidth++) {
            
            RGBTRIPLE topLeftPixel = copy[indexHeight - 1][indexWidth - 1];
            RGBTRIPLE topMidPixel = copy[indexHeight - 1][indexWidth];
            RGBTRIPLE topRightPixel = copy[indexHeight - 1][indexWidth + 1];

            RGBTRIPLE middleLeftPixel = copy[indexHeight][indexWidth - 1];
            RGBTRIPLE middleMidPixel = copy[indexHeight][indexWidth];
            RGBTRIPLE middleRightPixel = copy[indexHeight][indexWidth + 1];

            RGBTRIPLE bottomLeftPixel = copy[indexHeight + 1][indexWidth - 1];
            RGBTRIPLE bottomMidPixel = copy[indexHeight + 1][indexWidth];
            RGBTRIPLE bottomRightPixel = copy[indexHeight + 1][indexWidth + 1];

            int blurredRed = (topLeftPixel.rgbtRed + topMidPixel.rgbtRed + topRightPixel.rgbtRed + middleLeftPixel.rgbtRed + middleMidPixel.rgbtRed + middleRightPixel.rgbtRed + bottomLeftPixel.rgbtRed + bottomMidPixel.rgbtRed + bottomRightPixel.rgbtRed) / 9;
            int blurredGreen = (topLeftPixel.rgbtGreen + topMidPixel.rgbtGreen + topRightPixel.rgbtGreen + middleLeftPixel.rgbtGreen + middleMidPixel.rgbtGreen + middleRightPixel.rgbtGreen + bottomLeftPixel.rgbtGreen + bottomMidPixel.rgbtGreen + bottomRightPixel.rgbtGreen) / 9;
            int blurredBlue = (topLeftPixel.rgbtBlue + topMidPixel.rgbtBlue + topRightPixel.rgbtBlue + middleLeftPixel.rgbtBlue + middleMidPixel.rgbtBlue + middleRightPixel.rgbtBlue + bottomLeftPixel.rgbtBlue + bottomMidPixel.rgbtBlue + bottomRightPixel.rgbtBlue) / 9;

            image[indexHeight][indexWidth].rgbtRed = blurredRed;
            image[indexHeight][indexWidth].rgbtGreen = blurredGreen;
            image[indexHeight][indexWidth].rgbtBlue = blurredBlue;
            
        }
    }

    return;
}
