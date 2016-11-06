set output 'introduction.png'
set view 307,6

unset key; unset border; unset tics;

set ticslevel 0

set style line 1 lt 1 lw 1 linecolor rgb "green" # easy
set style line 2 lt 1 lw 1 linecolor rgb "blue"  # med
set style line 3 lt 1 lw 1 pt 7 ps .5 linecolor rgb "black" # expert
set style line 4 lt 1 lw 1 linecolor rgb "red"   # chair
set style line 5 lt 1 lw 1 linecolor rgb "gray"  # env
set style line 6 lt 1 lw 1 linecolor rgb "yellow" # route


set title 'Resort'
set label "1" at 0,500,0


#"chairs.dat" with lines ls 4, \

splot 'resort.dat' using 1:2:3 with points ls 3, \
"easy.dat" with lines ls 1, \
"med.dat" with lines ls 2, \
"expert.dat" with lines ls 3, \
"suggested.dat" with lines ls 6, \
"env.dat" with lines ls 5
