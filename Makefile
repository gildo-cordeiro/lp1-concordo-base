dir:
	mkdir -p bin

bin/sistema.o: src/sistema.cpp
	g++ src/sistema.cpp -Iinclude -O0 -fsanitize=address -g -Wall -ansi -pedantic -std=c++11 -c -o bin/sistema.o

bin/executor.o: src/executor.cpp bin/sistema.o
	g++ src/executor.cpp -Iinclude -O0 -fsanitize=address -g -Wall -ansi -pedantic -std=c++11 -c -o bin/executor.o

bin/usuario.o: usuario.cpp usuario.h
	g++ src/usuario.cpp -Iinclude -O0 -fsanitize=address -g -Wall -ansi -pedantic -std=c++11 -c -o bin/usuario.o

objects: bin/sistema.o bin/executor.o

concordo: dir objects src/concordo.cpp
	g++ -Wall -Iinclude -O0 -fsanitize=address bin/sistema.o bin/executor.o src/concordo.cpp -o concordo

clean:
	rm -rf bin *.o concordo

all: concordo

run:
	./concordo
