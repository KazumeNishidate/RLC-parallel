# RLC-parallel

This code solves the RLC parallel circuit using GSL. 
The system parameters are L=47mH, C=47 nF, Is=5 A, and R=20 kohm. 

Use the following command to compile:
  gcc rlc-parallel.c -o rlc-parallel -lgsl -lgslcblas -lm

See the Figure on p.15 of the text:
https://ocw.mit.edu/courses/6-071j-introduction-to-electronics-signals-and-measurement-spring-2006/a929d33896839a7bf1ca2631cd87e711_16_transint_rlc2.pdf

kazume.nishidate@gmail.com
