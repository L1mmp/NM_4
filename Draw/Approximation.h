#pragma once
class Approximation
{
public:
	double Approximate(double x, double a, double b, int m, int n);	
	void RandomiseF(double* f, double* x, int m);	
	void GetPointsX(double* x, double a, double b, int m);
private:
	double F(double x);
	void ArrD(double* d, double* x, int m, int n);
	void ArrB(double* b, double* f, double* x, int m, int n);
	double** GetA(double* B, double* D, int n);
	void SLU(double** A, double* C, int n);
};

