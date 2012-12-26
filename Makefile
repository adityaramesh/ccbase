#
# File Name:	Makefile
# Author:	Aditya Ramesh
# Date:		12/05/2012
# Contact:	_@adityaramesh.com
#

ifeq ($(CXX),)
	cxx = g++
else
	cxx = $(CXX)
endif

ifeq ($(findstring clang,$(cxx)),)
	optflags := -Ofast
else
	optflags := -O3
endif

stdflags  := -std=c++11
incflags  := -I. -I$(XUTIL_INCLUDE_PATH)
wflags    := -Wall
archflags := -march=native
cxxflags  := $(stdflags) $(incflags) $(wflags) $(optflags) $(archflags)
objects   := $(foreach i,$(shell ls test),out/$(basename $(notdir $(i))).run)

all : $(objects)

%.run :
	$(cxx) $(cxxflags) test/$(*F).cpp -o $@

clean :
	rm -rf out/*
