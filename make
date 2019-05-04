CC=GCC
FLAGS=-g-Wall

all: FIRSTFIT BESTFIT NEXTFIT BUDDY

FIRSTFIT: first.c
        $(CC) $(FLAGS) -O FIRSTFIT first.c

BESTFIT: best.c
        $(CC) $(FLAGS) -O BESTFIT best.c

NEXTFIT: next.c
        $(CC) $(FLAGS) -O NEXTFIT next.c

BUDDY: buddy.c
        $(CC) $(FLAGS) -O BUDDY buddy.c

clean:
        -rm FIRSTFIT
        -rm BESTFIT
        -rm NEXTFIT
        -rm BUDDY
