#include "stdafx.h"
#include "Approximation.h"

#define M_E        2.71828182845904523536

double Approximation::Approximate(double x, double a, double b, int m, int n)
{
	double* xPoints = new double[m];
	double* f = new double[m];
	GetPointsX(xPoints, a, b, m);
	RandomiseF(f, xPoints, m);


	double* D = new double[2 * n + 1];
	double* B = new double[2 * n + 1];

	ArrD(D, xPoints, m, n);
	ArrB(B, f, xPoints, m, n);

	double** A = GetA(B, D, n);
	double* C = new double[n + 1];

	SLU(A, C, n);

	double apprPolinom = 0.0;

	for (int i = 0; i < n + 1; i++)
	{
		apprPolinom += C[i] * pow(x, i);
	}

	delete[] xPoints;
	delete[] f;
	delete[] B;
	delete[] D;
	delete[] C;
	return apprPolinom;
}

double Approximation::F(double x)
{
	return pow(M_E, -x) * cos(x);
}

void Approximation::RandomiseF(double* f, double* x, int m)
{
	double* y = new double[m];
	double* z = new double[m];

	srand(time(NULL));
	int c = rand() % 5 + 1;

	for (int i = 0; i < m; i++)
	{
		y[i] = F(x[i]);
		z[i] = (double)rand() / RAND_MAX * 2.0 - 1;
		f[i] = (y[i] * (1 + z[i] / c));
	}

	delete[] y;
	delete[] z;
}

void Approximation::GetPointsX(double* x, double a, double b, int m)
{
	for (int i = 0; i < m; i++)
	{
		x[i] = a + i * (b - a) / (m - 1);
	}
}

void Approximation::ArrD(double* d, double* x, int m, int n)
{
	for (int i = 0; i < 2 * n + 1; i++)
	{
		d[i] = 0;
		for (int j = 0; j < m; j++)
		{
			d[i] += pow(x[j], i);
		}
	}
}

void Approximation::ArrB(double* b, double* f, double* x, int m, int n)
{
	for (int i = 0; i < n + 1; i++)
	{
		b[i] = 0;
		for (int j = 0; j < m; j++)
		{
			b[i] += pow(x[j], i) * f[j];
		}
	}
}

double** Approximation::GetA(double* B, double* D, int n)
{
	double** A;

	A = new double* [n + 1];

	for (int i = 0; i < n + 1; i++)	A[i] = new double[n + 2];

	for (int i = 0; i < n + 1; i++)
	{
		for (int j = 0; j < n + 1; j++)
		{
			A[i][j] = D[i + j];
		}
	}

	for (int i = 0; i < n + 1; i++)
	{
		A[i][n + 1] = B[i];
	}

	return A;
}

void Approximation::SLU(double** A, double* C, int n)
{
	double Amax, Pr;
	int p;
	for (int k = 0; k < n; k++)
	{
		Amax = abs(A[k][k]);
		p = k;
		for (int i = k + 1; i < n + 1; i++)
		{
			if (abs(A[i][k]) > Amax)
			{
				Amax = abs(A[i][k]);
				p = i;
			}
		}
		for (int j = k; j < n + 2; j++)
		{
			Pr = A[k][j];
			A[k][j] = A[p][j];
			A[p][j] = Pr;
		}
		for (int i = k + 1; i < n + 1; i++)
		{
			for (int j = k + 1; j < n + 2; j++)
			{
				A[i][j] = A[i][j] - (A[i][k] * A[k][j]) / A[k][k];
			}
		}
	}
	C[n] = A[n][n + 1] / A[n][n];
	for (int i = n - 1; i >= 0; i--)
	{
		double Sum = A[i][n + 1];
		for (int j = n; j >= i + 1; j--)
		{
			Sum = Sum - A[i][j] * C[j];
		}
		C[i] = Sum / A[i][i];
	}

}
