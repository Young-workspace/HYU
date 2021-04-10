#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float get_eps();


int main()
{
	float ans;
	ans = get_eps();
	printf("machine accuracy: %f\n", ans);
	printf("machine accuracy .8f: %.8f\n", ans);
	return 0;
}

float get_eps()
{
	float eps, result;
	eps = 1;
	while ((1 + eps) != 1)
	{
		result = eps;
		eps /= 2;
	}
	
	return result;
}

