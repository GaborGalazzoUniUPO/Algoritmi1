
CC=gcc
CFLAGS=-g -Wall -std=c99 -O
MAIN=src/main
TEST=test/test
MODEL_H = $(wildcard src/model/*.h)
SHARED_H = $(wildcard ../shared/*.h)
MODEL_C = $(wildcard src/model/*.c)
SHARED_C = $(wildcard ../shared/*.c)
ENGINE_C = $(wildcard src/engine/*.c)
ENGINE_H = $(wildcard src/engine/*.h)

tutti: clear $(MAIN) $(TEST)

%: %.c $(MODEL_H) $(SHARED_H) $(MODEL_C) $(SHARED_C) $(ENGINE_H) $(ENGINE_C) 
	gcc -g -Wall -std=c99 -o out/$@ $< $(MODEL_C) $(SHARED_C) $(ENGINE_C)

run: 
	./out/$(MAIN)
test: 
	./out/$(TEST)

clear:
	clear