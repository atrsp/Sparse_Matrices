all:
	gcc -o matrix main.c matrix.c cell.c

run: 
	make
	./matrix

clean:
	rm -f matrix
	clear

valgrind:
	make
	valgrind ./matrix