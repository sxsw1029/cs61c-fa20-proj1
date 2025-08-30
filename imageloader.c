/************************************************************************
**
** NAME:        imageloader.c
**
** DESCRIPTION: CS61C Fall 2020 Project 1
**
** AUTHOR:      Dan Garcia  -  University of California at Berkeley
**              Copyright (C) Dan Garcia, 2020. All rights reserved.
**              Justin Yokota - Starter Code
**				YOUR NAME HERE
**
**
** DATE:        2020-08-15
**
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include "imageloader.h"

//Opens a .ppm P3 image file, and constructs an Image object. 
//You may find the function fscanf useful.
//Make sure that you close the file with fclose before returning.
Image *readData(char *filename) 
{
	//YOUR CODE HERE
	FILE *fp = fopen(filename, "r");
	if(fp == NULL) return NULL;

	char format[20];
	uint32_t cols, rows, range;
	fscanf(fp, "%s %u %u %u", format, &cols, &rows, &range);

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

		for(uint32_t j = 0; j < cols; j++)
		{
			fscanf(fp, "%hhu %hhu %hhu", &colorImage[i][j].R, &colorImage[i][j].G, &colorImage[i][j].B);
		}
	}

	Image *image = (Image *)malloc(sizeof(Image));
	if(image == NULL)
	{
        for(uint32_t i = 0; i < rows; i++)
		{
            free(colorImage[i]);
        }
        free(colorImage);
        return NULL;
	}

	image->image = colorImage;
	image->rows = rows;
	image->cols = cols;

	fclose(fp);

	return image;
}

//Given an image, prints to stdout (e.g. with printf) a .ppm P3 file with the image's data.
void writeData(Image *image)
{
	//YOUR CODE HERE
	printf("P3\n");
	printf("%u %u\n", image->cols, image->rows);
	printf("255\n");

	for(uint32_t i = 0; i < image->rows; i++)
	{
		for (uint32_t j = 0; j < image->cols; j++)
		{
			printf("%3hhu %3hhu %3hhu", image->image[i][j].R, image->image[i][j].G, image->image[i][j].B);
			if(j + 1 != image->cols)
			{
				printf("   ");
			}
		}
		printf("\n");
	}
}

//Frees an image
void freeImage(Image *image)
{
	//YOUR CODE HERE
	for(uint32_t i = 0; i < image->rows; i++)
	{
		free(image->image[i]);
	}
	free(image->image);
	free(image);
}
