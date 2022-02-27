run :compileMain compileHelper
	gcc -std=gnu89 -pedantic -Wall ./modules/main2.o ./modules/libreria.o -o minefield
	rm ./modules/main2.o
	rm ./modules/libreria.o
	rmdir ./modules
	./minefield
compileHelper : minefieldHelper.c minefieldHelper.h
	gcc -c --ansi minefieldHelper.c -o  ./modules/libreria.o
compileMain : minefield.c minefieldHelper.h
	mkdir ./modules
	gcc -c --ansi minefield.c -o ./modules/main2.o
uninstall :
	rm progetto
	rm output.txt