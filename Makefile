CC = gcc
CCFLAGS = -std=c99 -g -Wall -pedantic

SOURCES = $(wildcard src/*.c)

# Get ALL of the header files, from EVERYWHERE (in the include dir, at least :P)
INCLUDE = -I./include -I/usr/include -I/usr/local/include

# Set locations of external libraries
LDFLAGS = -L/usr/lib -L/usr/local/lib
# Set which external libraries to include in the binary
LDLIBS = -ltiff -lglfw3 -lGL -lX11 -lpthread -lXrandr -lXi -ldl

all: clean finnes

# Rule to build the binary "finnes"
finnes: $(SOURCES)
	$(CXX) $(CXXFLAGS) $^ $(INCLUDE) $(LDFLAGS) $(LDLIBS) -o $@

.PHONY: clean
clean:
	rm -rf finnes