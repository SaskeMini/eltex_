CFLAGS=-Wall -Werror -Wextra
CHECK=-lcheck -lsubunit -lm -lrt -lpthread
GCOV_FLAGS=-fprofile-arcs -ftest-coverage

all:
	make phonebook
	./phonebook
	make clean

phonebook:
	gcc $(CFLAGS) -fPIC -c phonebook_source.c user_input_func.c
	gcc $(CFLAGS) -shared -o din_lib.so *.o
	gcc $(FLAGS) phonebook_main.c din_lib.so -Wl,-rpath,. -o phonebook

memory:
	gcc $(CFLAGS) -c phonebook_source.c user_input_func.c phonebook_main.c
	gcc *.o -o phonebook
	valgrind ./phonebook

testing:
	gcc $(CFLAGS) $(GCOV_FLAGS) -fPIC -c phonebook_source.c
	gcc $(CFLAGS) -shared -o din_lib.so *.o -lgcov 
	gcc $(GCOV_FLAGS) test_phonebook.c din_lib.so -Wl,-rpath,. -o testing $(CHECK) -lgcov
	./testing
	lcov -t "testing" -o testing.info -c -d .
	genhtml -o report testing.info
	make clean

clean:
	rm -rf phonebook testing *.gcda *.gcno *info *.o