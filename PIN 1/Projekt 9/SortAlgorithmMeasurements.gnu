#!/usr/bin/gnuplot -persist
#
#    
#    	G N U P L O T
#    	Version 5.2 patchlevel 2    last modified 2017-11-15 
#    
#    	Copyright (C) 1986-1993, 1998, 2004, 2007-2017
#    	Thomas Williams, Colin Kelley and many others
#    
#    	gnuplot home:     http://www.gnuplot.info
#    	faq, bugs, etc:   type "help FAQ"
#    	immediate help:   type "help"  (plot window: hit 'h')
# set terminal qt 0 font "Sans,9"
# set output
set border 31 front lt black linewidth 1.000 dashtype solid
set ydata 
set xdata 
set boxwidth
set style fill  empty border
set format x "% h" 
set format y "% h" 
set tics back
unset grid
set style parallel front  lt black linewidth 2.000 dashtype solid
set key title "" center
set key fixed left top vertical Right noreverse enhanced autotitle columnhead nobox
set key noinvert samplen 4 spacing 1 width 0 height 0 
set key noopaque
set style textbox transparent margins  1.0,  1.0 border  lt -1 linewidth  1.0
set view 60, 30, 1, 1
set cntrlabel  format '%8.3g' font '' start 5 interval 20
set datafile separator whitespace
set size ratio 0 1,1
set origin 0,0
set style data points
set style function lines
set tics scale  1, 0.5, 1, 1, 1
set mytics default
set nomttics
set xtics border in scale 1,0.5 mirror norotate  autojustify
set xtics  norangelimit autofreq 
set ytics border in scale 1,0.5 mirror norotate  autojustify
set ytics  norangelimit autofreq 
unset ttics
set title "" 
set title  font "" norotate
set timestamp bottom 
set timestamp "" 
set timestamp  font "" norotate
set xlabel "Anzahl sortierter Daten" 
set xlabel  font "" textcolor lt -1 norotate
set xrange [ * : * ] noreverse nowriteback
set ylabel "Laufzeit in ms" 
set ylabel  font "" textcolor lt -1 rotate
set yrange [ * : * ] noreverse nowriteback
unset logscale
set zero 1e-08
set lmargin  -1
set bmargin  -1
set rmargin  -1
set tmargin  -1
set loadpath 
set fontpath 
set psdir
GNUTERM = "qt"
x = 0.0
set term push
set term pdfcairo color enhanced size 20cm,12cm
datafiles="'Ergebnis_unsortiert.txt' 'Ergebnis_vorsortiert.txt'"
do for [datafilename in datafiles]{
 prefixname=datafilename[0:strstrt(datafilename, ".")-1]
 set output prefixname."_linear.pdf"
 plot datafilename using 1:2 with linespoints pt 5, datafilename using 1:3 with linespoints pt 5, datafilename using 1:4 with linespoints pt 5, datafilename using 1:5 with linespoints pt 5 
#, #datafilename using 1:6 with linespoints pt 5,
 set output prefixname."_logscale.pdf"
 set logscale y
 replot
 set output prefixname."_loglogscale.pdf"
 set logscale x
 replot
}
set output
set term pop
#    EOF
