all:
	gcc -o matrix main.c matrix.c cell.c

run: 
	make
	./matrix bin

clean:
	rm -f matrix
	rm -f bin
	clear

valgrind:
	make
	valgrind -s --leak-check=full ./matrix bin