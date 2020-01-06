CFLAGS=-march=native -O3

make: main.dat
	gnuplot plot > main.svg

main.dat: main
	./main > main.dat
