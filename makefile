OBJ_FLDR=build/
SRC_FLDR=src/
BIN_FLDR=bin/
OBJ_STR=$(OBJ_FLDR)lib.o $(OBJ_FLDR)sc.o $(OBJ_FLDR)myTerm.o
OBJ_F=lib.o sc.o myTerm.o

.PHONY: all clean

all: $(OBJ_F)
	g++ $(OBJ_STR) -o $(BIN_FLDR)sc
	echo "============PROGRAM STARTED============"
	./$(BIN_FLDR)sc
	echo "=============PROGRAM  ENDED============"

lib.o: $(SRC_FLDR)lib.cpp
	g++ -Wall -Werror -c $(SRC_FLDR)lib.cpp -o $(OBJ_FLDR)lib.o

sc.o: $(SRC_FLDR)sc.cpp
	g++ -Wall -Werror -c $(SRC_FLDR)sc.cpp -o $(OBJ_FLDR)sc.o

myTerm.o: $(SRC_FLDR)myTerm.cpp
	g++ -Wall -Werror -c $(SRC_FLDR)myTerm.cpp -o $(OBJ_FLDR)myTerm.o

clean:
	rm -rf $(OBJ_FLDR)*.*
	rm -rf $(BIN_FLDR)*
