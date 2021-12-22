# convolve
Fast 1D convolution and Gaussian PSF in C without using Fourier Transforms

convolvx.c: fast 1D convolution
-------------------------------

Originally convolve.c from read5, here stripped to just the
convolution function, without the profile (gaussian) generator.
The convolution was hand-optimised for the read5 code and is
pretty quick, but does require the profile (PSF) to be the
same size as the source and result functions (this eliminates
boundary checking and makes it much faster). This should not
be a problem however.

The original unoptimised code has been left in comments for
reference - it is actually pretty quick too, and is easier
to visualise (it also requires same-sized arrays).
The optimisation splits the loop in two, thus taking the
if statement outside.

Speed is particularly important if the convolution is repeated
many times, as it was in read5 (in a Monte-Carlo simulation)
or as part of a Lucy-Richardson iterative deconvolution process.
(This code is in fact derived from code for a 1D L-R program.)


psfx.c: point-spread function (PSF) generator for 1D convolution
----------------------------------------------------------------

Originally "gauss()" was part of convolve.c, the convolution routine
from read5. Here made into a generic 1D PSF code for general use,
for example in line broadening of spectra.


Copyright (c) G.S.Stachowski 1999-2003

