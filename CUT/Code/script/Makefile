
GCC = gcc
INC = inc
SRC = src
BIN = bin
OBJ = obj
CFLAGS = -c -g -Wall
LDFLAGS = -o 
IFLAGS = -I $(INC)


all : TES

TES : $(OBJ)/main.o $(OBJ)/list.o
	$(GCC) $(LDFLAGS) $(BIN)/TES $(OBJ)/main.o $(OBJ)/list.o


$(OBJ)/main.o : $(SRC)/main.c
	$(GCC) $(CFLAGS) $(SRC)/main.c $(IFLAGS)
	mv main.o $(OBJ)/  

$(OBJ)/list.o : $(SRC)/list.c
	$(GCC) $(CFLAGS) $(SRC)/list.c $(IFLAGS)
	mv list.o $(OBJ)/        

clean : 
	rm -f *.out *.o
	rm -f $(OBJ)/*.o
	rm -f $(BIN)/*
	@echo "Cleaning Done!"    
