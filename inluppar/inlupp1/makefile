CC=gcc
FLAGS= -Wall -std=c17 -g -pedantic
TARGETS=hash_table_tests linked_list_tests iterator_tests freq-count freq-count-gprof

all: freq-count

test: freq-count
	./freq-count 16k-words.txt

freq-count-gprof: freq-count.c linked_list.o hash_table.o iterator.h common.h
		$(CC) $(FLAGS) $< linked_list.o hash_table.o -pg -lcunit -o $@ 

freq-count: freq-count.c linked_list.o hash_table.o iterator.h common.h
		$(CC) $(FLAGS) $< linked_list.o hash_table.o -lcunit -o $@

linked_list.o: linked_list.c linked_list.h common.h
	$(CC) $(FLAGS) $< -c

hash_table.o: hash_table.c hash_table.h linked_list.o iterator.h common.h
	$(CC) $(FLAGS) $< -c

iterator.o: linked_list.o iterator.h
	$(CC) $(FLAGS) $< -c




linked_list_tests: linked_list.o linked_list_tests.c common.h
	$(CC) $(FLAGS) linked_list.o linked_list_tests.c -lcunit -o $@	

iterator_tests: linked_list.o iterator.h common.h iterator_tests.c
	$(CC) $(FLAGS) linked_list.o iterator_tests.c -lcunit -o $@
	
hash_table_tests: linked_list.o hash_table_tests.c hash_table.o common.h
	$(CC) $(FLAGS) linked_list.o hash_table_tests.c hash_table.o -lcunit -o $@




freq-count_run: freq-count
	./freq-count


memtest: iterator_tests
	valgrind --leak-check=full ./iterator_tests

hashmemtest: hash_table_tests
	valgrind --leak-check=full ./hash_table_tests

listmemtest: linked_list_tests
	valgrind --leak-check=full ./linked_list_tests

clean:
	rm -f *o
	rm -f *out
	rm -f $(TARGETS)

.PHONY: test clean


