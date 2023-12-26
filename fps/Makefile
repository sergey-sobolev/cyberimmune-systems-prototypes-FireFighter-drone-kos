binary_path := $(dir $(realpath $(lastword $(MAKEFILE_LIST))))
src := $(binary_path)
build := $(binary_path)../build

CXX=g++
CXXFLAGS=-Og -ggdb -fno-sanitize-recover=all -fsanitize=address,alignment,undefined -Wall

OBJS=$(build)/utils.o

EXECS=$(build)/fps

INCLUDE = -I/usr/include/ -I$(src)/

LDFLAGS:=$(LDFLAGS) -pthread -lcivetweb-cpp -lcivetweb

SHELL=/bin/bash

all: $(OBJS) $(patsubst %.cpp, %.out, $(addsuffix .cpp, $(EXECS)))

$(build):
	mkdir -p $@

$(build)/%.o: $(src)/%.cpp $(src)/%.h | $(build)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o $@ -c $< 

$(build)/%.out: $(src)/%.cpp | $(build)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o $(patsubst %.out, %.o, $@) -c $< 
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(INCLUDE) -o $(@:.out=) $(patsubst %.out, %.o, $@) $(OBJS)

clean:
	@rm ${EXECS} ${OBJS} $(addsuffix .o, $(EXECS)) || true

