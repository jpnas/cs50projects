#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float value = (image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0;
            value = round(value);
            image[i][j].rgbtRed = value;
            image[i][j].rgbtGreen = value;
            image[i][j].rgbtBlue = value;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float sepiaRed = .393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue;
            float sepiaGreen = .349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue;
            float sepiaBlue = .272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue;
            sepiaRed = round(sepiaRed);
            sepiaGreen = round(sepiaGreen);
            sepiaBlue = round(sepiaBlue);
        
            //Limiting the value to 255
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }
            
            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            //Doing a simple switch between pixels
            int tempRed = image[i][j].rgbtRed;
            int tempGreen = image[i][j].rgbtGreen;
            int tempBlue = image[i][j].rgbtBlue;
            image[i][j].rgbtRed = image[i][width - 1 - j].rgbtRed;
            image[i][j].rgbtGreen = image[i][width - 1 - j].rgbtGreen;
            image[i][j].rgbtBlue = image[i][width - 1 - j].rgbtBlue;
            
            image[i][width - 1 - j].rgbtRed = tempRed;
            image[i][width - 1 - j].rgbtGreen = tempGreen;
            image[i][width - 1 - j].rgbtBlue = tempBlue;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //Creating a duplicate where we will store the blurred pixels
    RGBTRIPLE image0[height][width];
    
    //For the first row
    
    //For the first corner pixel
    float avgRed = (image[0][0].rgbtRed + image[0][1].rgbtRed + image[1][0].rgbtRed + image[1][1].rgbtRed) / 4.0;
    float avgGreen = (image[0][0].rgbtGreen + image[0][1].rgbtGreen + image[1][0].rgbtGreen + image[1][1].rgbtGreen) / 4.0;
    float avgBlue = (image[0][0].rgbtBlue + image[0][1].rgbtBlue + image[1][0].rgbtBlue + image[1][1].rgbtBlue) / 4.0;
    avgRed = round(avgRed);
    avgGreen = round(avgGreen);
    avgBlue = round(avgBlue);
    image0[0][0].rgbtRed = avgRed;
    image0[0][0].rgbtGreen = avgGreen;
    image0[0][0].rgbtBlue = avgBlue;
    
    //For the middle of the first row
    for (int i = 1; i < width - 1; i++)
    {
        avgRed = (image[0][i - 1].rgbtRed + image[0][i].rgbtRed + image[0][i + 1].rgbtRed + image[1][i - 1].rgbtRed + image[1][i].rgbtRed + image[1][i + 1].rgbtRed) / 6.0;
        avgGreen = (image[0][i - 1].rgbtGreen + image[0][i].rgbtGreen + image[0][i + 1].rgbtGreen + image[1][i - 1].rgbtGreen + image[1][i].rgbtGreen + image[1][i + 1].rgbtGreen) / 6.0;
        avgBlue = (image[0][i - 1].rgbtBlue + image[0][i].rgbtBlue + image[0][i + 1].rgbtBlue + image[1][i - 1].rgbtBlue + image[1][i].rgbtBlue + image[1][i + 1].rgbtBlue) / 6.0;
        avgRed = round(avgRed);
        avgGreen = round(avgGreen);
        avgBlue = round(avgBlue);
        image0[0][i].rgbtRed = avgRed;
        image0[0][i].rgbtGreen = avgGreen;
        image0[0][i].rgbtBlue = avgBlue;
    }
    //For the right corner of the first row
    avgRed = (image[0][width - 2].rgbtRed + image[0][width - 1].rgbtRed + image[1][width - 2].rgbtRed + image[1][width - 1].rgbtRed) / 4.0;
    avgGreen = (image[0][width - 2].rgbtGreen + image[0][width - 1].rgbtGreen + image[1][width - 2].rgbtGreen + image[1][width - 1].rgbtGreen) / 4.0;
    avgBlue = (image[0][width - 2].rgbtBlue + image[0][width - 1].rgbtBlue + image[1][width - 2].rgbtBlue + image[1][width - 1].rgbtBlue) / 4.0;
    avgRed = round(avgRed);
    avgGreen = round(avgGreen);
    avgBlue = round(avgBlue);
    image0[0][width - 1].rgbtRed = avgRed;
    image0[0][width - 1].rgbtGreen = avgGreen;
    image0[0][width - 1].rgbtBlue = avgBlue;
    
    //For the middle rows
    for (int i = 1; i < height - 1; i++)
    {
        //For the left edges
        avgRed = (image[i - 1][0].rgbtRed + image[i - 1][1].rgbtRed + image[i][0].rgbtRed + image[i][1].rgbtRed + image[i + 1][0].rgbtRed + image[i + 1][1].rgbtRed) / 6.0;
        avgGreen = (image[i - 1][0].rgbtGreen + image[i - 1][1].rgbtGreen + image[i][0].rgbtGreen + image[i][1].rgbtGreen + image[i + 1][0].rgbtGreen + image[i + 1][1].rgbtGreen) / 6.0;
        avgBlue = (image[i - 1][0].rgbtBlue + image[i - 1][1].rgbtBlue + image[i][0].rgbtBlue + image[i][1].rgbtBlue + image[i + 1][0].rgbtBlue + image[i + 1][1].rgbtBlue) / 6.0;
        avgRed = round(avgRed);
        avgGreen = round(avgGreen);
        avgBlue = round(avgBlue);
        image0[i][0].rgbtRed = avgRed;
        image0[i][0].rgbtGreen = avgGreen;
        image0[i][0].rgbtBlue = avgBlue;
        
        for (int j = 1; j < width - 1; j++)
        {
            //Fot the middle of the middle rows
            avgRed = (image[i - 1][j - 1].rgbtRed + image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed + image[i][j - 1].rgbtRed + image[i][j].rgbtRed + image[i][j + 1].rgbtRed + image[i + 1][j - 1].rgbtRed + image[i + 1][j].rgbtRed + image[i + 1][j + 1].rgbtRed) / 9.0;
            avgGreen = (image[i - 1][j - 1].rgbtGreen + image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen + image[i][j - 1].rgbtGreen + image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen + image[i + 1][j - 1].rgbtGreen + image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen) / 9.0;
            avgBlue = (image[i - 1][j - 1].rgbtBlue + image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue + image[i][j - 1].rgbtBlue + image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue + image[i + 1][j - 1].rgbtBlue + image[i + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue) / 9.0;
            avgRed = round(avgRed);
            avgGreen = round(avgGreen);
            avgBlue = round(avgBlue);
            image0[i][j].rgbtRed = avgRed;
            image0[i][j].rgbtGreen = avgGreen;
            image0[i][j].rgbtBlue = avgBlue;
        }
        //For the right edges
        avgRed = (image[i - 1][width - 2].rgbtRed + image[i - 1][width - 1].rgbtRed + image[i][width - 2].rgbtRed + image[i][width - 1].rgbtRed + image[i + 1][width - 2].rgbtRed + image[i + 1][width - 1].rgbtRed) / 6.0;
        avgGreen = (image[i - 1][width - 2].rgbtGreen + image[i - 1][width - 1].rgbtGreen + image[i][width - 2].rgbtGreen + image[i][width - 1].rgbtGreen + image[i + 1][width - 2].rgbtGreen + image[i + 1][width - 1].rgbtGreen) / 6.0;
        avgBlue = (image[i - 1][width - 2].rgbtBlue + image[i - 1][width - 1].rgbtBlue + image[i][width - 2].rgbtBlue + image[i][width - 1].rgbtBlue + image[i + 1][width - 2].rgbtBlue + image[i + 1][width - 1].rgbtBlue) / 6.0;
        avgRed = round(avgRed);
        avgGreen = round(avgGreen);
        avgBlue = round(avgBlue);
        image0[i][width - 1].rgbtRed = avgRed;
        image0[i][width - 1].rgbtGreen = avgGreen;
        image0[i][width - 1].rgbtBlue = avgBlue;
    }
    
    //For the last row
    
    //For the left corner from the last row
    avgRed = (image[height - 2][0].rgbtRed + image[height - 2][1].rgbtRed + image[height - 1][0].rgbtRed + image[height - 1][1].rgbtRed) / 4.0;
    avgGreen = (image[height - 2][0].rgbtGreen + image[height - 2][1].rgbtGreen + image[height - 1][0].rgbtGreen + image[height - 1][1].rgbtGreen) / 4.0;
    avgBlue = (image[height - 2][0].rgbtBlue + image[height - 2][1].rgbtBlue + image[height - 1][0].rgbtBlue + image[height - 1][1].rgbtBlue) / 4.0;
    avgRed = round(avgRed);
    avgGreen = round(avgGreen);
    avgBlue = round(avgBlue);
    image0[height - 1][0].rgbtRed = avgRed;
    image0[height - 1][0].rgbtGreen = avgGreen;
    image0[height - 1][0].rgbtBlue = avgBlue;
    
    //For the middle of the last row
    for (int i = 1; i < width - 1; i++)
    {
        avgRed = (image[height - 2][i - 1].rgbtRed + image[height - 2][i].rgbtRed + image[height - 2][i + 1].rgbtRed + image[height - 1][i - 1].rgbtRed + image[height - 1][i].rgbtRed + image[height - 1][i + 1].rgbtRed) / 6.0;
        avgGreen = (image[height - 2][i - 1].rgbtGreen + image[height - 2][i].rgbtGreen + image[height - 2][i + 1].rgbtGreen + image[height - 1][i - 1].rgbtGreen + image[height - 1][i].rgbtGreen + image[height - 1][i + 1].rgbtGreen) / 6.0;
        avgBlue = (image[height - 2][i - 1].rgbtBlue + image[height - 2][i].rgbtBlue + image[height - 2][i + 1].rgbtBlue + image[height - 1][i - 1].rgbtBlue + image[height - 1][i].rgbtBlue + image[height - 1][i + 1].rgbtBlue) / 6.0;
        avgRed = round(avgRed);
        avgGreen = round(avgGreen);
        avgBlue = round(avgBlue);
        image0[height - 1][i].rgbtRed = avgRed;
        image0[height - 1][i].rgbtGreen = avgGreen;
        image0[height - 1][i].rgbtBlue = avgBlue;
    }
    //For the right corner of the last row
    avgRed = (image[height - 2][width - 2].rgbtRed + image[height - 2][width - 1].rgbtRed + image[height - 1][width - 2].rgbtRed + image[height - 1][width - 1].rgbtRed) / 4.0;
    avgGreen = (image[height - 2][width - 2].rgbtGreen + image[height - 2][width - 1].rgbtGreen + image[height - 1][width - 2].rgbtGreen + image[height - 1][width - 1].rgbtGreen) / 4.0;
    avgBlue = (image[height - 2][width - 2].rgbtBlue + image[height - 2][width - 1].rgbtBlue + image[height - 1][width - 2].rgbtBlue + image[height - 1][width - 1].rgbtBlue) / 4.0;
    avgRed = round(avgRed);
    avgGreen = round(avgGreen);
    avgBlue = round(avgBlue);
    image0[height - 1][width - 1].rgbtRed = avgRed;
    image0[height - 1][width - 1].rgbtGreen = avgGreen;
    image0[height - 1][width - 1].rgbtBlue = avgBlue;
    
    //Making the original image identical to the blurred duplicate
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = image0[i][j].rgbtRed;
            image[i][j].rgbtGreen = image0[i][j].rgbtGreen;
            image[i][j].rgbtBlue = image0[i][j].rgbtBlue;
        }
    }
    return;
}
