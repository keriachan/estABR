CC=gcc
CFLAGS=-std=c17 -pedantic -Wall
LDLIBS=

abr: main.o arbre_binaire.o est_ABR.o genere_arbre_binaire.o
	$(CC) -o $@ $^ $(LDLIBS)

main.o: main.c arbre_binaire.h est_ABR.h
arbre_binaire.o: arbre_binaire.c arbre_binaire.h
genere_arbre_binaire.o: genere_arbre_binaire.c genere_arbre_binaire.h arbre_binaire.h
est_ABR.o: est_ABR.c est_ABR.h arbre_binaire.h

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<
	
clean:
	rm -f *.o abr