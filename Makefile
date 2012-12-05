#
# File Name:	Makefile
# Author:	Aditya Ramesh
# Date:		12/05/2012
# Contact:	_@adityaramesh.com
#


uname := $(shell uname)

ifeq ($(uname),Darwin)
	cxx = g++-mp-4.7
else ifeq ($(uname),Linux)
	cxx = g++
endif

cxxflags := -std=c++11 -Wall -Ofast -march=native -Iinclude
objects  := out/format_test.run

all : $(objects)

%.run :
	$(cxx) $(cxxflags) test/$(*F).cpp -o $@

clean :
	rm -rf out/*
