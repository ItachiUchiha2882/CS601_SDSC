CXX=g++
# EIGEN= -I/nfs_home/nikhilh/eigen-3.3.9
CFLAGS= -Wall -Werror -I./inc -std=gnu++11 -O3

all: checkbin checkobj fem1 fem2

fem1: src/fem1.cpp
	$(CXX) $(CFLAGS) $^ -o bin/$@

fem2: src/fem2.cpp
	$(CXX) $(CFLAGS) $^ -o bin/$@

# checkbin:
# 	[ -d bin ] || mkdir -p bin

checkbin:
	if [ ! -d bin/ ]; then mkdir bin/; fi
	
checkobj:
	if [ ! -d obj/ ]; then mkdir obj/; fi

# checkobj:
# 	[ -d obj ] || mkdir -p obj
# .PHONY : clean
clean:
	-rm -f obj/* bin/*

team:
	@echo "Sourabh Bhosale 200010004@iitdh.ac.in\nDibyashu Kashyap 200010013@iitdh.ac.in"