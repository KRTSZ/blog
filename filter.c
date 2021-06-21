#include "helpers.h"
#include <stdio.h>
#include <stdbool.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            float tmp = (image[h][w].rgbtRed + image[h][w].rgbtGreen + image[h][w].rgbtBlue) / 3;
            float a = tmp - (int)tmp;
            if (a >= 0.5)
            {
                tmp += 1;
            }
            image[h][w].rgbtRed = (int)tmp;
            image[h][w].rgbtGreen = (int)tmp;
            image[h][w].rgbtBlue = (int)tmp;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            float tmpRed = (image[h][w].rgbtRed * 0.393 + image[h][w].rgbtGreen * 0.769 + image[h][w].rgbtBlue * 0.189);
            float a = tmpRed - (int)tmpRed;
            if (a >= 0.5)
            {
                tmpRed += 1;
            }
            if (tmpRed > 255)
            {
                tmpRed = 255;
            }
            if (tmpRed < 0)
            {
                tmpRed = 0;
            }
            tmpRed = (int)tmpRed;

            float tmpGreen = (image[h][w].rgbtRed * 0.349 + image[h][w].rgbtGreen * 0.686 + image[h][w].rgbtBlue * 0.168);
            float b = tmpGreen - (int)tmpGreen;
            if (b >= 0.5)
            {
                tmpGreen += 1;
            }
            if (tmpGreen > 255)
            {
                tmpGreen = 255;
            }
            if (tmpGreen < 0)
            {
                tmpGreen = 0;
            }
            tmpGreen = (int)tmpGreen;

            float tmpBlue = (image[h][w].rgbtRed * 0.272 + image[h][w].rgbtGreen * 0.534 + image[h][w].rgbtBlue * 0.131);
            float c = tmpBlue - (int)tmpBlue;
            if (c >= 0.5)
            {
                tmpBlue += 1;
            }
            if (tmpBlue > 255)
            {
                tmpBlue = 255;
            }
            if (tmpBlue < 0)
            {
                tmpBlue = 0;
            }
            tmpBlue = (int)tmpBlue;

            image[h][w].rgbtRed = tmpRed;
            image[h][w].rgbtGreen = tmpGreen;
            image[h][w].rgbtBlue = tmpBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < (width / 2); w++)
        {
            RGBTRIPLE tmp = image[h][w];
            image[h][w] = image[h][width - w - 1];
            image[h][width - w - 1] = tmp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            // exceptions for 4 corners
            bool ha = false;
            bool hb = false;
            bool wa = false;
            bool wb = false;
            if (h == 0)
            {
                ha = true;
                //printf("ha = true\n");
            }
            if (h == height -1)
            {
                hb = true;
                //printf("hb = true\n");
            }
            if (w == 0)
            {
                wa = true;
                //printf("wa = true\n");
            }
            if (w == width-1)
            {
                wb = true;
                //printf("wb = true\n");
            }


            if (ha && wa)
            {
                //printf("h0 w0\n");
                image[h][w].rgbtRed = (image[h+1][w+1].rgbtRed + image[h+1][w].rgbtRed + image[h][w+1].rgbtRed + image[h][w].rgbtRed) / 4;
                image[h][w].rgbtGreen = (image[h+1][w+1].rgbtGreen + image[h+1][w].rgbtGreen + image[h][w+1].rgbtGreen + image[h][w].rgbtGreen) / 4;
                image[h][w].rgbtBlue = (image[h+1][w+1].rgbtBlue + image[h+1][w].rgbtBlue + image[h][w+1].rgbtBlue + image[h][w].rgbtBlue) / 4;
                //printf("finish\n");
            }
            if (ha && wb)
            {
                //printf("h0 ww\n");
                image[h][w].rgbtRed = (image[h+1][w-1].rgbtRed + image[h+1][w].rgbtRed + image[h][w-1].rgbtRed + image[h][w].rgbtRed) / 4;
                image[h][w].rgbtGreen = (image[h+1][w-1].rgbtGreen + image[h+1][w].rgbtGreen + image[h][w-1].rgbtGreen + image[h][w].rgbtGreen) / 4;
                image[h][w].rgbtBlue = (image[h+1][w-1].rgbtBlue + image[h+1][w].rgbtBlue + image[h][w-1].rgbtBlue + image[h][w].rgbtBlue) / 4;
                //printf("finish\n");
            }
            if (hb && wa)
            {
                //printf("hh w0\n");
                image[h][w].rgbtRed = (image[h-1][w+1].rgbtRed + image[h-1][w].rgbtRed + image[h][w+1].rgbtRed + image[h][w].rgbtRed) / 4;
                image[h][w].rgbtGreen = (image[h-1][w+1].rgbtGreen + image[h-1][w].rgbtGreen + image[h][w+1].rgbtGreen + image[h][w].rgbtGreen) / 4;
                image[h][w].rgbtBlue = (image[h-1][w+1].rgbtBlue + image[h-1][w].rgbtBlue + image[h][w+1].rgbtBlue + image[h][w].rgbtBlue) / 4;
                //printf("finish\n");
            }
            if (hb && wb)
            {
                //printf("hh ww\n");
                image[h][w].rgbtRed = (image[h-1][w-1].rgbtRed + image[h-1][w].rgbtRed + image[h][w-1].rgbtRed + image[h][w].rgbtRed) / 4;
                image[h][w].rgbtGreen = (image[h-1][w-1].rgbtGreen + image[h-1][w].rgbtGreen + image[h][w-1].rgbtGreen + image[h][w].rgbtGreen) / 4;
                image[h][w].rgbtBlue = (image[h-1][w-1].rgbtBlue + image[h-1][w].rgbtBlue + image[h][w-1].rgbtBlue + image[h][w].rgbtBlue) / 4;
                //printf("finish\n");
            }
            // exceptions for the 4 sides
            if ((ha && !wa) && (ha && !wb))
            {
                //printf("h0\n");
                image[h][w].rgbtRed = (image[h+1][w+1].rgbtRed + image[h+1][w].rgbtRed + image[h][w+1].rgbtRed + image[h][w].rgbtRed + image[h][w-1].rgbtRed + image[h+1][w-1].rgbtRed) / 6;
                image[h][w].rgbtGreen = (image[h+1][w+1].rgbtGreen + image[h+1][w].rgbtGreen + image[h][w+1].rgbtGreen + image[h][w].rgbtGreen + image[h][w-1].rgbtGreen + image[h+1][w-1].rgbtGreen) / 6;
                image[h][w].rgbtBlue = (image[h+1][w+1].rgbtBlue + image[h+1][w].rgbtBlue + image[h][w+1].rgbtBlue + image[h][w].rgbtBlue + image[h][w-1].rgbtBlue + image[h+1][w-1].rgbtBlue) / 6;
                //printf("finish\n");
            }
            if ((hb && !wa) && (hb && !wb))
            {
                //printf("hh\n");
                image[h][w].rgbtRed = (image[h-1][w+1].rgbtRed + image[h-1][w].rgbtRed + image[h][w+1].rgbtRed + image[h][w].rgbtRed + image[h][w-1].rgbtRed + image[h-1][w-1].rgbtRed) / 6;
                image[h][w].rgbtGreen = (image[h-1][w+1].rgbtGreen + image[h-1][w].rgbtGreen + image[h][w+1].rgbtGreen + image[h][w].rgbtGreen + image[h][w-1].rgbtGreen + image[h-1][w-1].rgbtGreen) / 6;
                image[h][w].rgbtBlue = (image[h-1][w+1].rgbtBlue + image[h-1][w].rgbtBlue + image[h][w+1].rgbtBlue + image[h][w].rgbtBlue + image[h][w-1].rgbtBlue + image[h-1][w-1].rgbtBlue) / 6;
                //printf("finish\n");
            }
            if ((wa && !ha) && (wa && !hb))
            {
                //printf("w0\n");
                //printf("h:%i w:%i\n", h, w);
                image[h][w].rgbtRed = (image[h+1][w+1].rgbtRed + image[h+1][w].rgbtRed + image[h][w+1].rgbtRed + image[h][w].rgbtRed + image[h-1][w].rgbtRed + image[h-1][w+1].rgbtRed) / 6;
                image[h][w].rgbtGreen = (image[h+1][w+1].rgbtGreen + image[h+1][w].rgbtGreen + image[h][w+1].rgbtGreen + image[h][w].rgbtGreen + image[h-1][w].rgbtGreen + image[h-1][w+1].rgbtGreen) / 6;
                image[h][w].rgbtBlue = (image[h+1][w+1].rgbtBlue + image[h+1][w].rgbtBlue + image[h][w+1].rgbtBlue + image[h][w].rgbtBlue + image[h-1][w].rgbtBlue + image[h-1][w+1].rgbtBlue) / 6;
                //printf("finish\n");
            }
            if ((wb && !ha) && (wb && !hb))
            {
                //printf("ww\n");
                image[h][w].rgbtRed = (image[h+1][w-1].rgbtRed + image[h+1][w].rgbtRed + image[h][w-1].rgbtRed + image[h][w].rgbtRed + image[h-1][w].rgbtRed + image[h-1][w-1].rgbtRed) / 6;
                image[h][w].rgbtGreen = (image[h+1][w-1].rgbtGreen + image[h+1][w].rgbtGreen + image[h][w-1].rgbtGreen + image[h][w].rgbtGreen + image[h-1][w].rgbtGreen + image[h-1][w-1].rgbtGreen) / 6;
                image[h][w].rgbtBlue = (image[h+1][w-1].rgbtBlue + image[h+1][w].rgbtBlue + image[h][w-1].rgbtBlue + image[h][w].rgbtBlue + image[h-1][w].rgbtBlue + image[h-1][w-1].rgbtBlue) / 6;
                //printf("finish\n");
            }
            // normal cases
            if (!ha && !hb && !wa && !wb)
            {
                //printf("norm\n");
                image[h][w].rgbtRed = (image[h+1][w+1].rgbtRed + image[h+1][w].rgbtRed + image[h][w+1].rgbtRed + image[h][w].rgbtRed + image[h-1][w-1].rgbtRed + image[h][w-1].rgbtRed + image[h-1][w].rgbtRed + image[h+1][w-1].rgbtRed + image[h-1][w+1].rgbtRed) / 9;
                image[h][w].rgbtGreen = (image[h+1][w+1].rgbtGreen + image[h+1][w].rgbtGreen + image[h][w+1].rgbtGreen + image[h][w].rgbtGreen + image[h-1][w-1].rgbtGreen + image[h][w-1].rgbtGreen + image[h-1][w].rgbtGreen + image[h+1][w-1].rgbtGreen + image[h-1][w+1].rgbtGreen) / 9;
                image[h][w].rgbtBlue = (image[h+1][w+1].rgbtBlue + image[h+1][w].rgbtBlue + image[h][w+1].rgbtBlue + image[h][w].rgbtBlue + image[h-1][w-1].rgbtBlue + image[h][w-1].rgbtBlue + image[h-1][w].rgbtBlue + image[h+1][w-1].rgbtBlue + image[h-1][w+1].rgbtBlue) / 9;
                //printf("finish\n");
            }
        }
    }


        return;
}
