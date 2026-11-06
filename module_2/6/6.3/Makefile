CFLAGS=-Wall -Werror -Wextra
CHECK=-lcheck -lsubunit -lm -lrt -lpthread
GCOV_FLAGS=-fprofile-arcs -ftest-coverage
NAME_FILE=calc2

all:
	make clean
	make $(NAME_FILE)
	./$(NAME_FILE)
	make clean

$(NAME_FILE):
	gcc $(CFLAGS) -fPIC -c $(NAME_FILE)_source.c
	gcc $(FLAGS) -shared -o sumsub.so $(NAME_FILE)_source.o
	gcc $(FLAGS) -shared -o multdiv.so $(NAME_FILE)_source.o
	gcc $(NAME_FILE)_main.c sumsub.so multdiv.so -Wl,-rpath,. -o $(NAME_FILE)


clean:
	rm -rf $(NAME_FILE) testing *.gcda *.gcno *info *.o *.so