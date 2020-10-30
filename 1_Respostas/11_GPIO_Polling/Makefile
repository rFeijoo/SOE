all: lib Ex01

Ex01: lib Ex01.c
	gcc -c Ex01.c
	gcc Ex01.o gpio_sysfs.o -o Ex01.out

lib: gpio_sysfs.c
	gcc -c gpio_sysfs.c

clean:
	rm -rf *.out *.o
