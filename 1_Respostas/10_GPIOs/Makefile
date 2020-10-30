all: lib Ex01 Ex02 Ex03

Ex01: lib Ex01.c
	gcc -c Ex01.c
	gcc Ex01.o gpio_sysfs.o -o Ex01.out

Ex02: lib Ex02.c
	gcc -c Ex02.c
	gcc Ex02.o gpio_sysfs.o -o Ex02.out

Ex03: lib Ex03.c
	gcc -c Ex03.c
	gcc Ex03.o gpio_sysfs.o -o Ex03.out

lib: gpio_sysfs.c
	gcc -c gpio_sysfs.c

clean:
	rm -rf *.out *.o
