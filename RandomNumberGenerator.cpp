#include <iostream>

#include "RandomNumberGenerator.h"

using namespace std;

RandomNumberGenerator::RandomNumberGenerator(int seed, int max, int m, int i)
{
	nextNumber = seed;
	multiplier = m;
	increment = i;
	maximum = max;
}

int RandomNumberGenerator::nextInt()
{

	int tmp = nextNumber;
	nextNumber = (multiplier * tmp + increment) % maximum;
	return tmp;
}

int RandomNumberGenerator::nextInt(int max)
{
	int tmp = nextInt();
	tmp = ((double)tmp/(double)maximum)*((double)max);
	return tmp;
}
