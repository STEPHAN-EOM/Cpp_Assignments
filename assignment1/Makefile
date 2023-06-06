
# @file : Makefile
# @author : Chanho Eom
# @contact : eomc@tcd.ie
# @date : 13 February 2023
#

all: assignment1

CXX = g++
CXXFLAGS = -W -Wall -std=c++17


#################################

assignment1: assignment1.cc
	$(CXX) $(CXXFLAGS) -o assignment1 assignment1.cc


############### You don't need to change below here ##################

.Phony: all clean

clean:
	rm -f function.o assignment1

test:
	./assignment1
