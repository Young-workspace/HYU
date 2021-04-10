
#include <math.h>
#define MAXIT 40

int c_rtsec = 0;
float rtsec(float (*func)(float), float x1, float x2, float xacc)
{
	void nrerror(char error_text[]);
	int j;
	float fl,f,dx,swap,xl,rts;

	fl=(*func)(x1);
	f=(*func)(x2);
	if (fabs(fl) < fabs(f)) {
		rts=x1;
		xl=x2;
		swap=fl;
		fl=f;
		f=swap;
	} else {
		xl=x1;
		rts=x2;
	}
	for (j=1;j<=MAXIT;j++) {
		dx=(xl-rts)*f/(f-fl);
		xl=rts;
		fl=f;
		rts += dx;
		f=(*func)(rts);
		if (fabs(dx) < xacc || f == 0.0) { 
			printf("count: %d\n", c_rtsec-1);
			return rts; 
		}
		c_rtsec++;
	}
	nrerror("Maximum number of iterations exceeded in rtsec");
	return 0.0;
}
#undef MAXIT
