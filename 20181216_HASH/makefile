
CC=gcc
CFLAGS=-g -Wall -std=c99
MAIN=main
SHARED_H = $(wildcard ../shared/*.h) hash.h
SHARED_C = $(wildcard ../shared/*.c) hash.c

tutti: clear $(MAIN)

%: %.c $(SHARED_H) $(SHARED_C)
	$(CC) $(CFLAGS) -o $@ $< $(SHARED_C)

run: 
	$(MAIN)

clear:
	clear