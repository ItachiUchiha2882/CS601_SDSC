#makefile used for VERSION4
CXX=g++
CFLAGS=-I./inc -g -Wall -Werror -std=c++11
dotprod: src/vectorprod.cpp build/scprod.o
	mkdir -p bin
	$(CXX) $(CFLAGS) $^ -o bin/$@
build/scprod.o: src/scprod.cpp inc/scprod.h
	mkdir -p build 	
	$(CXX) $(CFLAGS) -c $< -o $@
.PHONY: clean
clean:
	rm -f build/* bin/*
