CFLAGS=-Wall -Werror -Wextra
CHECK=-lcheck -lsubunit -lm -lrt -lpthread
GCOV_FLAGS=-fprofile-arcs -ftest-coverage
NAME_FILE=net

all:
	make clean
	make $(NAME_FILE)
	./$(NAME_FILE) 192.168.1.1 128 100
	./$(NAME_FILE) 192.168.1.1 128.0.0.0
	./$(NAME_FILE) 192.168.1.1 128.0.0.0 -2
	./$(NAME_FILE) 192...1 128.0.0.0 1000
	./$(NAME_FILE) 192.168.1.1 128.0.0.0 777
	./$(NAME_FILE) 192.168.1.1 255.255.255.255 100
	./$(NAME_FILE) 192.168.1.1 0.0.0.0 100
	make clean

$(NAME_FILE):
	gcc $(CFLAGS) -c $(NAME_FILE)_source.c $(NAME_FILE)_main.c -lm
	gcc $(NAME_FILE)_source.o $(NAME_FILE)_main.o -o $(NAME_FILE) -lm

memory:
	gcc $(CFLAGS) -c $(NAME_FILE)_source.c $(NAME_FILE)_main.c -lm
	gcc $(NAME_FILE)_source.o $(NAME_FILE)_main.o -o $(NAME_FILE) -lm
	valgrind ./$(NAME_FILE) 192.168.1.1 128.0.0.0 500

clean:
	rm -rf $(NAME_FILE) testing *.gcda *.gcno *info *.o