
CC=gcc
CFLAGS=-g -Wall -std=c99 -O
MAIN=src/main test/test
MODEL_H = $(shell python ../utils/find.py src/model/ *.h)
SHARED_H = $(shell python ../utils/find.py ../shared/ *.h)
MODEL_C = $(shell python ../utils/find.py src/model/ *.c)
SHARED_C = $(shell python ../utils/find.py ../shared/ *.c)
ENGINE_C = $(shell python ../utils/find.py src/engine/ *.c)
ENGINE_H = $(shell python ../utils/find.py src/engine/ *.h)

tutti: $(MAIN)

%: %.c $(MODEL_H) $(SHARED_H) $(MODEL_C) $(SHARED_C) $(ENGINE_H) $(ENGINE_C)
	clear 
	gcc -g -Wall -std=c99 -o out/$@ $< $(MODEL_C) $(SHARED_C) $(ENGINE_C)



clean:
	rm -rf *.o *.exe $(MAIN)