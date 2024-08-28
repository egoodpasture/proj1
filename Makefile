CXX=		g++
CXXFLAGS=	-g -Wall -std=gnu++11
SHELL=		bash

all:		lib_info

lib_info:	lib_info.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -f lib_info

test:		test-output

test-output:	lib_info
	@echo Running all gradescripts...
	./gradeall

