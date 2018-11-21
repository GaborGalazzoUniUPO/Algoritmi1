
CC=gcc
CFLAGS=-g -Wall -std=c99 -O -fsanitize=address
EXECS=benchmark

tutti: $(EXECS)

%: %.c
	gcc -g -Wall -std=c99 -o $@ $<