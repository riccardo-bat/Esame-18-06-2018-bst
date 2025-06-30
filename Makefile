#Variabili utili per le regole
CC = gcc
CFLAGS = -Wall


#Regole

#regola di default - generazione esame.exe
esame: compito.o carta.o bst.o
	$(CC) $(CFLAGS) -o $@ $^ 
	del /F *.out *.o *.gch 

#Regole per la generazione dei file oggetto
compito.o: compito.c tipo_inf.h carta.h bst.h
	$(CC) $(CFLAGS) -c $^

carta.o: carta.c carta.h tipo_inf.h 
	$(CC) $(CFLAGS) -c $^

bst.o: bst.c bst.h tipo_inf.h 
	$(CC) $(CFLAGS) -c $^


clean: 
	del /F *.out *.o *.gch *.exe

.PHONY: clean