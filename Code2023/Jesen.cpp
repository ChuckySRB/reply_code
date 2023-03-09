#include "Jesen.hpp"

#include <fstream>
//#include <bits/stdc++.h>
#include <vector>
#include <algorithm>

using namespace std;

struct AproxVectorElem {
	int value;
	int i;
	int j;
	bool operator< (AproxVectorElem& a2)
	{
		return this->value < a2.value;
	}
};


long** matrix;




Coordinate* aprox_field(Map* map)
{
	int R = map->R;
	int C = map->C;
	int** matrix = map->Grid;
	int cntS = map->S;
	int* snakes = map->Snakes;

	int currently_taken = map->T;
	

	float avgSnakeSize = 0;
	for (int i = 0; i < cntS; i++)
	{
		avgSnakeSize += snakes[i];
	}

	avgSnakeSize /= cntS;

	int aproxSquareLen = (int) sqrt(avgSnakeSize) + 1;
	vector<AproxVectorElem> bestFields = vector<AproxVectorElem>(cntS);


	int numOfFilled = 0;
	int tmpAvg = 0;
	for (int i = 0; i < R; i+= aproxSquareLen)
	{
		for (int j = 0; j < C; j += aproxSquareLen)
		{
			tmpAvg = 0;

			for (int k = 0; k < aproxSquareLen; k++)
			{
				for (int l = 0; l < aproxSquareLen; l++)
				{
					tmpAvg += matrix[(k + i) % R][(l + j) % C];
				}
			}
			if (numOfFilled < cntS)
			{
				AproxVectorElem ap = AproxVectorElem();
				ap.value = tmpAvg;
				ap.i = i;
				ap.j = j;
				bestFields[numOfFilled] = ap;
				numOfFilled++;
				if (numOfFilled == cntS)
				{
					sort(bestFields.begin(), bestFields.end());
				}
			}
			else {

				if (bestFields[0].value < tmpAvg)
				{
					AproxVectorElem ap = AproxVectorElem();
					ap.value = tmpAvg;
					ap.i = i;
					ap.j = j;
					bestFields[0] = ap;
					sort(bestFields.begin(), bestFields.end());
				}

			}


		}
	}

	Coordinate* coordinates = new Coordinate[cntS];

	int dif = cntS - numOfFilled;

	for (int n = 0; n < numOfFilled; n++)
	{
		int i = bestFields[n].i;
		int j = bestFields[n].j;

		int bestVal = -11000;
		int lBest = 0;
		int mBest = 0;
		for (int l = 0; l < aproxSquareLen; l++)
		{
			for (int m = 0; m < aproxSquareLen; m++)
			{
				if (bestVal < matrix[(i + l) % R][(j + m) % C])
				{
					bestVal = matrix[(i + l) % R][(j + m) % C];
					lBest = l;
					mBest = m;
				}
			}
		}

		coordinates[n].X = (lBest + i) % R;
		coordinates[n].Y = (mBest + j) % C;
	}

	return coordinates;

}


int zdravo() {
	return 1;
}
