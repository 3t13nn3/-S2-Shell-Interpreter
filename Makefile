CC=gcc


interpreteur:	main.o fonction.o prototype.h
	$(CC) main.o fonction.o -o interpreteur

main.o:	main.c prototype.h
	$(CC) -c main.c

fontions.o:	fonctions.c prototype.h
	$(CC) -c fonctions.c

clean:
	rm interpreteur
	rm *o
	rm *~
