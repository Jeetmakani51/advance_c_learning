hash_table: main.o hash_table.o entry.o
	gcc -o hash_table main.o hash_table.o entry.o

main.o: main.c hash_table.h
	gcc -c main.c

hash_table.o: hash_table.c hash_table.h entry.h
	gcc -c hash_table.c

entry.o: entry.c entry.h
	gcc -c entry.c

clean:
	rm -f *.o hash_table