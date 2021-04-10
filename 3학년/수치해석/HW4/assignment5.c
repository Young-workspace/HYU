#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define NRANSI
#include "nr.h"
#include "nrutil.h"

#define NP 20
#define MP 20
#define MAXSTR 80

#define N 5

// Change file name 
char filename[] = "lineq2.dat";

//Call gaussj(), Gauss-Jordan
void gauss() {
	int j, k, l, m, n;
	float **a, **ai, **u, **b, **x, **t;
	char dummy[MAXSTR];
	FILE *fp;

	a = matrix(1, NP, 1, NP);
	ai = matrix(1, NP, 1, NP);
	u = matrix(1, NP, 1, NP);
	b = matrix(1, NP, 1, MP);
	x = matrix(1, NP, 1, MP);
	t = matrix(1, NP, 1, MP);
	//if ((fp = fopen("lineq1.dat", "r")) == NULL)
	if((fp = fopen(filename, "r")) == NULL)
		nrerror("Data file %s not found\n", filename);
	while (!feof(fp)) {
		fscanf(fp, "%d %d ", &n, &m);
		for (k = 1; k <= n; k++)
			for (l = 1; l <= n; l++) fscanf(fp, "%f ", &a[k][l]);
		//fgets(dummy, MAXSTR, fp);
		for (l = 1; l <= m; l++)
			for (k = 1; k <= n; k++) fscanf(fp, "%f ", &b[k][l]);
		
		
		
		/* save matrices for later testing of results */
		for (l = 1; l <= n; l++) {
			for (k = 1; k <= n; k++) ai[k][l] = a[k][l];
			for (k = 1; k <= m; k++) x[l][k] = b[1][k];
		}
		/* invert matrix */
		gaussj(ai, n, x, m);
		
		printf("original matrix:\n");
		for (k = 1; k <= n; k++) {
			for (l = 1; l <= n; l++) printf("%12.6f", a[k][l]);
			printf("\n");
		}

		printf("\nInverse of matrix a : \n");
		for (k = 1; k <= n; k++) {
			for (l = 1; l <= n; l++) printf("%12.6f", ai[k][l]);
			printf("\n");
		}

		/* check inverse */
		printf("\na times a-inverse:\n");
		for (k = 1; k <= n; k++) {
			for (l = 1; l <= n; l++) {
				u[k][l] = 0.0;
				for (j = 1; j <= n; j++)
					u[k][l] += (a[k][j] * ai[j][l]);
			}
			for (l = 1; l <= n; l++) printf("%12.6f", u[k][l]);
			printf("\n");
		}
		
		printf("***********************************\n");
		printf("press RETURN for next problem:\n");
		(void)getchar();
	}
	fclose(fp);
	free_matrix(t, 1, NP, 1, MP);
	free_matrix(x, 1, NP, 1, MP);
	free_matrix(b, 1, NP, 1, MP);
	free_matrix(u, 1, NP, 1, NP);
	free_matrix(ai, 1, NP, 1, NP);
	free_matrix(a, 1, NP, 1, NP);
}

//Call ludcmp(), LU Decomposition
void lu() {
	int j, k, l, m, n, dum, *indx, *jndx;
	float d, **a, **xl, **xu, **x;
	char dummy[MAXSTR];
	FILE *fp;

	indx = ivector(1, NP);
	jndx = ivector(1, NP);
	a = matrix(1, NP, 1, NP);
	xl = matrix(1, NP, 1, NP);
	xu = matrix(1, NP, 1, NP);
	x = matrix(1, NP, 1, NP);
	//if ((fp = fopen("lineq1.dat", "r")) == NULL)
	if ((fp = fopen(filename, "r")) == NULL)
		nrerror("Data file %s not found\n", filename);
	while (!feof(fp)) {
		fscanf(fp, "%d %d ", &n, &m);
		
		for (k = 1; k <= n; k++) {
			for (l = 1; l <= n; l++) fscanf(fp, "%f ", &a[k][l]);
		}
		for (l = 1; l <= m; l++)
			for (k = 1; k <= n; k++) fscanf(fp, "%f ", &x[k][l]);
		/* Print out a-matrix for comparison with product of
		   lower and upper decomposition matrices */
		printf("original matrix:\n");
		for (k = 1; k <= n; k++) {
			for (l = 1; l <= n; l++) printf("%12.6f", a[k][l]);
			printf("\n");
		}
		/* Perform the decomposition */
		ludcmp(a, n, indx, &d);
		/* Compose separately the lower and upper matrices */
		for (k = 1; k <= n; k++) {
			for (l = 1; l <= n; l++) {
				if (l > k) {
					xu[k][l] = a[k][l];
					xl[k][l] = 0.0;
				}
				else if (l < k) {
					xu[k][l] = 0.0;
					xl[k][l] = a[k][l];
				}
				else {
					xu[k][l] = a[k][l];
					xl[k][l] = 1.0;
				}
			}
		}
		/* Compute product of lower and upper matrices for
		   comparison with original matrix */
		for (k = 1; k <= n; k++) {
			jndx[k] = k;
			for (l = 1; l <= n; l++) {
				x[k][l] = 0.0;
				for (j = 1; j <= n; j++)
					x[k][l] += (xl[k][j] * xu[j][l]);
			}
		}
		printf("\n%s%s\n", "product of lower and upper ",
			"matrices (rows unscrambled):");
		for (k = 1; k <= n; k++) {
			dum = jndx[indx[k]];
			jndx[indx[k]] = jndx[k];
			jndx[k] = dum;
		}
		for (k = 1; k <= n; k++)
			for (j = 1; j <= n; j++)
				if (jndx[j] == k) {
					for (l = 1; l <= n; l++)
						printf("%12.6f", x[j][l]);
					printf("\n");
				}
		printf("\nlower matrix of the decomposition:\n");
		for (k = 1; k <= n; k++) {
			for (l = 1; l <= n; l++) printf("%12.6f", xl[k][l]);
			printf("\n");
		}
		printf("\nupper matrix of the decomposition:\n");
		for (k = 1; k <= n; k++) {
			for (l = 1; l <= n; l++) printf("%12.6f", xu[k][l]);
			printf("\n");
		}
		printf("\n***********************************\n");
		printf("press return for next problem:\n");
		(void)getchar();
	}
	fclose(fp);
	free_matrix(x, 1, NP, 1, NP);
	free_matrix(xu, 1, NP, 1, NP);
	free_matrix(xl, 1, NP, 1, NP);
	free_matrix(a, 1, NP, 1, NP);
	free_ivector(jndx, 1, NP);
	free_ivector(indx, 1, NP);
}

//Call svdcmp(), Singular Value Decomposition
void single() {
	int j, k, l, m, n;
	float *w, **a, **u, **v;
	char dummy[MAXSTR];
	FILE *fp;

	w = vector(1, NP);
	a = matrix(1, MP, 1, NP);
	u = matrix(1, MP, 1, NP);
	v = matrix(1, NP, 1, NP);
	/* read input matrices */
	//if ((fp = fopen("lineq1.dat", "r")) == NULL)
	if ((fp = fopen(filename, "r")) == NULL)
		nrerror("Data file %s not found\n", filename);
	while (!feof(fp)) {
		fscanf(fp, "%d %d ", &n, &m);
		/* copy original matrix into u */
		for (k = 1; k <= m; k++)
			for (l = 1; l <= n; l++) {
				fscanf(fp, "%f ", &a[k][l]);
				u[k][l] = a[k][l];
			}
		fgets(dummy, MAXSTR, fp);
		
		/* perform decomposition */
		svdcmp(u, m, n, w, v);
		/* write results */
		printf("Decomposition matrices:\n");
		printf("Matrix u\n");
		for (k = 1; k <= m; k++) {
			for (l = 1; l <= n; l++)
				printf("%12.6f", u[k][l]);
			printf("\n");
		}
		printf("\n");
		printf("Diagonal of matrix w\n");
		for (k = 1; k <= n; k++)
			printf("%12.6f", w[k]);
		printf("\n");
		printf("\nMatrix v-transpose\n");
		for (k = 1; k <= n; k++) {
			for (l = 1; l <= n; l++)
				printf("%12.6f", v[l][k]);
			printf("\n");
		}
		printf("\nCheck product against original matrix:\n");
		printf("Original matrix:\n");
		for (k = 1; k <= m; k++) {
			for (l = 1; l <= n; l++)
				printf("%12.6f", a[k][l]);
			printf("\n");
		}
		printf("\n");
		printf("Product u*w*(v-transpose):\n");
		for (k = 1; k <= m; k++) {
			for (l = 1; l <= n; l++) {
				a[k][l] = 0.0;
				for (j = 1; j <= n; j++)
					a[k][l] += u[k][j] * w[j] * v[l][j];
			}
			for (l = 1; l <= n; l++) printf("%12.6f", a[k][l]);
			printf("\n");
		}
		printf("***********************************\n");
		printf("press RETURN for next problem\n");
		(void)getchar();
	}
	fclose(fp);
	free_matrix(v, 1, NP, 1, NP);
	free_matrix(u, 1, MP, 1, NP);
	free_matrix(a, 1, MP, 1, NP);
	free_vector(w, 1, NP);
}

//Call mprove()
void prove() {
	int i, j, *indx, n, m;
	long idum = (-13);
	float d, *x, **a, **aa, *b;
	FILE *fp;

	a = matrix(1, NP, 1, NP);
	indx = ivector(1, NP);
	x = vector(1, NP);
	aa = matrix(1, NP, 1, NP);
	b = vector(1, NP);
	if ((fp = fopen(filename, "r")) == NULL)
		nrerror("Data file %s not found\n", filename);
	while (!feof(fp)) {
		fscanf(fp, "%d %d ", &n, &m);
		for (i = 1; i <= n; i++) {
			for (j= 1; j <= n; j++) fscanf(fp, "%f ", &a[i][j]);
		}
		for (i = 1; i <= n; i++) fscanf(fp, "%f ", &b[i]);

		printf("original matrix:\n");
		for (i = 1; i <= n; i++) {
			for (j = 1; j <= n; j++) printf("%12.6f", a[i][j]);
			printf("\n");
		}

		printf("RHV\n");
		for (int i = 1; i <= n; i++) printf("%12.6f", b[i]);
		printf("\n");

		for (i = 1; i <= n; i++) {
			x[i] = b[i];
			for (j = 1; j <= n; j++) aa[i][j] = a[i][j];
		}
		ludcmp(aa, n, indx, &d);
		lubksb(aa, n, indx, x);
		printf("\nSolution vector for the equations:\n");
		for (i = 1; i <= n; i++) printf("%12.6f", x[i]);
		printf("\n");
		/* now phoney up x and let mprove fix it */
		for (i = 1; i <= n; i++) x[i] *= (1.0 + 0.2*ran3(&idum));
		printf("\nSolution vector with noise added:\n");
		for (i = 1; i <= n; i++) printf("%12.6f", x[i]);
		printf("\n");
		mprove(a, aa, n, indx, b, x);
		printf("\nSolution vector recovered by mprove:\n");
		for (i = 1; i <= n; i++) printf("%12.6f", x[i]);
		printf("\n");
		free_matrix(aa, 1, NP, 1, NP);
		free_vector(x, 1, NP);
		free_ivector(indx, 1, NP);

	}

}

int main() {
	
	printf("================== gauss ==================\n");
	gauss();
	printf("\n================== lu ==================\n");
	lu();
	printf("\n================== single ==================\n");
	single();
	printf("\n================== prove ==================\n");
	prove();
	return 0;
}
#undef NRANSI