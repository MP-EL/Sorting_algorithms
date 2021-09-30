//Using SDL and standard IO
#include <SDL2/SDL.h>
#include <stdio.h>
#include <iostream>

//Screen dimensions
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;
const int arraySize = 128;
int array_a[arraySize] = {0};
const int range = SCREEN_HEIGHT;
int current_Sort = 0;

//Rendering window
SDL_Window* gWindow = NULL;

//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

SDL_Renderer* gRenderer = NULL;

bool init()
{
    //init flag
    bool success = true;
    //Init SDL
    if(SDL_Init(SDL_INIT_VIDEO)< 0)
    {
        std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
    }
    else
    {
        //Set texture filtering to linear
        if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1"))
        {
            std::cout << "Warning: Linear texture filtering not enabled!" << std::endl;
        }
        
        //Create window
        gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if (gWindow == NULL)
        {       
            std::cout << "Window could not be created! SDL_Eroor: " << SDL_GetError() << std::endl;
            success = false;
        }
        else
        {
            //Create renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
			if( gRenderer == NULL )
			{
				std::cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;
				success = false;
			}
        }
    }
    return success;
}

void visualize()
{
    //Clear rendering surface with white
    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(gRenderer);
    
    for (int i = 0; i <= arraySize; i++)
    {
        
        if(current_Sort == i)
        {
            SDL_SetRenderDrawColor(gRenderer, 0x00, 0xFF, 0x00, 0xFF);
        }
        else
        {
            SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0xFF, 0xFF);
        }
        SDL_Rect outlineRect = {(i)*(SCREEN_WIDTH/arraySize), SCREEN_HEIGHT, (SCREEN_WIDTH/arraySize)-1, -array_a[i]};
        
        SDL_RenderFillRect(gRenderer, &outlineRect);
    }
    SDL_RenderPresent(gRenderer);
}

void randomizeArray()
{
    for (int i=0;i<arraySize-1;i++)
    {
        array_a[i]=1+rand()%range;
    }
}

void insertionSort()
{
    std::cout << "using insertion sort" << std::endl;
    current_Sort = 0;
    int i = 0, key = 0;
    for(i = 0; arraySize > i; i++)
    {
        key = array_a[i];
        current_Sort = i - 1;

        while (current_Sort >= 0 && array_a[current_Sort] > key)
        {
            array_a[current_Sort + 1] = array_a[current_Sort];
            current_Sort = current_Sort - 1;
            visualize();
            SDL_Delay(5);
        }
        array_a[current_Sort + 1] = key;
    }
    std::cout << "Done" << std::endl;
}

void bubbleSort() // Dont use it will crash terminal 8) 8) Perfect code 10/10
{
    std::cout << "using bubble sort" << std::endl;
    current_Sort = 0;
    int tmp = 0, i=0;
    int counter = 0;
    while (counter < arraySize-1)
    {
        for (i = 0; i < arraySize-1; i++)
        {
            if (array_a[i]>array_a[i+1])
            {
                current_Sort = i;
                tmp = array_a[i];
                array_a[i] = array_a[i+1];
                array_a[i+1] = tmp;
            }
            visualize();
            SDL_Delay(2);
        }
        counter += 1;
    }
    std::cout << "Done" << std::endl;
}

void printControls()
{
    std::system("clear");
    std::cout << "To run a sorting algorythm type one of the following numbers: " << std::endl;
    std::cout << "0: Randomize the array" << std::endl;
    std::cout << "1: Use insertion sort" << std::endl;
    std::cout << "2: Use bubble sort" << std::endl;
}

void close()
{
    //Destroy window
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    gRenderer = NULL;

    //Quit SDL subsystems
    SDL_Quit();  
}

int main( int argc, char* args[] )
{
    randomizeArray();
    printControls();
    //check initialization
    if(!init())
    {
        std::cout << "Failed to init! " << std::endl;
    }
    else
    {
        //Loop flag
        bool quit = false;
        //Event handler
        SDL_Event kevent;
        //While application is running
        while (!quit)
        {   
            
            //Handle events on queue
            while(SDL_PollEvent(&kevent) !=0)
            {   
                //User requests quit
                switch(kevent.key.keysym.sym)
                {
                    case SDLK_q:
                        if (kevent.key.state == SDL_PRESSED)
                        {
                            quit = true;
                            break;
                        }
                        else
                        {
                            break;
                        }
                    case SDLK_0:
                        if (kevent.key.state == SDL_PRESSED)
                        {
                            randomizeArray();
                            printControls();
                            break; 
                        }
                        else
                        {
                            break;
                        }
                    case SDLK_1:
                        if (kevent.key.state == SDL_PRESSED)
                        {
                            insertionSort();
                            printControls();
                            break;
                        }
                        else
                        {
                            break;
                        }
                    case SDLK_2:
                        if (kevent.key.state == SDL_PRESSED)
                        {
                            bubbleSort();
                            printControls();
                            break;
                        }
                        else
                        {
                            break;
                        }
                        
                        
                }
            }
            visualize();
        }
    }
    //Free resources and close SDL
    close();
    return 0;
}