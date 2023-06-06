# @author: Chanho Eom
# @date: 24-Mar-2023
# @file: Makefile
#


CXX = g++
CXXFLAGS = -W -Wall -std=c++20 -Wsign-conversion -Werror
OBJECTS = matrix_operations.o assignment3.o

all: assignment3

############################################

logging.o: logging.cc logging.h
	$(CXX) $(CXXFLAGS) -c logging.cc -o logging.o

matrix.o: matrix.cc matrix.h logging.h hpc_concepts.h
	$(CXX) $(CXXFLAGS) -c matrix.cc -o matrix.o

matrix_operations.o: matrix_operations.cc matrix_operations.h matrix.h hpc_concepts.h
	$(CXX) $(CXXFLAGS) -c matrix_operations.cc -o matrix_operations.o

assignment3.o: assignment3.cc matrix_operations.h matrix.h
	$(CXX) $(CXXFLAGS) -c assignment3.cc -o assignment3.o

assignment3: $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o assignment3 $(OBJECTS)

############################################

.Phony: all clean

clean:
	rm -f *.o assignment3

















