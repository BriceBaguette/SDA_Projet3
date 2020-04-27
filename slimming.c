#include "slimming.h"

PNMImage* reduceImageWidth(const PNMImage* image, size_t k)
{
	size_t width  = image.width;
    size_t height = image.height;
    size_t size = width*height;
    double energy[size];
    double cost[size];
    int move[size];

    //remplissage du tableau d'enrgie
    for (size_t i = 0; i < size_energy ; ++i)
    {
    	if ((i%width) == 0)
    		energy[i] = ...;
    	else if((i%width) == width)
    		energy[i] = ...;
    	else
    		energy[i] = ...;
    }

    //remplissage du tableau de cout et de mouvement
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
    for (size_t i = 0; i < k; ++i)
    {
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
    }
}
