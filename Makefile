#OBJS specifies which files to compile as part of the project
OBJS = src/sorting_alg_SDL2_main.cpp

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = obj/sorting_alg_SDL2_main

#This is the target that compiles our executable
all : $(OBJS)
	g++ $(OBJS) -w -lSDL2 -o $(OBJ_NAME)
