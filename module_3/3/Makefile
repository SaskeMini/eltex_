CFLAGS=-Wall -Werror -Wextra
CHECK=-lcheck -lsubunit -lm -lrt -lpthread
GCOV_FLAGS=-fprofile-arcs -ftest-coverage
NAME_FILE=message

all:
	make clean
	make $(NAME_FILE)
	./$(NAME_FILE) my_queue
	make clean

$(NAME_FILE):
	gcc $(CFLAGS) -c $(NAME_FILE)_source.c $(NAME_FILE)_main.c
	gcc $(NAME_FILE)_source.o $(NAME_FILE)_main.o -o $(NAME_FILE) -lrt

memory:
	gcc $(CFLAGS) -c $(NAME_FILE)_source.c $(NAME_FILE)_main.c
	gcc $(NAME_FILE)_source.o $(NAME_FILE)_main.o -o $(NAME_FILE) -lrt
	valgrind ./$(NAME_FILE)

clean:
	rm -rf $(NAME_FILE) *.o