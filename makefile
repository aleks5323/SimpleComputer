.PHONY: all clean

all: lib.o sc.o
	g++ build/lib.o build/sc.o -o bin/sc
	echo "============PROGRAM STARTED============"
	./bin/sc
	echo "=============PROGRAM  ENDED============"

lib.o: src/lib.cpp
	g++ -Wall -Werror -c src/lib.cpp -o build/lib.o

sc.o: src/sc.cpp
	g++ -Wall -Werror -c src/sc.cpp -o build/sc.o

clean:
	rm -rf build/*.o
	rm -rf bin/*
