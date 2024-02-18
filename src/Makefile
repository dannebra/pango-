# Files to compile
OBJS = pango.cpp game_manager.cpp timer.cpp input_manager.cpp game_entity.cpp graphics.cpp texture.cpp animated_texture.cpp asset_manager.cpp audio_manager.cpp

# Compiler
CC = g++

COMPILER_FLAGS = -std=c++17 -O2

COMPILER_FLAGS_DEBUG = -Werror -Wshadow -Wall -std=c++17 -g

LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf

# Name of the exectuable
EXECUTABLE = Pango++

# Debug build name
EXECUTABLE_DEBUG = PangoDebug

pango : $(OBJS)	
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(EXECUTABLE)

pango_debug : $(OBJS)	
	$(CC) $(OBJS) $(COMPILER_FLAGS_DEBUG) $(LINKER_FLAGS) -o $(EXECUTABLE_DEBUG)

.PHONY: start
start: pango run

.PHONY: start_debug
start_debug: pango_debug run_debug

.PHONY: run
run:
	./$(EXECUTABLE)

.PHONY: run_debug
run_debug:
	./$(EXECUTABLE_DEBUG)

.PHONY: clean
clean:
	rm -f *.o $(EXECUTABLE) $(EXECUTABLE_DEBUG)