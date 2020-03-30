Ex10: Ex09.o num_caracs.o
	gcc -o Ex10 Ex09.o num_caracs.o
Ex09.o: Ex09.c num_caracs.h
	gcc -c Ex09.c
num_caracs.o: num_caracs.c num_caracs.h
	gcc -c num_caracs.c
clean:
	rm -f *.o Ex10
