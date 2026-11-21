CFLAGS=-Wall -Werror -Wextra
CHECK=-lcheck -lsubunit -lm -lrt -lpthread
GCOV_FLAGS=-fprofile-arcs -ftest-coverage
NAME_FILE=ibp

all:
	make clean
	make $(NAME_FILE)
	./$(NAME_FILE) -b &
	sleep 1
	./$(NAME_FILE) -s news sport &
	./$(NAME_FILE) -s weather &
	sleep 1
	./$(NAME_FILE) -p news &
	./$(NAME_FILE) -p weather &
	sleep 5
	killall -INT $(NAME_FILE)
	make clean

$(NAME_FILE):
	gcc $(CFLAGS) -c $(NAME_FILE)_source.c $(NAME_FILE)_main.c
	gcc $(NAME_FILE)_source.o $(NAME_FILE)_main.o -o $(NAME_FILE)

memory:
	gcc $(CFLAGS) -c $(NAME_FILE)_source.c $(NAME_FILE)_main.c
	gcc $(NAME_FILE)_source.o $(NAME_FILE)_main.o -o $(NAME_FILE)
	valgrind ./$(NAME_FILE)

clean:
	rm -rf $(NAME_FILE) *.o