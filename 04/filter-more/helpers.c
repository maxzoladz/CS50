#include "helpers.h"
#include <math.h>

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

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
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
