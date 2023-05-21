all:
	gcc -o matrix main.c matrix.c cell.c

run: 
	make
	./matrix bin

clean:
	rm -f matrix
	rm -f bin
	rm -f convolution
	clear

valgrind:
	make
	valgrind -s --leak-check=full ./matrix bin

convolution:
	gcc -o convolution convolution.c matrix.c cell.c
	./convolution