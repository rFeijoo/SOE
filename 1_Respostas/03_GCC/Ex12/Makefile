Ex12: Ex11.o num_caracs.o
	gcc -o Ex12 Ex11.o num_caracs.o
Ex11.o: Ex11.c num_caracs.h
	gcc -c Ex11.c
num_caracs.o: num_caracs.c num_caracs.h
	gcc -c num_caracs.c
clean:
	rm -f *.o Ex12
