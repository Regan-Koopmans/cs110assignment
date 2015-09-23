#ifndef LINEARCONGRUENTIALRANDOMNUMBERGENERATOR_H
#define LINEARCONGRUENTIALRANDOMNUMBERGENERATOR_H


class RandomNumberGenerator
{
public:
    RandomNumberGenerator(int seed, int max, int m = 11, int i = 7);
		
    int nextInt();
    int nextInt(int max);
				
private:
    int nextNumber;
    int multiplier;
    int increment;
    int maximum;
};

#endif //LINEARCONGRUENTIALRANDOMNUMBERGENERATOR_H

