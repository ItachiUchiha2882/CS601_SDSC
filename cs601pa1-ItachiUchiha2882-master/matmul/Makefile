CXX=g++
CFLAGS=-I/home/s200010004/papi/src/install/include
ifeq ($(DEBUG), 1)
CFLAGS+= -g -DPAPI
LDFLAGS=-L/home/s200010004/papi/src/install/lib -lpapi
endif

all: matmul1 matmul2 matmul3

matmul1: src/matmul1.cpp
	mkdir -p bin
	$(CXX) $(CFLAGS) $^ -o bin/$@ $(LDFLAGS) 
matmul2: src/matmul1.cpp
	$(CXX) $(CFLAGS) $^ -o bin/$@ $(LDFLAGS) 
matmul3: src/matmul1.cpp
	$(CXX) $(CFLAGS) $^ -o bin/$@ $(LDFLAGS) 

team:
	@echo "Sourabh Bhosale 200010004@iitdh.ac.in\nDibyashu Kashyap 200010013@iitdh.ac.in"