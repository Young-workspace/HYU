#include <stdio.h>
#include <math.h>
#include <time.h>
#define NRANSI
#include "nr.h"

//#define N 20							// Interval?
#define N 100
#define NOVER2 (N/2)
#define NPTS 10000				// Number of Sample
#define ISCAL 400
#define LLEN 50

void gauss() {
	char words[LLEN + 1];
	int i, j, k, klim, dist[N + 1];
	long idum = (-13);
	float dd, x;

	for (j = 0; j <= N; j++) dist[j] = 0;
	for (i = 1; i <= NPTS; i++) {
		x = 0.2* N*gasdev(&idum);
		j = (int)(x > 0 ? x + 0.5 : x - 0.5);
		if ((j >= -NOVER2) && (j <= NOVER2)) ++dist[j + NOVER2];
	}
	printf("Normally distributed deviate of %6d points\n", NPTS);
	printf("%5s %10s %9s\n", "x", "p(x)", "graph:");
	for (j = 0; j <= N; j++) {
		dd = (float)dist[j] / NPTS;
		for (k = 1; k <= LLEN; k++) words[k] = ' ';
		klim = (int)(ISCAL*dd);
		if (klim > LLEN)  klim = LLEN;
		for (k = 1; k <= klim; k++) words[k] = '*';
		printf("%8.4f %8.4f  ", j / (0.2*N) - 3, dd);
		for (k = 1; k <= LLEN; k++) printf("%c", words[k]);
		printf("\n");
	}
}

void ran() {
	char words[LLEN + 1];
	int i, j, k, klim, dist[N + 1];
	long idum = (-13);
	float dd, x;

	for (j = 0; j <= N; j++) dist[j] = 0;
	for (i = 1; i <= NPTS; i++) {
		x =  ran1(&idum) * N;
		j = (int)(x > 0 ? x + 0.5 : x - 0.5);
		//if ((j >= -NOVER2) && (j <= NOVER2)) ++dist[j + NOVER2];
		++dist[j];
	}
	printf("Uniform distribution of %6d points\n", NPTS);
	printf("%5s %10s %9s\n", "x", "p(x)", "graph:");
	for (j = 0; j <= N; j++) {
		dd = 10 * (float)dist[j] / NPTS;
		for (k = 1; k <= LLEN; k++) words[k] = ' ';
		klim = (int)(ISCAL * dd);
		if (klim > LLEN)  klim = LLEN;
		for (k = 1; k <= klim; k++) words[k] = '*';
		printf("%8.4f %8.4f  ", j / (0.2 * N) -3 , dd);
		for (k = 1; k <= LLEN; k++) printf("%c", words[k]);
		printf("\n");
	}
}

int main(void)
{
	// ran: random number generator
	printf("\n =========== Ran1 =========:\n"); ran();
	printf("\n ========= Gaussian distribution:\n"); gauss();
	return 0;
}
#undef NRANSI