
#include <math.h>
#define MAXIT 3

int c_muller = 0;
float muller(void(*funcd)(float, float *, float *), float x1, float x2,
	float xacc)
{
	
	void nrerror(char error_text[]);
	int j;
	float x3;
	float h0, h1;
	float d0, d1, a, b, c;
	x3 = (x1 + x2) / 2;
	float fn, rad, den;
	float dx, xr;


	for (j = 1; j <= MAXIT; j++) {
		h0 = x2 - x1;
		h1 = x3 - x2;
		(*funcd)(x2, &fn, &d0);

		(*funcd)(x3, &fn, &d1);
		a = (d1 - d0) / (h1 + h0);
		
		b = a * h1 + d1;
		c = fn;
		rad = sqrt(b*b - 4 * a*c);
		if (fabs(b + rad) > fabs(b - rad)) {
			den = b + rad;
		}
		else {
			den = b - rad;
		}

		dx = -2 * c / den;
		xr = x3 + dx;
		if (fabs(dx) < xacc || j >= MAXIT) {
			//nrerror("maximum number of iterations exceeded in muller");
			printf("count: %d\n", c_muller);
			return xr;
		}
		x1 = x2;
		x2 = x3;
		x3 = xr;
		c_muller++;

	}
	
	return 0.0;
}
#undef MAXIT
