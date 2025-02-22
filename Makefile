CC = gcc
CCFLAGS = -std=c99 -g -D_DEBUG -Wall -Werror -pedantic

# Get list of source files
SOURCES = $(wildcard src/*.c)
# Local header files
INCLUDE = -I./include

# Different linked libraries, include paths, library paths for Windows vs. Linux
ifeq ($(PLATFORM_OS),WINDOWS)
	INCLUDE += -IC:\\msys64\\include -IC:\\msys64\\ucrt64\\include
	LDFLAGS = -LC:\\msys64\\lib -LC:\\msys64\\ucrt64\\lib
	LDLIBS = -lraylib -lopengl32 -lgdi32 -lwinmm -lcomdlg32 -lole32
endif
ifeq ($(PLATFORM_OS),LINUX)
	INCLUDE += -I/usr/include -I/usr/local/include
	LDFLAGS = -L/usr/lib -L/usr/local/lib
	LDLIBS = -lraylib -lGl -lm -lpthread -ldl -lrt -lX11

	CFLAGS += -D_DEFAULT_SOURCE
endif

# Check if game implemenation exists (must be a file named "Game.c" 
# inside directory "/game"; must also define main() function)
ifneq ("$(wildcard game/Game.c)","")
    FILE_EXISTS = 1
endif

# Exit if "Game.c" doesn't exist
ifeq ($(FILE_EXISTS),)
$(error ***COMPILATION ERROR: Game.c not present in game dir***)
endif

# Compile the raylib app binary
purdoom: $(SOURCES)
	$(CC) $(CCFLAGS) $^ $(INCLUDE) $(LDFLAGS) $(LDLIBS) -o $@ -DPLATFORM_DESKTOP
