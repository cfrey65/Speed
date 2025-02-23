CC = gcc
CCFLAGS = -std=c99 -g -D_DEBUG -Wall -pedantic #Removed -Werror for testing, add back after testing

# Get list of the ENGINE's source files
SOURCES = $(wildcard src/*.c)
# Get list of the GAME's source files
SOURCES += $(wildcard game/*.c) #Commented out because of duplicate defintions of main
# Local header files
INCLUDE = -I./include -I./game

# Different linked libraries, include paths, library paths for Windows vs. Linux
ifeq ($(OS),Windows_NT)
	INCLUDE += -IC:\\msys64\\include -IC:\\msys64\\ucrt64\\include
	LDFLAGS = -LC:\\msys64\\lib -LC:\\msys64\\ucrt64\\lib
	LDLIBS = -lraylib -lopengl32 -lgdi32 -lwinmm -lcomdlg32 -lole32
else
	INCLUDE += -I/usr/include -I/usr/local/include
	LDFLAGS = -L/usr/lib -L/usr/local/lib
	LDLIBS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -lXrandr -lXinerama -lXi -lXxf86vm -lXcursor

	CFLAGS += -D_DEFAULT_SOURCE
endif
LDFLAGS += -L./lib

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
