json_parser: main.o lexer.o parser.o value.o
	gcc -o json_parser main.o lexer.o parser.o value.o

main.o: main.c parser.h value.h
	gcc -c main.c

lexer.o: lexer.c lexer.h
	gcc -c lexer.c

parser.o: parser.c parser.h
	gcc -c parser.c

value.o: value.c value.h
	gcc -c value.c

clean:
	rm -f *.o json_parser