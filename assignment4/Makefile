# @author: Chanho Eom
# @date: 4-May-2023
# @file: Makefile


CXX = g++
CXXFLAGS = -W -Wall -std=c++20 -Wsign-conversion -Werror

all: assignment4a assignment4b sort sort_ranges

#####################################

person.o: person.cc person.h assignment4.h
	$(CXX) $(CXXFLAGS) -c person.cc -o person.o

assignment4a.o: assignment4a.cc assignment4.h person.h
	$(CXX) $(CXXFLAGS) -c assignment4a.cc -o assignment4a.o

assignment4a: assignment4a.o person.o 
	$(CXX) $(CXXFLAGS) -o assignment4a assignment4a.o person.o

grid.o: grid.cc grid.h person.h assignment4.h
	$(CXX) $(CXXFLAGS) -c grid.cc -o grid.o

assignment4b.o: assignment4b.cc assignment4.h person.h grid.h
	$(CXX) $(CXXFLAGS) -c assignment4b.cc -o assignment4b.o 

assignment4b: assignment4b.o person.o grid.o
	$(CXX) $(CXXFLAGS) -o assignment4b assignment4b.o person.o grid.o

sort: sort.cc
	$(CXX) $(CXXFLAGS) -o sort sort.cc

sort_ranges: sort_ranges.cc
	$(CXX) $(CXXFLAGS) -o sort_ranges sort_ranges.cc


######################################

.Phony: all clean

clean:
	rm -f *.o assignment4a assignment4b sort sort_ranges

