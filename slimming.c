#include "slimming.h"
#include <stdlib.h>

//remplissage du tableau d'énergie
static void fillEnergy(PNMImage* image, double* energy, size_t width, size_t height);
//remplissage du tableau de coup et de mouvement
static void fillCostAndMove(double* energy, double* cost, int* move, size_t width, size_t height);
//recherche du coup minimum de la dernière rangée 
static size_t searchMinCost(double* cost, size_t width, size_t height);
//crée le sillion des pixels à enlever
static void createSillion(int* move, size_t* sillion, size_t width, size_t height, size_t min);
//supprime le sillion de l'image
static PNMImage* deleteSillion(PNMImage* image, size_t* sillion, size_t width, size_t height);
//remet l'énergie des voisins du sillion à 0 et supprime le sillion de l'énergie
static double* updateEnergy(double* energy, size_t* sillion, size_t width, size_t height);


static void fillEnergy(PNMImage* image, double* energy,  size_t width, size_t height)
{
	size_t size = width*height;
	for (size_t i = 0; i < size; ++i)
    {
    	if (energy[i] == 0)
    	{
    		if ((i%width) == 0)
    			energy[i] = ...;
    		else if((i%width) == width-1)
    			energy[i] = ...;
    		else
    			energy[i] = ...;
    	}
    }
}

static void fillCostAndMove(double* energy, double* cost, int* move, size_t width, size_t height)
{
	size_t size = width*height;
	for (size_t i = 0; i < size; ++i)
    { 
    	if (i < width)
    	{
    		cost[i] = energy[i];
    		move[i] = 2;
    	}

    	else
    	{
    		double min = cost[i-width-1] + energy[i];
    		int direction = 1;
    		if (cost[i-width] + energy[i] < min)
    		{
    			min = cost[i-width] + energy[i];
    			direction = 0;
    		}
    		if (cost[i-width+1] + energy[i] < min)
    		{
    			min = cost[i-width+1] + energy[i];
    			direction = -1;
    		}
    		cost[i] = min;
    		move[i] = direction;
    	}
    }
}

static size_t searchMinCost(double* cost, size_t width, size_t height)
{
	size_t size = width*height;
	double min_cost = cost[size - width]
    size_t count = size-width;
   	for (size_t i = size-width+1; i < size ; ++i)
  	{
   		if (cost[i] < min_cost)
    	{
    		min_cost = cost[i];
  			count = i;
 		}
 	}
 	return count;
}

static void createSillion(int* move, size_t* sillion, size_t width, size_t height, size_t min)
{
	for (size_t i = 0; i < height-1; ++i)
	{
		sillion[i] = min;
		min = min-width-move[i];
	}
	sillion[height-1] = min;
}

static PNMImage* deleteSillion(PNMImage* image, size_t* sillion, size_t width, size_t height)
{
	PNMImage* newimage = createPNM(width-1, height);
	size_t size = width*height;

	for (size_t i = 0, size_t count = 0, size_t count2 = height-1; i < size; ++i)
	{
		if(count == sillion[count2])
		{
			count2--;
			continue;
		}
		newimage[count] = image[i];
		count++;
	}
	freePNM(image);
	return newimage;
}

static double* updateEnergy(double* energy, size_t* sillion, size_t width, size_t height)
{
	double* newenergy = (double*) calloc((width-1)*height, sizeof(double));
	size_t size = width*height;

	for (size_t i = 0, size_t count = 0, size_t count2 = height-1; i < size; ++i)
	{
		if(count == sillion[count2])
		{
			newenergy[count] = 0;
			newenergy[count-1] = 0;
			count2--;
			count++;
			i++;
			continue;
		}
		newenergy[count] = energy[i];
		count++;
	}
	free(energy);
	return newenergy;
}

PNMImage* reduceImageWidth(const PNMImage* image, size_t k)
{
	size_t width  = image.width;
    size_t height = image.height;
    size_t size = width*height;
    double* energy = (double*) calloc(size, sizeof(double));
    double* cost = (double*) calloc(size, sizeof(double));
    int* move = (int*) calloc(size, sizeof(int));
    size_t* sillion = (size_t*) calloc(height, sizeof(size_t));
    PNMImage* newimage = createPNM(width, height);

    for (int i = 0; i < size; ++i)
    {
    	newimage[i] = image[i];
    }

    for (int i = 0; i < k-1; ++i)
    {
    	fillEnergy(newimage, energy, width, height);
    	fillCostAndMove(energy, cost, move, width, height);
    	int min = searchMinCost(cost, width, height);
    	createSillion(move, sillion, width, height, min);
    	newimage = deleteSillion(image, sillion, width, height);
    	energy = updateEnergy(energy, sillion, width, height);
    	size -=width;
    	width--;
    	cost* = (double*) realloc(cost, size*sizeof(double));
    	move* = (int*) realloc(move, size*sizeof(int));
    }
    fillEnergy(newimage, energy, width, height);
    fillCostAndMove(energy, cost, move, width, height);
   	int min = searchMinCost(cost, width, height);
   	createSillion(move, sillion, width, height, min);
   	newimage = deleteSillion(image, sillion, width, height);

    return newimage;
}
