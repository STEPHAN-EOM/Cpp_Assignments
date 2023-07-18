CXX = g++
CXXFLAGSMAC = -W -Wall -std=c++17 
CXXFLAGS = -W -Wall -std=c++17 -pthread

all: assignment5a assignment5b
#####################################################
assignment5a: assignment5a.cc
	$(CXX) $(CXXFLAGS) -o assignment5a assignment5a.cc

point.o: point.cc point.h
	$(CXX) $(CXXFLAGS)  -o point.o -c point.cc

ConvexHull.o: ConvexHull.cc point.h ConvexHull.h
	$(CXX) $(CXXFLAGS)  -o ConvexHull.o -c ConvexHull.cc

assignment5b.o: assignment5b.cc point.h ConvexHull.h
	$(CXX) $(CXXFLAGS) -o assignment5b.o -c assignment5b.cc

assignment5b: assignment5b.o point.o ConvexHull.o
	$(CXX) $(CXXFLAGS)  -o assignment5b assignment5b.o point.o ConvexHull.o

#####################################################
.Phony: all clean

clean:
	$(RM) -f *.o *.txt assignment5a assignment5b
