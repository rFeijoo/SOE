all: Ex01.out Ex02.out Ex03.out Ex06.out Ex07.out bib_arqs
Ex01.out: Ex01.c
	gcc Ex01.c -o Ex01.out
Ex02.out: Ex02.c
	gcc Ex02.c -o Ex02.out
Ex03.out: Ex03.c
	gcc Ex03.c -o Ex03.out
Ex06.out: Ex06.c bib_arqs.h bib_arqs
	gcc -c Ex06.c
	gcc Ex06.o bib_arqs.o -o Ex06.out
Ex07.out: Ex07.c bib_arqs.h bib_arqs
	gcc -c Ex07.c
	gcc Ex07.o bib_arqs.o -o Ex07.out
bib_arqs: bib_arqs.c bib_arqs.h
	gcc -c bib_arqs.c
clean:
	rm -f *.out *.bin *.txt *.o
