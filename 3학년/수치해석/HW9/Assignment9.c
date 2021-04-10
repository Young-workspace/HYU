#include <stdio.h>
#include <math.h>
#include "nr.h"
#include "nrutil.h"

float xi[10000], yi[10000];		// xi, yi 를 저장하는 배열
float xp[10000], yp[10000];  // xi', yi' 을 저장하는 배열
int p = 0;

void calculate()
{
	float** M = matrix(1, 3, 1, 3);				// matrix(a, b, a, b) a~b 까지로 b 포함하는 듯
	float** A = matrix(1, 3, 1, 1);
	float** B = matrix(1, 3, 1, 1);
	float *a = vector(1, 6);
	
	// M, A, B 초기화
	for (int i = 1; i < 4; i++)
	{
		for (int j = 1; j < 4; j++)
		{
			M[i][j] = 0;
		}
		A[i][1] = 0;
		B[i][1] = 0;
	}

	for (int i = 0; i < p; i++)
	{
		M[1][1] += SQR(xi[i]);
		M[1][2] += xi[i] * yi[i];
		M[1][3] += xi[i];
		M[2][2] += SQR(yi[i]);
		M[2][3] += yi[i];
		A[1][1] += xp[i] * xi[i];
		A[2][1] += xp[i] * yi[i];
		A[3][1] += xp[i];
		B[1][1] += yp[i] * xi[i];
		B[2][1] += yp[i] * yi[i];
		B[3][1] += yp[i];
	}
	M[2][1] = M[1][2];
	M[3][1] = M[1][3];
	M[3][2] = M[2][3];
	M[3][3] = 1;

	gaussj(M, 3, A, 1);

	
	gaussj(M, 3, NULL, 0);
	gaussj(M, 3, B, 1);

	//Check
	for (int i = 1; i < 4; i++)
	{
		printf("a[%d] = %f\n", i, A[i][1]);
	}

	for (int i = 1; i < 4; i++)
	{
		printf("a[%d] = %f\n", i + 3, B[i][1]);
	}
}

int main(void)
{
	//파일 읽기
	char buffer[100];
	
	//char* ptr;
	FILE* fp = fopen("fitdata3.dat", "r");

	if (fp != NULL)
	{
		while (!feof(fp))
		{
			//데이터 저장하기
			int c = fscanf(fp,"%f %f %f %f", &xi[p], &yi[p], &xp[p], &yp[p]);
			p++;
		}
		fclose(fp);
	}
	//확인하기
	/*for (int i = 0; i < p-1; i++)
	{
		printf("xi = %.2f,", xi[i]);
		printf("yi = %.2f,", yi[i]);
		printf("xp = %.2f,", xp[i]);
		printf("yp = %.2f\n\n", yp[i]);
	}*/
	
	calculate();
	
	return 0;
}