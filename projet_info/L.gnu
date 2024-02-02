set terminal png size 1000,1000
set output 'L.png'
set title '  Option -I Dstance = f(Route) '
set style fill solid 
set boxwidth 0.5
 
# Configuration des axes  
set xrange [0:*] 
set yrange [0:*] 
# nom des axes

set ylabel 'distance (km)' 
set xlabel 'route id' 

set xtics nomirror rotate by 360 font '1' offset -3.0,-0.2
set ytics nomirror rotate by 360 
set offset 0.5,0,0,0

plot "resultatsL.txt" using 2:xtic(1) with boxes lc rgb "green" notitle

