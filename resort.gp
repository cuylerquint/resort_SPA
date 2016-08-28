set output 'introduction.png'
set view 332,0

unset key; unset border; unset tics;

set ticslevel 0

set style line 1 lc rgb '#008000' lt 1 lw 2 pt 7 ps 1.5 # --- Greene
set style line 2 lc rgb '#0060ad' lt 1 lw 2 pt 7 ps 1.5 # --- Blue
set style line 3 lc rgb '#000000' lt 1 lw 2 pt 7 ps .5 # --- Black
set style line 5 lc rgb "red" # --- chair
set style line 4 lt 1 lw 1 linecolor rgb "red" # chair

set title 'Resort'
set label "1" at 0,500,0



splot 'resort.dat' using 1:2:3 with points ls 3, "chairs.dat" with lines ls 4 
