all:
	gcc -Wall -Werror -Wextra cp_fuga.c -c
	gcc -Wall -Werror -Wextra main.c -c

	gcc cp_fuga.o main.o -o exec

run:
	./exec < teste_fuga/1.in

valgrind: clean all
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./exec < teste_fuga/1.in

clean: 
	rm -rf *.o exec