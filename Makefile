#OBJS specifies which files to compile as part of the project
OBJS = sorting_alg_SDL2_main.cpp

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = sorting_alg_SDL2_main

#This is the target that compiles our executable
all : $(OBJS)
	g++ $(OBJS) -w -lSDL2 -lSDL2_ttf -o $(OBJ_NAME)
