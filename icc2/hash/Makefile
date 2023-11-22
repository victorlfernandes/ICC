OBJECTS = main.o llist.o hash.o str.o

FLAGS  = -g -Wall -Werror -Wextra -lm
VFLAGS = --leak-check=full --show-leak-kinds=all --track-origins=yes

all: $(OBJECTS)
	@gcc $(OBJECTS) -o exec $(FLAGS)

main.o: main.c llist.h
	@gcc main.c -c $(FLAGS)

llist.o: llist.c llist.h
	@gcc llist.c -c $(FLAGS)

hash.o: hash.c hash.h
	@gcc hash.c -c $(FLAGS)

str.o: str.c str.h
	@gcc str.c -c $(FLAGS)

run: all
	@./exec

valgrind: all
	@valgrind $(VFLAGS) ./exec

clean:
	@rm -rf *.o exec

zip:
	@zip hash.zip Makefile main.c llist.c llist.h hash.c hash.h str.c str.h
