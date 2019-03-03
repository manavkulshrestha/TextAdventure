DEP = rooms.h items.h
SRC = rooms.c items.c adventure.c
OBJ = rooms.o items.o adventure.o
PROG = adventure

$(PROG): $(OBJ)
	gcc $(DEP) $(OBJ) -o $(PROG)

$(OBJ): $(SRC)