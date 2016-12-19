CC = g++
LINK_FLAGS = -lboost_graph;
CC_FLAGS = -std=c++11 -Werror -Wall -Wextra -pedantic -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-include-dirs -Wnoexcept -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 -Wundef -Wno-unused -Wno-variadic-macros -Wno-parentheses -fdiagnostics-show-option
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
