#include <math.h>
#include <stdlib.h>
#include <stdio.h>

/* psfx.c: point-spread function (PSF) generator for 1D convolution.
 *
 * Originally "gauss()" was part of convolve.c, the convolution routine
 * from read5. Here made into a generic 1D PSF code for general use,
 * for example in line broadening of spectra.
 *
 * Copyright (c) G.S.Stachowski 1993-2003
 * 
 * ---------------------------------------------------------------------
 *
 * Example of calling code, here with "gauss" as the psf function:
 *  
 * double *gauss(double s, long SIZE_DATA, long map_proj_size);
 *  
 * double *conv_drvr(double *projection, double beam, long SIZE_DATA) {
 *         double *ans;
 *         convolve(projection, gauss(beam, SIZE_DATA), ans, SIZE_DATA);
 *         free(gauss);
 *         return(ans);
 * }
 *
 * ---------------------------------------------------------------------
 *
 * 2003.04.14:
 * - malloc changed to calloc (clears memory after allocation).
 * - conversion to Angstroms as unit specyfing width of broadening.
 * - added line rotation psf.
 *
 */ 

#define SIZE_DATA          n
#define SPEED_OF_LIGHT_KMS 299.792458

/* f[SIZE_DATA]: original function, */
/* g[SIZE_DATA]: centred PSF,       */
/* h[SIZE_DATA]: result.            */        

/* Gaussian PDF */ 

double *gauss(double s, long SIZE_DATA, long map_proj_size) {
	double *g;
	long    i;
	double  m, sum=0;
	
	/*FILE *outf;*/
		
	printf("# gauss: %5.4lf ", s);
	
	s = (double)map_proj_size/(double)SIZE_DATA*s/sqrt(-8*log(0.5));
	
	m = 0.5; 
	
	g = (double *)calloc(SIZE_DATA,sizeof(*g));
	
	for (i=0;i<SIZE_DATA;i++) {
		g[i] = exp(-0.5*pow(((double)i/SIZE_DATA-m)/s,2))/(sqrt(2*M_PI)*s);
		sum  += g[i];
	}
	for (i=0;i<SIZE_DATA;i++) {
		g[i] = g[i]/sum;
	}
	printf(" n=%ld\tsigma=%lf, sum=%lf\n",SIZE_DATA,s,sum);

/*	outf = fopen("gauss", "wt");
	setvbuf(outf, (char *)NULL, _IONBF, 0);
	for(i=0;i<SIZE_DATA;i++) {
		fprintf(outf, "%le\t%le\n",(double)i/SIZE_DATA,*(g+i));
	}
	fclose(outf);
*/
	return(g);
}	

double *line_rotation(double velocity, long SIZE_DATA, double dl) {

	/* dl: wavelength step size in Angstroms
	 */ 

	const double c = SPEED_OF_LIGHT_KMS;

	double *g, a;
	long    i;
	
	g = (double *)calloc(SIZE_DATA,sizeof(*g));

	a = (c*c*dl*dl)/(velocity*velocity);

	for (i=0;i<SIZE_DATA;i++) {
	        g[i] = sqrt((1.0-(csq/vsq)*(vsq*fsq))); 
                sum  += g[i];
        }
        for (i=0;i<SIZE_DATA;i++) {
                g[i] = g[i]/sum;
        }


}
