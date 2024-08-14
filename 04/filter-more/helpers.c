#include "helpers.h"
#include <math.h>
#include <stdbool.h>

void createCopy(int height, int width, RGBTRIPLE copy[height][width], RGBTRIPLE image[height][width]);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for(int indexHeight = 0; indexHeight < height; indexHeight++) {

        for(int indexWidth = 0; indexWidth < width; indexWidth++) {

            int red = image[indexHeight][indexWidth].rgbtRed;
            int green = image[indexHeight][indexWidth].rgbtGreen;
            int blue = image[indexHeight][indexWidth].rgbtBlue;

            int average = roundf((red + green + blue) / 3.0);

            image[indexHeight][indexWidth].rgbtRed = average;
            image[indexHeight][indexWidth].rgbtGreen = average;
            image[indexHeight][indexWidth].rgbtBlue = average;
        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for(int indexHeight = 0; indexHeight < height; indexHeight++) {

        for(int indexWidth = 0; indexWidth < width / 2; indexWidth++) {

            RGBTRIPLE pixelStorage = image[indexHeight][indexWidth];
            RGBTRIPLE pixelStorageBackwards = image[indexHeight][width - indexWidth - 1];

            image[indexHeight][width - indexWidth - 1] = pixelStorage;
            image[indexHeight][indexWidth] = pixelStorageBackwards;
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];

    createCopy(height, width, copy, image);

    for(int indexHeight = 0; indexHeight < height; indexHeight++) {
        for(int indexWidth = 0; indexWidth < width; indexWidth++) {
            int counter = 0;

            RGBTRIPLE topLeftPixel; topLeftPixel.rgbtRed = 0; topLeftPixel.rgbtGreen = 0; topLeftPixel.rgbtBlue = 0;
            bool hasTopLeftPixel = (indexHeight - 1) >= 0 && (indexWidth - 1) >= 0;
            if(hasTopLeftPixel) {
                topLeftPixel = copy[indexHeight - 1][indexWidth - 1];
                counter++;
            } 

            RGBTRIPLE topMidPixel; topMidPixel.rgbtRed = 0; topMidPixel.rgbtGreen = 0; topMidPixel.rgbtBlue = 0;
            bool hasTopMidPixel = (indexHeight - 1) >= 0;
            if(hasTopMidPixel) {
                topMidPixel = copy[indexHeight - 1][indexWidth];
                counter++;
            }

            RGBTRIPLE topRightPixel; topRightPixel.rgbtRed = 0; topRightPixel.rgbtGreen = 0; topRightPixel.rgbtBlue = 0;
            bool hasTopRightPixel = (indexHeight - 1) >= 0 && (indexWidth + 1) < width;
            if(hasTopRightPixel) {
                topRightPixel = copy[indexHeight - 1][indexWidth + 1];
                counter++;
            }

            RGBTRIPLE middleLeftPixel; middleLeftPixel.rgbtRed = 0; middleLeftPixel.rgbtGreen = 0; middleLeftPixel.rgbtBlue = 0;
            bool hasMiddleLeftPixel = (indexWidth - 1) >= 0;
            if(hasMiddleLeftPixel) {
                middleLeftPixel = copy[indexHeight][indexWidth - 1];
                counter++;
            }
            
            RGBTRIPLE middleMidPixel = copy[indexHeight][indexWidth];
            counter++;

            RGBTRIPLE middleRightPixel; middleRightPixel.rgbtRed = 0; middleRightPixel.rgbtGreen = 0; middleRightPixel.rgbtBlue = 0;
            bool hasMiddleRightPixel = (indexWidth + 1) < width;
            if(hasMiddleRightPixel) {
                middleRightPixel = copy[indexHeight][indexWidth + 1];
                counter++;
            }

            RGBTRIPLE bottomLeftPixel; bottomLeftPixel.rgbtRed = 0; bottomLeftPixel.rgbtGreen = 0; bottomLeftPixel.rgbtBlue = 0;
            bool hasBottomLeftPixel = (indexHeight + 1) < height && (indexWidth - 1) >= 0;
            if(hasBottomLeftPixel) {
                bottomLeftPixel = copy[indexHeight + 1][indexWidth - 1];
                counter++;
            }
            
            RGBTRIPLE bottomMidPixel; bottomMidPixel.rgbtRed = 0; bottomMidPixel.rgbtGreen = 0; bottomMidPixel.rgbtBlue = 0;
            bool hasBottomMidPixel = (indexHeight + 1) < height;
            if(hasBottomMidPixel) {
                bottomMidPixel = copy[indexHeight + 1][indexWidth];
                counter++;
            }

            RGBTRIPLE bottomRightPixel; bottomRightPixel.rgbtRed = 0; bottomRightPixel.rgbtGreen = 0; bottomRightPixel.rgbtBlue = 0;
            bool hasBottomRightPixel = (indexHeight + 1) < height && (indexWidth + 1) < width;
            if(hasBottomRightPixel) {
                bottomRightPixel = copy[indexHeight + 1][indexWidth + 1];
                counter++;
            }

            int blurredRed = (topLeftPixel.rgbtRed + topMidPixel.rgbtRed + topRightPixel.rgbtRed + middleLeftPixel.rgbtRed + middleMidPixel.rgbtRed + middleRightPixel.rgbtRed + bottomLeftPixel.rgbtRed + bottomMidPixel.rgbtRed + bottomRightPixel.rgbtRed) / counter;
            int blurredGreen = (topLeftPixel.rgbtGreen + topMidPixel.rgbtGreen + topRightPixel.rgbtGreen + middleLeftPixel.rgbtGreen + middleMidPixel.rgbtGreen + middleRightPixel.rgbtGreen + bottomLeftPixel.rgbtGreen + bottomMidPixel.rgbtGreen + bottomRightPixel.rgbtGreen) / counter;
            int blurredBlue = (topLeftPixel.rgbtBlue + topMidPixel.rgbtBlue + topRightPixel.rgbtBlue + middleLeftPixel.rgbtBlue + middleMidPixel.rgbtBlue + middleRightPixel.rgbtBlue + bottomLeftPixel.rgbtBlue + bottomMidPixel.rgbtBlue + bottomRightPixel.rgbtBlue) / counter;

            image[indexHeight][indexWidth].rgbtRed = blurredRed;
            image[indexHeight][indexWidth].rgbtGreen = blurredGreen;
            image[indexHeight][indexWidth].rgbtBlue = blurredBlue;
            
        }
    }

    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];

    createCopy(height, width, copy, image);

    for(int indexHeight = 0; indexHeight < height; indexHeight++) {

        for(int indexWidth = 0; indexWidth < width; indexWidth++) {

            
            RGBTRIPLE topLeftPixel; topLeftPixel.rgbtRed = 0; topLeftPixel.rgbtGreen = 0; topLeftPixel.rgbtBlue = 0;
            bool hasTopLeftPixel = (indexHeight - 1) >= 0 && (indexWidth - 1) >= 0;
            if(hasTopLeftPixel) {
                topLeftPixel = copy[indexHeight - 1][indexWidth - 1];
            } 

            RGBTRIPLE topMidPixel; topMidPixel.rgbtRed = 0; topMidPixel.rgbtGreen = 0; topMidPixel.rgbtBlue = 0;
            bool hasTopMidPixel = (indexHeight - 1) >= 0;
            if(hasTopMidPixel) {
                topMidPixel = copy[indexHeight - 1][indexWidth];
            }

            RGBTRIPLE topRightPixel; topRightPixel.rgbtRed = 0; topRightPixel.rgbtGreen = 0; topRightPixel.rgbtBlue = 0;
            bool hasTopRightPixel = (indexHeight - 1) >= 0 && (indexWidth + 1) < width;
            if(hasTopRightPixel) {
                topRightPixel = copy[indexHeight - 1][indexWidth + 1];
            }

            RGBTRIPLE middleLeftPixel; middleLeftPixel.rgbtRed = 0; middleLeftPixel.rgbtGreen = 0; middleLeftPixel.rgbtBlue = 0;
            bool hasMiddleLeftPixel = (indexWidth - 1) >= 0;
            if(hasMiddleLeftPixel) {
                middleLeftPixel = copy[indexHeight][indexWidth - 1];
            }
            
            RGBTRIPLE middleMidPixel = copy[indexHeight][indexWidth];

            RGBTRIPLE middleRightPixel; middleRightPixel.rgbtRed = 0; middleRightPixel.rgbtGreen = 0; middleRightPixel.rgbtBlue = 0;
            bool hasMiddleRightPixel = (indexWidth + 1) < width;
            if(hasMiddleRightPixel) {
                middleRightPixel = copy[indexHeight][indexWidth + 1];
            }

            RGBTRIPLE bottomLeftPixel; bottomLeftPixel.rgbtRed = 0; bottomLeftPixel.rgbtGreen = 0; bottomLeftPixel.rgbtBlue = 0;
            bool hasBottomLeftPixel = (indexHeight + 1) < height && (indexWidth - 1) >= 0;
            if(hasBottomLeftPixel) {
                bottomLeftPixel = copy[indexHeight + 1][indexWidth - 1];
            }
            
            RGBTRIPLE bottomMidPixel; bottomMidPixel.rgbtRed = 0; bottomMidPixel.rgbtGreen = 0; bottomMidPixel.rgbtBlue = 0;
            bool hasBottomMidPixel = (indexHeight + 1) < height;
            if(hasBottomMidPixel) {
                bottomMidPixel = copy[indexHeight + 1][indexWidth];
            }

            RGBTRIPLE bottomRightPixel; bottomRightPixel.rgbtRed = 0; bottomRightPixel.rgbtGreen = 0; bottomRightPixel.rgbtBlue = 0;
            bool hasBottomRightPixel = (indexHeight + 1) < height && (indexWidth + 1) < width;
            if(hasBottomRightPixel) {
                bottomRightPixel = copy[indexHeight + 1][indexWidth + 1];
            }

            // ROT

            int redGx = topLeftPixel.rgbtRed * (-1) + middleLeftPixel.rgbtRed * (-2) + bottomLeftPixel.rgbtRed * (-1) + topRightPixel.rgbtRed + middleRightPixel.rgbtRed *(2) + bottomRightPixel.rgbtRed;
            int redGy = topLeftPixel.rgbtRed * (-1) + topMidPixel.rgbtRed * (-2) + topRightPixel.rgbtRed * (-1) + bottomLeftPixel.rgbtRed + bottomMidPixel.rgbtRed * (2) + bottomRightPixel.rgbtRed;
            int redEdge = round(sqrt(pow(redGx, 2) + pow(redGy, 2)));

            if (redEdge > 255) redEdge = 255;
            else if (redEdge < 0) redEdge = 0;

            image[indexHeight][indexWidth].rgbtRed = redEdge;

            // GRÜN

            int greenGx = topLeftPixel.rgbtGreen * (-1) + middleLeftPixel.rgbtGreen * (-2) + bottomLeftPixel.rgbtGreen * (-1) + topRightPixel.rgbtGreen + middleRightPixel.rgbtGreen *(2) + bottomRightPixel.rgbtGreen;
            int greenGy = topLeftPixel.rgbtGreen * (-1) + topMidPixel.rgbtGreen * (-2) + topRightPixel.rgbtGreen * (-1) + bottomLeftPixel.rgbtGreen + bottomMidPixel.rgbtGreen * (2) + bottomRightPixel.rgbtGreen;
            int greenEdge = round(sqrt(pow(greenGx, 2) + pow(greenGy, 2)));

            if (greenEdge > 255) greenEdge = 255;
            else if (greenEdge < 0) greenEdge = 0;

            image[indexHeight][indexWidth].rgbtGreen = greenEdge;

            // BLAU

            int blueGx = topLeftPixel.rgbtBlue * (-1) + middleLeftPixel.rgbtBlue * (-2) + bottomLeftPixel.rgbtBlue * (-1) + topRightPixel.rgbtBlue + middleRightPixel.rgbtBlue *(2) + bottomRightPixel.rgbtBlue;
            int blueGy = topLeftPixel.rgbtBlue * (-1) + topMidPixel.rgbtBlue * (-2) + topRightPixel.rgbtBlue * (-1) + bottomLeftPixel.rgbtBlue + bottomMidPixel.rgbtBlue * (2) + bottomRightPixel.rgbtBlue;
            int blueEdge = round(sqrt(pow(blueGx, 2) + pow(blueGy, 2)));

            if (blueEdge > 255) blueEdge = 255;
            else if (blueEdge < 0) blueEdge = 0;

            image[indexHeight][indexWidth].rgbtBlue = blueEdge;
        }
    }

    return;
}

void createCopy(int height, int width, RGBTRIPLE copy[height][width], RGBTRIPLE image[height][width]) {
    for(int indexHeight = 0; indexHeight < height; indexHeight++) {
        for(int indexWidth = 0; indexWidth < width; indexWidth++) {
            copy[indexHeight][indexWidth] = image[indexHeight][indexWidth];
        }
    }

    return;
}
