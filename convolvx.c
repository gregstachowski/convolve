#include <math.h>

/* convolvx.c: fast 1D convolution. 
 *
 * Originally convolve.c from read5, here stripped to just the
 * convolution function, without the profile (gaussian) generator.
 * The convolution was hand-optimised for the read5 code and is
 * pretty quick, but does require the profile (PSF) to be the 
 * same size as the source and result functions (this eliminates
 * boundary checking and makes it much faster). This should not
 * be a problem however. 
 *
 * The original unoptimised code has been left in comments for 
 * reference - it is actually pretty quick too, and is easier 
 * to visualise (it also requires same-sized arrays). 
 * The optimisation splits the loop in two, thus taking the 
 * if statement outside.
 *
 * Speed is particularly important if the convolution is repeated
 * many times, as it was in read5 (in a Monte-Carlo simulation) 
 * or as part of a Lucy-Richardson iterative deconvolution process.
 * (This code is in fact derived from code for a 1D L-R program.)
 *
 * Copyright (c) G.S.Stachowski 1999-2003
 */

#define SIZE_DATA n

/* f[SIZE_DATA]: original function, */
/* g[SIZE_DATA]: centred PSF,       */
/* h[SIZE_DATA]: result.            */        

/* Generic convolution */		 

void convolve(double *f, double *g, double *h, long SIZE_DATA) {
	long    i, m, half, ih;
/*	long	jmin, jmax;*/
	
	half=SIZE_DATA/2;

	/*for (i=0;i<SIZE_DATA;i++) {
		*(h+i) = 0;
		ih = i-half;
		if ( ih < 0 ) {
			jmin=0; 
			jmax=SIZE_DATA+ih;
		} else {
			jmin=ih;
			jmax=SIZE_DATA;
		}
		for (m=jmin;m<jmax;m++) {
			*(h+i)+=*(f+m)*(*(g+m-ih));
		}
	}*/
        for (i=0;i<half;i++) {
                *(h+i) = 0;
                ih = i-half;
                for (m=0;m<SIZE_DATA+ih;m++) {
                        *(h+i)+=*(f+m)*(*(g+m-ih));
                }
        }
        for (i=half;i<SIZE_DATA;i++) {
                *(h+i) = 0;
                ih = i-half;
                for (m=ih;m<SIZE_DATA;m++) {
                        *(h+i)+=*(f+m)*(*(g+m-ih));
                }
        }
}

/* Example of calling code, here with "gauss" as the psf function.
 * gauss prototype:  
 * 	double *gauss(double s, long SIZE_DATA, long map_proj_size)
 */

/* Generate parameters and do convolution */
/*
double *conv_drvr(double *projection, double beam, long SIZE_DATA) {
	double *ans;
	convolve(projection, gauss(beam, SIZE_DATA), ans, SIZE_DATA);
	free(gauss);
	return(ans);
}	
*/
