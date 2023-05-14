FLAGS = -c -Wall

COMPILED = compiled

LIBRARY = -I tarefas -L . -ltads -lm

all: 
	gcc -c cell.c matrix.c
	
#make experimental

%.o: 
	mkdir $(COMPILED)
	gcc $(FLAGS) tads/palavras.c -o $(COMPILED)/palavras.o
	gcc $(FLAGS) tads/documentos.c -o $(COMPILED)/documentos.o
	gcc $(FLAGS) tads/propriedades.c -o $(COMPILED)/propriedades.o
	gcc $(FLAGS) tads/indices.c -o $(COMPILED)/indices.o
	
run: 
	make
	./main

clean:
	rm main
	rm %.o
	clear

valgrind:
	make
#	valgrind --leak-check=full --show-leak-kinds=all ./indexador datasets/medium-small/test.txt binario.bin
	valgrind --leak-check=full --show-leak-kinds=all ./principal binario.bin 10

gdb:
	make
	gdb ./main datasets/medium-small/test.txt binario.bin 