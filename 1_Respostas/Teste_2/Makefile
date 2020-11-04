all: Ex01 Ex02 Ex03 Ex04 Ex05 Ex06

Ex01: Ex01.c
	gcc Ex01.c -o Ex01.out -lwiringPi

lib: gpio_sysfs.c
	gcc -c gpio_sysfs.c

Ex02: Ex02.c
	gcc Ex02.c -o Ex02.out

Ex03: Ex03.c
	gcc Ex03.c -o Ex03.out -lwiringPi

Ex04: Ex04.c
	gcc Ex04.c -o Ex04.out

Ex05: Ex05.c
	gcc Ex05.c -o Ex05.out -lwiringPi

Ex06: Ex06.c
	gcc Ex06.c -o Ex06.out -lwiringPi

clean:
	rm -f *.out