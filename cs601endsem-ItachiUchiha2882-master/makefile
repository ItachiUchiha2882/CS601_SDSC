CXX=g++
CFLAGS=-I./inc -Wall -Werror -std=c++11

file: src/file.cpp
	mkdir -p bin
	$(CXX) $(CFLAGS) $^ -o bin/$@

checkbin:
	if [ ! -d bin/ ]; then mkdir bin/; fi

clean:
	rm -f bin/*
