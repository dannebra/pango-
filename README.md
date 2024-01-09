# Pango++ (WIP)

Pango++ is a clone of the MS-DOS game Pango written in C++. This is a work in progress that will be updated continously. 

## Prerequisites
* SDL2
* GCC (g++) if using the Makefile. If you are using clang then replace CC in the Makefile with clang++ instead.
* (GNU Make)

  
Make sure that SDL2 is installed on your computer. Follow the instructions [here](https://lazyfoo.net/tutorials/SDL/01_hello_SDL/index.php#:~:text=Select%20Your%20Operating%20System) to install SDL2 on your machine.

## Setting up Pango++ 
1. Clone the project: `git clone https://github.com/dannebra/pango_plus_plus.git`.
2. Move (cd) into the source directory where you cloned the project `cd pango_plus_plus/src/`
3. To build and run the program type `make start`.
4. To build and run a debug build type `make start_debug`
5. To just build the program, type `make` or `make pango_debug` for the debug build.
6. To clean the project type `make clean`.

## Controls
* ESC: Exit the game.
* M: Toggle music.

## Architecture (TODO)
The plan is to use the state pattern in order to easily swtich between different game states.
