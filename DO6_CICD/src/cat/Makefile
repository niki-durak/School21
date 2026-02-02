CC = gcc
CFLAGS = -std=c11 -Wall -Werror -Wextra -D_GNU_SOURCE -g

BUILD = ../build/

s21_cat:
	$(CC) $(CFLAGS) s21_cat.c -o s21_cat
style:
	cp ../../materials/linters/.clang-format ../../src/cat    clang-format -i *.c
	clang-format -i *.h    rm .clang-format
clean:
	rm -rf s21_cat
leaks:
	leaks -atExit -- ./s21_cat j y.txt
test:
	sh test_cat.sh s21_cat
rebuild: clean