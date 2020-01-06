CFLAGS=-march=native -O3

make: main.dat plot
	gnuplot plot > main.svg

main.dat: main
	./main > main.dat
