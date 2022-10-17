check : minimal.c dataset.c parameters.c
	@gcc -Wall -c dataset.c parameters.c util.c minimal.c
	@gcc -Wall -o minimal minimal.o dataset.o util.o parameters.o
	@rm -rf minimal
	@echo "Check warning and error OK"
build : minimal.c dataset.c parameters.c
	@gcc -Wall -c dataset.c parameters.c util.c minimal.c
	@gcc -Wall -o minimal minimal.o dataset.o util.o parameters.o
	@echo "Build OK"
clean : 
	@rm -rf minimal main.c main.h *.o createNewFile.h
	@echo "clean OK"
test :
	@./minimal -f "x.h"
	@more x.h
	@rm -rf x.h
