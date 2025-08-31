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
	char format[20];
	uint32_t range;

	FILE *fp = fopen(filename, "r");

	Image *image = (Image *)malloc(sizeof(Image));

	fscanf(fp, "%s %u %u %u", format, &image->cols, &image->rows, &range);

	image->image = (Color **)malloc(image->rows * sizeof(Color *));

	for(uint32_t i = 0; i < image->rows; i++)
	{
		image->image[i] = (Color *)malloc(image->cols * sizeof(Color));

		for(uint32_t j = 0; j < image->cols; j++)
		{
			fscanf(fp, "%hhu %hhu %hhu", &image->image[i][j].R, &image->image[i][j].G, &image->image[i][j].B);
		}
	}

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
