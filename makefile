CC=gcc
FLAGS=-g -Wall

all: FIRSTFIT BESTFIT NEXTFIT BUDDY

FIRSTFIT: first.c
	$(CC) $(FLAGS) -o FIRSTFIT first.c

BESTFIT: best.c
	$(CC) $(FLAGS) -o BESTFIT best.c

NEXTFIT: next.c
	$(CC) $(FLAGS) -o NEXTFIT next.c

BUDDY: buddy.c
	$(CC) $(FLAGS) -o BUDDY buddy.c

clean:
	-rm FIRSTFIT
	-rm BESTFIT
	-rm NEXTFIT
	-rm BUDDY

