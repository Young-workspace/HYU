#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double get_eps();


int main()
{
	double ans;
	ans = get_eps();
	printf("machine accuracy: %f\n", ans);
	printf("machine accuracy .17f: %.17f\n", ans);
	return 0;
}

double get_eps()
{
	double eps, result;
	eps = 1;
	while ((1 + eps) != 1)
	{
		result = eps;
		eps /= 2;
	}

	return result;
}

