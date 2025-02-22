CC = gcc
CFLAGS = -std=c99 -ggdb -Werror -Wall -lm

LDFLAGS = -LC:/msys64/ucrt64/bin
LDLIBS = -lraylib -lopengl32 -lgdi32 -lwinmm -static -lpthread

INCLUDE = -Isrc -IC:/msys64/ucrt64/include

rpp-demo: src/driver.c src/gui-mgr.c src/gui-rpp.c
	$(CC) $(CFLAGS) $^ $(LDFLAGS) $(LDLIBS) $(INCLUDE) -o $@