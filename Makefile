CC     = gcc
CFLAGS = -Wall -Wextra -g
SRCS   = insert.c delete.c search.c find_min.c find_max.c delete_min.c delete_max.c rotate.c print_tree.c

all: rbt

rbt: main.c $(SRCS) rbt.h
	$(CC) $(CFLAGS) main.c $(SRCS) -o rbt

test: tests/test_rbt.c $(SRCS) rbt.h
	$(CC) $(CFLAGS) tests/test_rbt.c $(SRCS) -o test_rbt
	./test_rbt

clean:
	rm -f rbt test_rbt

.PHONY: all test clean
