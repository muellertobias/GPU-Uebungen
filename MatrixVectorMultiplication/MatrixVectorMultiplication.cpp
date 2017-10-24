// MatrixVectorMultiplication.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <cstdlib>
#include <ctime>
#include <omp.h>

void randomInit(float* vector, int n) 
{
	srand(time(NULL));
	#pragma omp parallel for
	for (int i = 0; i < n; i++) 
	{
		vector[i] = (float)rand() / (float)(RAND_MAX / (float)rand());
		//vector[i] = 2;
	}
}

void init(float* vector, int n)
{
	#pragma omp parallel for
	for (int i = 0; i < n; i++)
	{
		vector[i] = 0;
	}
}

void matrixInit(float** matrix, int n, int m) 
{
	#pragma omp parallel for
	for (int i = 0; i < n; i++)
	{
		matrix[i] = new float[n];
		for (int j = 0; j < n; j++)
		{
			matrix[i][j] = 0;
		}
	}
}

// Übung 1 - Aufgabe 2
int main()
{
	const int n = 50000;

	float **a = new float*[n];
	float b[n];
	float c[n];

	randomInit(b, n);
	init(c, n);
	matrixInit(a, n, n);

	clock_t start = clock();

	// do it
	//#pragma omp parallel for // 1,67s (n=29000, speedup=66%), 6,9s (n=40000, speedup=52%), 0,745s (n=20000, speedup=70%), 2,6s (n=35000, speedup=65%), 14,2s (n=50000)
	for (int i = 0; i < n; i++) 
	{
		//#pragma omp parallel for // 11,66s (n=29000)
		for (int j = 0; j < n; j++) 
		{
			c[i] += a[i][j] * b[j];
		}
	}

	clock_t stop = clock();
	clock_t difference = stop - start;
	double t = (double)difference/ CLOCKS_PER_SEC; // ohne OpenMP 5,2s (n=29000), 14,24s (n=40000), 2,46s (n=20000), 7,55s (n=35000), 22,4s
    return 0;
}

