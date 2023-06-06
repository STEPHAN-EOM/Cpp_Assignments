# @author: Chanho Eom
# @date: 28 Feb 2023
# @file: Makefile
#


CXX = g++
CXXFLAGS = -W -Wall -std=c++17
OBJECTS = portfolio.o assignment2b.o

all: assignment2a assignment2b

###############################

assignment2a: assignment2a.cc
	$(CXX) $(CXXFLAGS) -o assignment2a assignment2a.cc

portfolio.o: portfolio.cc portfolio.h instruments.h
	$(CXX) $(CXXFLAGS) -c portfolio.cc -o portfolio.o

assignment2b.o: assignment2b.cc portfolio.h instruments.h
	$(CXX) $(CXXFLAGS) -c assignment2b.cc -o assignment2b.o

assignment2b: $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o assignment2b $(OBJECTS)

################################

.Phony: all clean

clean:
	rm -f *.o assignment2a assignment2b


