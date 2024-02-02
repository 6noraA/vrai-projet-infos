set terminal png
    
    set xlabel "TOWN NAMES" font "Arial,7"
    set ylabel "NB ROUTES" font "Arial,7"
    set title "Option -t : Nb routes = f(Towns)" font "Arial,8"
    set style data histograms
    set output 't.png'
    set style fill solid border -1
    set boxwidth 0.5
    SkyBlue = "#87CEEB"
    DarkBlue = "#00008B"
    set datafile separator ";"
    set yrange [0:*]
    set ytics font "Arial,7"
    set xtics font "Arial,7"
    set xtics rotate by -45  # Incliner les étiquettes sur l'axe x de 45 degrés
    set key font "Arial,8"  # Changer la taille de la légende
    plot "./temp/temp2.txt" using 2:xtic(1) lc rgb SkyBlue title "Total routes", '' using 3 lc rgb DarkBlue title "First Town"
