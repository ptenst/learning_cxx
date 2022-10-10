CXX=g++
FLAG=-std=c++11 -g -Wall
DEP_INCLUDE=-I./includes
DEP_LIB=-L./libs -pthread -lm 

SOURCE = $(wildcard *.cc)
OBJS = $(patsubst %.cc,%.o,${SOURCE})
TARGETS = $(patsubst %.o,%,${OBJS})

$(info $(OBJS))
$(info $(TARGETS))

all:${TARGETS}

${TARGETS}:%:%.o
	$(CXX) $(FLAG) $(DEP_LIB) -o $@ $<

%.o:%.cc
	$(CXX) $(FLAG) $(DEP_INCLUDE) -c -o $@ $<

.PHONY:clean
clean:
	rm -rf *.o $(TARGETS) backtrace
