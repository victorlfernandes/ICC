OBJECTS = main.o mine_sweeper.o

FLAGS  = -g -Wall -Werror -Wextra
VFLAGS = --leak-check=full --show-leak-kinds=all --track-origins=yes

all: $(OBJECTS)
	@gcc $(OBJECTS) -o exec $(FLAGS)

$(OBJECTS): mine_sweeper.h

run: 
	@./exec

valgrind: all
	@valgrind $(VFLAGS) ./exec

clean:
	@rm -rf *.o exec

zip:
	@zip mine_sweeper.zip Makefile main.c mine_sweeper.c mine_sweeper.h
