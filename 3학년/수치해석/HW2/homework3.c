#include <stdio.h>
#define NRANSI
#include "nr.h"
#include "nrutil.h"

#define N 100
#define NBMAX 20
#define X1 1.0			
//#define X1 -2.0
#define X2 10.0			
//#define X2 -1.0
static float fx(float x) {
	return bessj0(x);
}

static void funcd(float x, float *fn, float *df)
{
	*fn = bessj0(x);
	*df = -bessj1(x);
}		

//Bisection
static void bi(int nb, float *xb1, float*xb2) {			
	float xacc, root;
	printf("============== Bisection ===============\n");
	for (int i = 1; i <= nb; i++) {
		xacc = (10e-6)*(xb1[i] + xb2[i]) / 2.0;
		root = rtbis(fx, xb1[i], xb2[i], xacc);
		printf("root %3d %14.6f %14.6f\n\n", i, root, fx(root));
	}
}			

//Linear Interpolation
static void LI(int nb, float *xb1, float*xb2) {			
	float xacc, root;
	printf("======= Linear Interpolation ==========\n");
	for (int i = 1; i <= nb; i++) {
		xacc = (10e-6)*(xb1[i] + xb2[i]) / 2.0;
		//xacc = (10e-6);
		root = rtflsp(fx, xb1[i], xb2[i], xacc);
		printf("root %3d %14.6f %14.6f\n\n", i, root, fx(root));
	}
}		

//Secant
static void Se(int nb, float *xb1, float*xb2) {			
	float xacc, root;
	printf("============== Secant ================\n");
	for (int i = 1; i <= nb; i++) {
		xacc = (10e-6)*(xb1[i] + xb2[i]) / 2.0;
		root = rtsec(fx, xb1[i], xb2[i], xacc);
		printf("root %3d %14.6f %14.6f\n\n", i, root, fx(root));
	}
}	 

//Newton raphson
static void NR(int nb, float *xb1, float*xb2) {		
	float xacc, root;
	printf("============ Newton Raphson =============\n");
	for (int i = 1; i <= nb; i++) {
		xacc = (10e-6)*(xb1[i] + xb2[i]) / 2.0;
		root = rtnewt(funcd, xb1[i], xb2[i], xacc);
		printf("root %3d %14.6f %14.6f\n\n", i, root, fx(root));
	}
}

//Newton with Bracketing
static void NB(int nb, float *xb1, float*xb2) {			
	float xacc, root;
	printf("========= Newton with Bracketing ========\n");
	for (int i = 1; i <= nb; i++) {
		xacc = (10e-6)*(xb1[i] + xb2[i]) / 2.0;
		root = rtsafe(funcd, xb1[i], xb2[i], xacc);
		printf("root %3d %14.6f %14.6f\n\n", i, root, fx(root));
	}
}

//Muller method
static void MU(int nb, float *xb1, float*xb2) {			
	float xacc, root;
	printf("============ Muller =============\n");
	for (int i = 1; i <= nb; i++) {
		xacc = (10e-6)*(xb1[i] + xb2[i]) / 2.0;
		root = muller(funcd, xb1[i], xb2[i], xacc);
		printf("root %3d %14.6f %14.6f\n\n", i, root, fx(root));
	}
}

int main(void) {
	int i, nb = NBMAX;
	float xacc, root, *xb1, *xb2;
	xb1 = vector(1, NBMAX);
	xb2 = vector(1, NBMAX);
	zbrak(fx, X1, X2, N, xb1, xb2, &nb);


	printf("\nRoots of bessj0:\n");
	printf("%21s %15s\n", "x", "f(x)");

	
	bi(nb, xb1, xb2);
	LI(nb, xb1, xb2);
	Se(nb, xb1, xb2);
	NR(nb, xb1, xb2);
	NB(nb, xb1, xb2);
	MU(nb, xb1, xb2);
	free_vector(xb2, 1, NBMAX);
	free_vector(xb1, 1, NBMAX);
	return 0;
}
#undef NRANSI