progetto :main2.o libreria.o
	gcc -std=gnu89 -pedantic -Wall main2.o libreria.o -oprogetto
libreria.o : funzioni.c libreria.h
	gcc -c --ansi funzioni.c -olibreria.o
main2 : main2.c libreria.h
	gcc -c --ansi main2.c -o main2.o
clear : 
	rm main2.o 
	rm libreria.o
	rm progetto	
	rm output.txt
	