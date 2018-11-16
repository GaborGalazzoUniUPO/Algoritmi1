
CC=gcc
CFLAGS=-g -Wall -std=c99 -O
MAIN=src/main test/test
MODEL_H = $(wildcard src/model/*.h)
SHARED_H = $(wildcard ../shared/*.h)
MODEL_C = $(wildcard src/model/*.c)
SHARED_C = $(wildcard ../shared/*.c)
ENGINE_C = $(wildcard src/engine/*.c)
ENGINE_H = $(wildcard src/engine/*.h)

tutti: $(MAIN)

%: %.c $(MODEL_H) $(SHARED_H) $(MODEL_C) $(SHARED_C) $(ENGINE_H) $(ENGINE_C)
	clear 
	gcc -g -Wall -std=c99 -o out/$@ $< $(MODEL_C) $(SHARED_C) $(ENGINE_C)



clean:
	rm -rf *.o *.exe $(MAIN)