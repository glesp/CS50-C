#include "helpers.h"
#include <stdio.h>
#include <string.h>
#include <cs50.h>
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            float red = image[i][j].rgbtRed;
            float green = image[i][j].rgbtGreen;
            float blue = image[i][j].rgbtBlue;

            int avg = round(red + green + blue)/3;

            image[i][j].rgbtRed = image[i][j].rgbtGreen = image[i][j].rgbtBlue = avg;
        }
    }
    return;
}

// Convert image to sepia
// Sepia guide below
//sepiaRed = .393 * originalRed + .769 * originalGreen + .189 * originalBlue
//sepiaGreen = .349 * originalRed + .686 * originalGreen + .168 * originalBlue
//sepiaBlue = .272 * originalRed + .534 * originalGreen + .131 * originalBlue

void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            float originalRed = image[i][j].rgbtRed;
            float originalGreen = image[i][j].rgbtGreen;
            float originalBlue = image[i][j].rgbtBlue;

            int sepiaRed = round(.393 * originalRed + .769 * originalGreen + .189 * originalBlue);
            int sepiaGreen = round(.349 * originalRed + .686 * originalGreen + .168 * originalBlue);
            int sepiaBlue = round(.272 * originalRed + .534 * originalGreen + .131 * originalBlue);

            if(sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            if(sepiaGreen > 255)
            {
            sepiaGreen = 255;
            }
            if(sepiaBlue > 255)
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
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width/2; j++)
        {
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - j];
            image[i][width - j] = temp;

        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            int count = 0;
            int totalred = copy[i][j].rgbtRed;
            int totalgreen = copy[i][j].rgbtGreen;
            int totalblue = copy[i][j].rgbtBlue;
            count++;

        //if row below
        if(j + 1 < height)
        {
            totalred += copy[i + 1][j].rgbtRed;
            totalgreen += copy[i + 1][j].rgbtGreen;
            totalblue += copy[i + 1][j].rgbtBlue;
            count++;
        }
        //if column to right
        if(i + 1 < width)
        {
            totalred += copy[i][j + 1].rgbtRed;
            totalgreen += copy[i][j + 1].rgbtGreen;
            totalblue += copy[i][j + 1].rgbtBlue;
            count++;
        }
        //if cell below and right
        if(i + 1 < height && j + 1 < width)
        {
            totalred += copy[i + 1][j + 1].rgbtRed;
            totalgreen += copy[i + 1][j + 1].rgbtGreen;
            totalblue += copy[i + 1][j + 1].rgbtBlue;
            count++;
        }
        //if row above available
        if(i - 1 >= 0)
        {
            totalred += copy[i - 1][j].rgbtRed;
            totalgreen += copy[i - 1][j].rgbtGreen;
            totalblue += copy[i - 1][j].rgbtBlue;
            count++;
        }

        //if column to left available
        if(j - 1 >= 0)
        {
            totalred += copy[i][j - 1].rgbtRed;
            totalgreen += copy[i][j - 1].rgbtGreen;
            totalblue += copy[i][j - 1].rgbtBlue;
            count++;
        }
        //if row above and column to right avilable
        if(i - 1 >=0 && j + 1 < width)
        {
            totalred += copy[i - 1][j + 1].rgbtRed;
            totalgreen += copy[i - 1][j + 1].rgbtGreen;
            totalblue += copy[i - 1][j + 1].rgbtBlue;
            count++;
        }
        //if cell below and left
        if(i + i < height && j - 1 >= 0)
        {
            totalred += copy[i + 1][j - 1].rgbtRed;
            totalgreen += copy[i + 1][j - 1].rgbtGreen;
            totalblue += copy[i + 1][j - 1].rgbtBlue;
            count++;
        }
        // if cell above and left
        if(i - i >= 0 && j - 1 >= 0)
        {
            totalred += copy[i - 1][j - 1].rgbtRed;
            totalgreen += copy[i - 1][j - 1].rgbtGreen;
            totalblue += copy[i - 1][j - 1].rgbtBlue;
            count++;
        }

          image[i][j].rgbtRed = totalred/count;
          image[i][j].rgbtGreen = totalgreen/counld
          image[i][j].rgbtBlue = totalblue/count;

          totalred = totalgreen = totalblue = 0;
          count = 0;


        }

    }





    return;
}
