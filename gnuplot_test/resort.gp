set hidden3d
set output 'introduction.png'
set view 332,0
unset key; unset border; unset tics;
set ticslevel 0

set style line 2 lc rgb '#dd181f' lt 1 lw 2 pt 5 ps 1.5   # --- chair 

set title 'Resort'
set label "1" at 0,500,0






splot 'resort.dat' with linespoints ls 2 
