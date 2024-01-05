binary_path := $(dir $(realpath $(lastword $(MAKEFILE_LIST))))
src := $(binary_path)
build := $(binary_path)../build

CXX=g++
CXXFLAGS=-Og -ggdb -fno-sanitize-recover=all -fsanitize=address,alignment,undefined -Wall

EXECS=$(build)/fps

INCLUDE = -I/usr/include/ -I$(src)/

LDFLAGS:=$(LDFLAGS) -pthread -lcivetweb-cpp -lcivetweb

SHELL=/bin/bash

all: $(patsubst %.cpp, %.out, $(addsuffix .cpp, $(EXECS)))

$(build):
	mkdir -p $@

$(build)/%.out: $(src)/%.cpp | $(build)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o $(patsubst %.out, %.o, $@) -c $< 
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(INCLUDE) -o $(@:.out=) $(patsubst %.out, %.o, $@)

clean:
	@rm ${EXECS} $(addsuffix .o, $(EXECS)) || true

