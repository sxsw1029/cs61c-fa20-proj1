/************************************************************************
**
** NAME:        steganography.c
**
** DESCRIPTION: CS61C Fall 2020 Project 1
**
** AUTHOR:      Dan Garcia  -  University of California at Berkeley
**              Copyright (C) Dan Garcia, 2020. All rights reserved.
**				Justin Yokota - Starter Code
**				YOUR NAME HERE
**
** DATE:        2020-08-23
**
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "imageloader.h"

//Determines what color the cell at the given row/col should be. This should not affect Image, and should allocate space for a new Color.
Color *evaluateOnePixel(Image *image, int row, int col)
{
	//YOUR CODE HERE
	Color *color = (Color *)malloc(sizeof(Color));
	if(color == NULL) return NULL;

	if((image->image[row][col].B & 0x1) == 0)
	{
		color->R = 0;
		color->G = 0;
		color->B = 0;
	}
	else
	{
		color->R = 255;
		color->G = 255;
		color->B = 255;
	}

	return color;
}

//Given an image, creates a new image extracting the LSB of the B channel.
Image *steganography(Image *image)
{
	//YOUR CODE HERE
	uint32_t rows = image->rows;
	uint32_t cols = image->cols;

	Color **colorImage = (Color **)malloc(rows * sizeof(Color *));
	if(colorImage == NULL) return NULL;

	for(uint32_t i = 0; i < rows; i++)
	{
		colorImage[i] = (Color *)malloc(cols * sizeof(Color));
		if(colorImage[i] == NULL)
		{
			for(uint32_t j = 0; j < i; j++)
			{
				free(colorImage[j]);
			}
			free(colorImage);
			return NULL;
		}
	}

	Image *newImage = (Image *)malloc(sizeof(Image));
	if(newImage == NULL)
	{
        for(uint32_t i = 0; i < rows; i++)
		{
            free(colorImage[i]);
        }
        free(colorImage);
        return NULL;
	}

	newImage->image = colorImage;
	newImage->rows = rows;
	newImage->cols = cols;

	for(uint32_t i = 0; i < rows; i++)
	{
		for(uint32_t j = 0; j < cols; j++)
		{
			newImage->image[i][j] = *evaluateOnePixel(image, i, j);
		}
	}

	return newImage;
}

/*
Loads a file of ppm P3 format from a file, and prints to stdout (e.g. with printf) a new image, 
where each pixel is black if the LSB of the B channel is 0, 
and white if the LSB of the B channel is 1.

argc stores the number of arguments.
argv stores a list of arguments. Here is the expected input:
argv[0] will store the name of the program (this happens automatically).
argv[1] should contain a filename, containing a file of ppm P3 format (not necessarily with .ppm file extension).
If the input is not correct, a malloc fails, or any other error occurs, you should exit with code -1.
Otherwise, you should return from main with code 0.
Make sure to free all memory before returning!
*/
int main(int argc, char **argv)
{
	//YOUR CODE HERE
	if(argc != 2) return -1;

	Image *image = readData(argv[1]);
	if(image == NULL) return -1;

	Image *newImage = steganography(image);

	writeData(newImage);

	freeImage(image);
	freeImage(newImage);
}
