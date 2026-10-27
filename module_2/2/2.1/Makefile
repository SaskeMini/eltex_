CFLAGS=-Wall -Werror -Wextra
CHECK=-lcheck -lsubunit -lm -lrt -lpthread
GCOV_FLAGS=-fprofile-arcs -ftest-coverage

all:
	make phonebook
	./phonebook
	make clean

phonebook:
	gcc $(CFLAGS) -c phonebook_source.c phonebook_main.c
	gcc phonebook_source.o phonebook_main.o -o phonebook

memory:
	gcc $(CFLAGS) -c phonebook_source.c phonebook_main.c
	gcc phonebook_source.o phonebook_main.o -o phonebook
	valgrind ./phonebook

testing:
	gcc $(CFLAGS) $(GCOV_FLAGS) -c phonebook_source.c
	gcc $(CFLAGS) -c test_phonebook.c
	gcc $(GCOV_FLAGS) phonebook_source.o test_phonebook.o -o testing $(CHECK)
	tr -d '\r' < test_input.txt > tmp && mv tmp test_input.txt
	./testing
	lcov -t "testing" -o testing.info -c -d .
	genhtml -o report testing.info
	make clean

clean:
	rm -rf phonebook testing *.gcda *.gcno *info *.o