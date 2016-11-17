CC = g++
LINK_FLAGS = -lboost_graph;
CC_FLAGS = -Wall -Wextra -Werror -std=c++11
EXEC = bin/main
SOURCES=$(wildcard src/*.cpp)
OBJECTS=$(SOURCES:.cpp=.o)

default: all clean

all: $(EXEC)

optimized :
	CC_FLAGS = -O3 -std=c++11
	$(EXEC)

debug:
	make -f Makefile-debug

$(EXEC): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(EXEC) $(LINK_FLAGS)

%.o: %.cpp
	$(CC) -c $(CC_FLAGS) $< -o $@

clean :
	rm $(OBJECTS)
