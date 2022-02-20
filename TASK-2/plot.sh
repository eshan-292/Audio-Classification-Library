#!/bin/bash
sudo gnuplot <<- EOF
         set terminal png
        set style fill solid 0.25 border -1
        set style boxplot outliers pointtype 7
        set boxwidth 200
        set style data boxplot
        set output "basicMultBoxPlot.png"
        set title "Time for basic multiplication"
        plot "basicMultBox.dat"
        set output "pthreadMultBoxPlot.png"
        set title "Time for pthread multiplication"
        plot "pthreadMultBox.dat" 
        set yrange[0:0.01] 
        set output "mklMultBoxPlot.png"
        set title "Time for mkl multiplication"
        plot "mklMultBox.dat" 
        set output "openBlasMultBoxPlot.png"
        set title "Time for openblas multiplication"
        plot "openBlasMultBox.dat"
	    set terminal eps   
        set style fill solid 0.25 border -1
        set style boxplot outliers pointtype 7
        set boxwidth 200
        set style data boxplot
        set yrange[0:1] 
        set output "basicMultBoxPlot.eps"
        set title "Time for basic multiplication"
        plot "basicMultBox.dat"
        set output "pthreadMultBoxPlot.eps"
        set title "Time for pthread multiplication"
        plot "pthreadMultBox.dat"
        set yrange[0:0.01] 
        set output "mklMultBoxPlot.eps" 
        set title "Time for mkl multiplication"
        plot "mklMultBox.dat"
        set output "openBlasMultBoxPlot.eps"
        set title "Time for openblas multiplication"
        plot "openBlasMultBox.dat"

EOF
