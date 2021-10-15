//Using SDL and standard IO
#include <SDL2/SDL.h>
//#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <iostream>
#include <vector>


/*

To use this program compile it with SDL2 (use the Makefile)

Any interaction with the program will happen through the SDL2 window but prints happen in the terminal. 

*/


//Screen dimensions
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;
int arraySize = 64;
bool light_mode = false;
//int array_a[arraySize] = {0};
std::vector<int> array_a(arraySize, 0);
const int range = SCREEN_HEIGHT;
int current_Sort = 0, current_Compare = 0;
int sortingDone = 0;
int iteration = 0;
//Loop flag
bool quit = false;
//Event handler
SDL_Event kevent;
int runningDelay = 5;
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
        gWindow = SDL_CreateWindow( "Sorting algorithms", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
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

std::string getOsName()
{
    #ifdef _WIN32
    return "Win";
    #elif _WIN64
    return "Win";
    #elif __APPLE__ || __MACH__
    return "Mac";
    #elif __linux__
    return "Linux";
    #else
    return "Other";
    #endif
}                

void clearTerminal()
{
    std::string opSys = getOsName();
    if (opSys == "Win")
    {
        std::system("cls");
    }
    else if (opSys == "Mac")
    {
        std::system("clear");
    }
    else if (opSys == "Linux")
    {
        std::system("clear");
    }
}

void printControls()
{
    clearTerminal();
    std::cout << "a: Change size of array, current size is: " << arraySize << std::endl;
    std::cout << "s: Change light mode" << std::endl;
    std::cout << "To run a sorting algorythm type one of the following numbers: " << std::endl;
    std::cout << "0: Randomize the array" << std::endl;
    std::cout << "1: Use insertion sort" << std::endl;
    std::cout << "2: Use bubble sort" << std::endl;
    std::cout << "3: Use optimized bubble sort" << std::endl;
    std::cout << "4: Merge sort" << std::endl;
    std::cout << std::endl;
    std::cout << "The following buttons can be changed at anypoint when running algorithms: " << std::endl;
    std::cout << "q: Quits the program" << std::endl;
    std::cout << "+: increase delay by 1 ms" << std::endl;
    std::cout << "-: decrease delay by 1 ms" << std::endl;
    std::cout << std::endl;
    std::cout << "Running delay is set to: " << runningDelay << " ms" << std::endl;
}

void visualize_light()
{
    //Clear rendering surface with white
    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(gRenderer);

    clearTerminal();
    std::cout << "Iteration: " << iteration << std::endl;
    iteration++;
    
    for (int i = 0; i <= arraySize-1; i++)
    {
        
        if(i == current_Sort)
        {
            SDL_SetRenderDrawColor(gRenderer, 0x00, 0xFF, 0x00, 0xFF);
        }
        // else if(i == current_Compare)
        // {
        //     SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF);
        // }
        else
        {
            SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0xFF, 0xFF);
        }
        SDL_Rect outlineRect = {(i)*((float)SCREEN_WIDTH/(float)arraySize), SCREEN_HEIGHT, ((float)SCREEN_WIDTH/(float)arraySize)-1, -array_a[i]*0.95};
        
        SDL_RenderFillRect(gRenderer, &outlineRect);
    }
    SDL_RenderPresent(gRenderer);
}

void visualize_dark()
{
    //Clear rendering surface with white
    SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0x00);
    SDL_RenderClear(gRenderer);

    clearTerminal();
    std::cout << "Iteration: " << iteration << std::endl;
    iteration++;
    
    for (int i = 0; i <= arraySize-1; i++)
    {
        // if(i == current_Sort)
        // {
        //     SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0x80);
        //     SDL_Rect outlineRectSelector = {(i)*((float)SCREEN_WIDTH/(float)arraySize), 10, ((float)SCREEN_WIDTH/(float)arraySize)-1, 20};

        //     SDL_RenderFillRect(gRenderer, &outlineRectSelector);
        //     SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
        // }
        // if(i == current_Compare && current_Compare != 0)
        // {
        //     SDL_SetRenderDrawColor(gRenderer, 0x00, 0xFF, 0x00, 0xFF);
        // }
        if(i == current_Sort)
        {
            SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF);
        }

        else
        {
            SDL_SetRenderDrawColor(gRenderer, 0x69, 0x69, 0x69, 0xFF);
        }
        SDL_Rect outlineRect = {(i)*((float)SCREEN_WIDTH/(float)arraySize), SCREEN_HEIGHT, ((float)SCREEN_WIDTH/(float)arraySize)-1, -array_a[i]*0.95};

        SDL_RenderFillRect(gRenderer, &outlineRect);
    }
    SDL_RenderPresent(gRenderer);
}

void visualize()
{
    if (light_mode == true)
    {
        visualize_light();
    }
    else
    {
        visualize_dark();
    }
    
}
void specialKeys()
{
    switch(kevent.key.keysym.sym)
    {
        case SDLK_q:
            if (kevent.key.state == SDL_PRESSED)
            {
                quit = true;
                close();
                break;
            }
            else
            {
                break;
            }
        case SDLK_PLUS:
        case SDLK_KP_PLUS:
            if (kevent.key.state == SDL_PRESSED)
            {
                runningDelay = runningDelay + 1;
                printControls();
                break;
            }
            else
            {
                break;
            }          
        case SDLK_MINUS:
        case SDLK_KP_MINUS:
            if (kevent.key.state == SDL_PRESSED)
            {
                if(runningDelay == 0)
                {
                    runningDelay = 0;
                }
                else
                {
                    runningDelay = runningDelay - 1;
                    printControls();
                    break;
                }
            }
            else
            {
                break;
            }
        break;   
    }
}

void specialKeyHandler()
{
    if(SDL_PollEvent(&kevent) !=0)
    {
        specialKeys();
    }
}

void sortingFrameHandler()
{
    visualize();
    SDL_Delay(runningDelay);
    specialKeyHandler();
}

void randomizeArray()
{
    for (int i=0;i<arraySize-1;i++)
    {
        array_a[i]=1+rand()%range;
    }
    visualize();
    std::cout << "Array has been randomized" << std::endl;
}

void insertionSort()
{
    std::cout << "using insertion sort" << std::endl;
    current_Sort = 0;
    int key = 0;
    for(current_Compare = 0; arraySize > current_Compare; current_Compare++)
    {
        key = array_a[current_Compare];
        current_Sort = current_Compare - 1;

        while (current_Sort >= 0 && array_a[current_Sort] > key && !quit && sortingDone == 0)
        {
            array_a[current_Sort + 1] = array_a[current_Sort];
            current_Sort = current_Sort - 1;
            sortingFrameHandler();
        }
        array_a[current_Sort + 1] = key;
    }
    std::cout << "Done" << std::endl;
    sortingDone = 1;
}

void bubbleSort()
{
    int tmp = 0;
    bool swapped; 
    while(true && !quit && sortingDone == 0)
    {
        swapped = false;
        for (current_Sort = 0; current_Sort < arraySize-1; current_Sort++)
        {
            
            current_Compare = current_Sort + 1;
            if (array_a[current_Sort] > array_a[current_Compare])
            {
                tmp = array_a[current_Sort];
                array_a[current_Sort] = array_a[current_Compare];
                array_a[current_Compare] = tmp;
                swapped = true;
            }
            sortingFrameHandler();
        }
        if(!swapped)
        {
            break;
        }
    }
}

void bubbleSortOptimized()
{
    int tmp = 0;
    bool swapped; 
    int n = arraySize-1;
    while(true && !quit && sortingDone == 0)
    {
        swapped = false;
        for (current_Sort = 0; current_Sort < n; current_Sort++)
        {
            
            current_Compare = current_Sort + 1;
            if (array_a[current_Sort] > array_a[current_Compare])
            {
                tmp = array_a[current_Sort];
                array_a[current_Sort] = array_a[current_Compare];
                array_a[current_Compare] = tmp;
                swapped = true;
            }
            sortingFrameHandler();
        }
        n -= 1;
        if(!swapped)
        {
            std::cout << "Done" << std::endl;
            break;
        }
    }
}


int mSortMerge(std::vector<int> & array_a, int start, int mid, int end)
{
    //I create a few ints for moving contents of main array into sub arrays.
    int n1 = mid - start + 1;
    int n2 = end - mid;

    //Then i create to arrays a left and and right array.
    std::vector<int> L(n1, 0);
    std::vector<int> R(n2, 0);

    //Then i transfer the contents of the array into right and left array.
    for (int i = 0; i < n1; i++)
    {
        L[i] = array_a[start + i];
    }
    for (int j = 0; j < n2; j++)
    {
        R[j] = array_a[mid + 1 + j];
    }

    //Create ints for iteration.
    int i = 0, j = 0, k = start;

    //Sorting loop
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            array_a[k] = L[i];
            i++;
            current_Sort = k;
            current_Compare = start + i;
            sortingFrameHandler();
        }
        else
        {
            array_a[k] = R[j];
            j++;
            current_Sort = k;
            current_Compare = mid + 1 + j;
            sortingFrameHandler();
        }       
        k++;
        
    }

    while (i < n1)
    {
        array_a[k] = L[i];
        i++;
        k++;
    }
    
    while (j < n2)
    {
        array_a[k] = R[j];
        j++;
        k++;
    }
}

int mSortSplit(std::vector<int> & array_a, int start, int end)
{
    if (start >= end)
        return 0;
    // Recursion to split arrays into single elements and then perform the merge.
    mSortSplit(array_a, start, (start+end)/2);
    mSortSplit(array_a, ((start+end)/2)+1, end);
    mSortMerge(array_a, start, (start+end)/2, end);
}

void mergeSort()
{
    mSortSplit(array_a, 0, arraySize);
}

void arrayResize(int current_size, int new_size)
{
    if (current_size < new_size)
        {
            for (int i = 0; i < new_size; i++)
            {
                array_a.push_back(0);
                arraySize = new_size;
            }
        }
        else if (current_size > new_size)
        {
            for (int i = 0; i < new_size; i++)
            {
                arraySize = new_size;
                array_a.pop_back();
            }
        }
}

int arrayResizeHandler()
{
    clearTerminal();
    std::cout << "0: size 16" << std::endl;
    std::cout << "1: size 32" << std::endl;
    std::cout << "2: size 64" << std::endl;
    std::cout << "3: size 128" << std::endl;
    std::cout << "4: size 256" << std::endl;

    while(SDL_WaitEvent(&kevent) !=0)
    {
        switch(kevent.key.keysym.sym)
            {
                case SDLK_0:
                    if (kevent.key.state == SDL_PRESSED)
                    {
                        arrayResize(arraySize, 16);
                        return 0;
                    }
                    else
                    {
                        break;
                    }
                case SDLK_1:
                    if (kevent.key.state == SDL_PRESSED)
                    {
                        arrayResize(arraySize, 32);
                        return 0;
                    }
                    else
                    {
                        break;
                    }
                case SDLK_2:
                    if (kevent.key.state == SDL_PRESSED)
                    {
                        arrayResize(arraySize, 64);
                        return 0;
                    }
                    else
                    {
                        break;
                    }
                case SDLK_3:
                    if (kevent.key.state == SDL_PRESSED)
                    {
                        arrayResize(arraySize, 128);
                        return 0;
                    }
                    else
                    {
                        break;
                    }
                case SDLK_4:
                    if (kevent.key.state == SDL_PRESSED)
                    {
                        arrayResize(arraySize, 256);
                        return 0;
                    }
                    else
                    {
                        break;
                    }
                break;
            }
    }
}

void generalKeys()
{
    switch(kevent.key.keysym.sym)
    {
        case SDLK_0:
            if (kevent.key.state == SDL_PRESSED)
            {
                randomizeArray();
                sortingDone = 0;
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
                SDL_Delay(2000);
                randomizeArray();
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
                SDL_Delay(2000);
                randomizeArray();
                printControls();
                break;
            }
            else
            {
                break;
            }    
        case SDLK_3:
            if (kevent.key.state == SDL_PRESSED)
            {
                bubbleSortOptimized();
                SDL_Delay(2000);
                randomizeArray();
                printControls();
                break;
            }
            else
            {
                break;
            }  
        case SDLK_4:
            if (kevent.key.state == SDL_PRESSED)
            {
                mergeSort();
                SDL_Delay(2000);
                randomizeArray();
                printControls();
                break;
            }
            else
            {
                break;
            }  
        case SDLK_a:
            if (kevent.key.state == SDL_PRESSED)
            {
                arrayResizeHandler();
                randomizeArray();
                printControls();
                break;
            }
            else
            {
                break;
            }
        case SDLK_s:
            if (kevent.key.state == SDL_PRESSED)
            {
                light_mode = !light_mode;
                visualize();
                printControls();
                break;
            }
            else
            {
                break;
            }         
        break;
    }
}

int main( int argc, char* args[] )
{
    printControls();
    //check initialization
    if(!init())
    {
        std::cout << "Failed to init! " << std::endl;
    }
    else
    {
        randomizeArray();
        printControls();
        //While application is runningq
        while (!quit)
        {   
            //Handle events on queue
            while(SDL_WaitEvent(&kevent) !=0)
            {   
                //User requests quit
                if(kevent.key.state == SDL_PRESSED)
                {
                    specialKeys();
                    generalKeys();
                    iteration = 0;
                } 
            }
        }
    }
    //Free resources and close SDL
    close();
    return 0;
}