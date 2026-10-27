CFLAGS=-Wall -Werror -Wextra
CHECK=-lcheck -lsubunit -lm -lrt -lpthread
GCOV_FLAGS=-fprofile-arcs -ftest-coverage
NAME_FILE=calc

all:
	make clean
	make $(NAME_FILE)
	./$(NAME_FILE)
	make clean

$(NAME_FILE):
	gcc $(CFLAGS) -c $(NAME_FILE)_source.c $(NAME_FILE)_main.c
	gcc $(NAME_FILE)_source.o $(NAME_FILE)_main.o -o $(NAME_FILE)

memory:
	gcc $(CFLAGS) -c $(NAME_FILE)_source.c $(NAME_FILE)_main.c
	gcc $(NAME_FILE)_source.o $(NAME_FILE)_main.o -o $(NAME_FILE)
	valgrind ./$(NAME_FILE)

testing:
	gcc $(CFLAGS) $(GCOV_FLAGS) -c $(NAME_FILE)_source.c
	gcc $(CFLAGS) -c test_$(NAME_FILE).c
	gcc $(GCOV_FLAGS) $(NAME_FILE)_source.o test_$(NAME_FILE).o -o testing $(CHECK)
	tr -d '\r' < test_input.txt > tmp && mv tmp test_input.txt
	./testing
	lcov -t "testing" -o testing.info -c -d .
	genhtml -o report testing.info
	make clean

clean:
	rm -rf $(NAME_FILE) testing *.gcda *.gcno *info *.o