set terminal svg

set multiplot layout 2, 1
set tmargin 5

set title "Number of agents richer than at the start"
plot 'main.dat' using 1:2 with line lt -1 lw 1 notitle

set title "The fortune of the richest one (% of the total)"
plot 'main.dat' using 1:3 with line lt -1 lw 1 notitle

unset multiplot
