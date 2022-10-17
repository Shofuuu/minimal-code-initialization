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
	@rm -rf minimal main.c main.h *.o
	@echo "clean OK"
test :
	@./minimal -h
	@echo "test 1 OK"
	@./minimal -f "main.c"
	@more main.c
	@echo "test 2 OK"
	@./minimal -f "main.c" -a "Shofuwan"
	@more main.c
	@echo "test 3 OK"
	@rm -rf main.c
