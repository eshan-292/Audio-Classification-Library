#!/bin/bash
sudo gnuplot <<- EOF
         set terminal png
        set style fill solid 0.25 border -1
	set style boxplot nooutliers
        set boxwidth 200
        set style data boxplot 
        set output "basicMult.png"
        set title "Time  for basic multiplication"
        plot "m1basicMult.dat", \
	     "m2basicMult.dat", \
	     "m3basicMult.dat", \
	     "m4basicMult.dat", \
	     "m5basicMult.dat", \
	     "m6basicMult.dat"
        set output "pthread.png"
        set title "Time for pthread multiplication"
        plot "m1pthread.dat", \
             "m2pthread.dat", \
             "m3pthread.dat", \
	     "m4pthread.dat", \
	     "m5pthread.dat", \
	     "m6pthread.dat" 
        set output "mkl.png"
        set title "Time for mkl multiplication"
        plot "m1mkl.dat", \
	     "m2mkl.dat", \
	     "m3mkl.dat", \
	     "m4mkl.dat", \
	     "m5mkl.dat", \
	     "m6mkl.dat" 
        set output "openblas.png"
        set title "Time for openblas multiplication"
        plot "m1openblas.dat", \
	     "m2openblas.dat", \
	     "m3openblas.dat", \
	     "m4openblas.dat", \
	     "m5openblas.dat", \
	     "m6openblas.dat"
        set terminal eps   
        set style fill solid 0.25 border -1
        set style boxplot nooutliers
        set boxwidth 200
        set style data boxplot
        set output "basicMult.eps"
        set title "Time for basic multiplication"
        plot "m1basicMult.dat", \
             "m2basicMult.dat", \
             "m3basicMult.dat", \
             "m4basicMult.dat", \
             "m5basicMult.dat", \
             "m6basicMult.dat"	  
        set output "pthread.eps"
        set title "Time for pthread multiplication"
        plot "m1pthread.dat", \
             "m2pthread.dat", \
             "m3pthread.dat", \
             "m4pthread.dat", \
             "m5pthread.dat", \
             "m6pthread.dat"
        set output "mkl.eps" 
        set title "Time for mkl multiplication"
        plot "m1mkl.dat", \
             "m2mkl.dat", \
             "m3mkl.dat", \
             "m4mkl.dat", \
             "m5mkl.dat", \
             "m6mkl.dat" 
        set output "openblas.eps"
        set title "Time for openblas multiplication"
        plot "m1openblas.dat", \
             "m2openblas.dat", \
             "m3openblas.dat", \
	     "m4openblas.dat", \
	     "m5openblas.dat", \
	     "m6openblas.dat"
EOF

