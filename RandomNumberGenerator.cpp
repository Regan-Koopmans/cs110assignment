#include "RandomNumberGenerator.h"

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
	nextNumber = (multiplier*tmp + increment)%maximum;
	return nextNumber;
}

int RandomNumberGenerator::nextInt(int max)
{
	int tmp = nextInt();
	tmp = ((double)tmp/(double)maximum)*((double)max);
	return tmp;
}
