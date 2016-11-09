CC = g++
LINK_FLAGS = -lboost_graph;
CC_FLAGS = -Wall -Wextra -Werror -O3
EXEC = main
SOURCES=$(wildcard *.cpp)
OBJECTS=$(SOURCES:.cpp=.o)

default: all clean

all: $(EXEC)

$(EXEC): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(EXEC) $(LINK_FLAGS)

%.o: %.cpp
	$(CC) -c $(CC_FLAGS) $< -o $@

clean :
	rm $(OBJECTS)
