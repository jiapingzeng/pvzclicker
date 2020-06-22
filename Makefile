CC = gcc
CFLAGS = -Wall -Wextra -Werror -lxdo

default: build

build: pvzclicker

clean:
	rm -rf *test* *.out pvzclicker

pvzclicker:
	$(CC) clicker.c -o $@ $(CFLAGS)