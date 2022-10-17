check : minimal.c
	@gcc -Wall -o minimal minimal.c
	@rm -rf minimal
	@echo "Check warning and error OK"
build : minimal.c
	@gcc -Wall -o minimal minimal.c
	@echo "Build OK"
clean : 
	@rm -rf minimal main.c
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
