CXX = g++
CXXFLAGS = -W -Wall -std=c++17 -fconcepts -pthread 
LDFLAGS = -lboost_mpi -lboost_serialization -lmpi

all: assignment5c
#####################################################

point.o: point.cc point.h
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o point.o -c point.cc

ConvexHull.o: ConvexHull.cc point.h ConvexHull.h
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o ConvexHull.o -c ConvexHull.cc

assignment5c.o: assignment5c.cc point.h ConvexHull.h
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o assignment5c.o -c assignment5c.cc

assignment5c: assignment5c.o point.o ConvexHull.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o assignment5c assignment5c.o point.o ConvexHull.o

#####################################################
.Phony: all clean

clean:
	$(RM) -f *.o *.txt assignment5c
