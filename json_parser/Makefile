json_parser: main.o lexer.o
	gcc -o json_parser main.o lexer.o

main.o: main.c lexer.h
	gcc -c main.c

lexer.o: lexer.c lexer.h
	gcc -c lexer.c

clean:
	rm -f *.o json_parser