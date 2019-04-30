output: main.o
	gcc -std=c89 -pedantic-errors main.o -o exe
main.o: main.c
	gcc -std=c89 -pedantic-errors -c main.c
clean:
	rm main.o exe
