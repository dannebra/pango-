# Files to compile
OBJS = pango.cpp gui.cpp gameloop.cpp init.cpp audio_manager.cpp

# Compiler
CC = g++

COMPILER_FLAGS = -std=c++17 -O2

COMPILER_FLAGS_DEBUG = -Werror -Wshadow -Wall -std=c++17 -g

LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_mixer

# Name of the exectuable
EXECUTABLE = pango

# Debug build name
EXECUTABLE_DEBUG = pango_debug

all : $(OBJS)	
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(EXECUTABLE)

debug : $(OBJS)	
	$(CC) $(OBJS) $(COMPILER_FLAGS_DEBUG) $(LINKER_FLAGS) -o $(EXECUTABLE_DEBUG)

start: all run

start_debug: debug run_debug

run:
	./$(EXECUTABLE)

run_debug:
	./$(EXECUTABLE_DEBUG)

clean:
	rm -f *.o pango pango_debug