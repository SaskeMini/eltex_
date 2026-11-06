CFLAGS=-Wall -Werror -Wextra
CHECK=-lcheck -lsubunit -lm -lrt -lpthread
GCOV_FLAGS=-fprofile-arcs -ftest-coverage

all:
	make phonebook
	./phonebook
	make clean

phonebook:
	gcc $(CFLAGS) -c phonebook_source.c user_input_func.c
	ar rcs libstatlib.a *.o
	gcc phonebook_main.c -L. -lstatlib -o phonebook

memory:
	gcc $(CFLAGS) -c phonebook_source.c user_input_func.c phonebook_main.c
	gcc *.o -o phonebook
	valgrind ./phonebook

testing:
	gcc $(CFLAGS) $(GCOV_FLAGS) -c phonebook_source.c
	gcc $(CFLAGS) -c test_phonebook.c
	ar rcs libstatlib.a *.o
	gcc $(GCOV_FLAGS) *.o -L. -lstatlib -o testing $(CHECK)
	./testing
	lcov -t "testing" -o testing.info -c -d .
	genhtml -o report testing.info
	make clean

clean:
	rm -rf phonebook testing *.gcda *.gcno *info *.o *.a statlib lstatlib