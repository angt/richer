CFLAGS=-march=native -O3

main.svg: main.dat plot
	gnuplot plot > $@

main.dat: main
	./main > $@
