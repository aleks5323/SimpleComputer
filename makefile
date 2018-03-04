OBJ_FLDR=build/
SRC_FLDR=src/
BIN_FLDR=bin/
OBJ_STR=$(OBJ_FLDR)lib.o $(OBJ_FLDR)sc.o $(OBJ_FLDR)myTerm.o $(OBJ_FLDR)myBigChars.o
OBJ_F=lib.o sc.o myTerm.o myBigChars.o
TESTS=binFldr buildFldr

.PHONY: all clean

all: $(TESTS) $(OBJ_F)
	g++ $(OBJ_STR) -o $(BIN_FLDR)sc
	./$(BIN_FLDR)sc

lib.o: $(SRC_FLDR)lib.cpp
	g++ -Wall -Werror -c $(SRC_FLDR)lib.cpp -o $(OBJ_FLDR)lib.o

sc.o: $(SRC_FLDR)sc.cpp
	g++ -Wall -Werror -c $(SRC_FLDR)sc.cpp -o $(OBJ_FLDR)sc.o

myTerm.o: $(SRC_FLDR)myTerm.cpp
	g++ -Wall -Werror -c $(SRC_FLDR)myTerm.cpp -o $(OBJ_FLDR)myTerm.o

myBigChars.o: $(SRC_FLDR)myBigChars.cpp
	g++ -Wall -Werror -c $(SRC_FLDR)myBigChars.cpp -o $(OBJ_FLDR)myBigChars.o

binFldr:
	[ -d $(BIN_FLDR) ] || mkdir $(BIN_FLDR)

buildFldr:
	[ -d $(OBJ_FLDR) ] || mkdir $(OBJ_FLDR)

clean:
	rm -rf $(OBJ_FLDR)*.*
	rm -rf $(BIN_FLDR)*
