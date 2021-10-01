//Using SDL and standard IO
#include <SDL2/SDL.h>
#include <stdio.h>
#include <iostream>

//Screen dimensions
const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;
const int arraySize = 200;
int array_a[arraySize] = {0};
const int range = SCREEN_HEIGHT;
int current_Sort = 0, current_Compare = 0;
int sortingDone = 0, sortingCounter = 0;
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
    
    for (int i = 0; i <= arraySize-1; i++)
    {
        
        if(i == current_Sort)
        {
            SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0x80);
            SDL_Rect outlineRectSelector = {(i)*(SCREEN_WIDTH/arraySize), SCREEN_HEIGHT-15, (SCREEN_WIDTH/arraySize)-1, 10};
        
            SDL_RenderFillRect(gRenderer, &outlineRectSelector);
            SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
        }
        // else if(i == current_Compare && current_Compare != 0)
        // {
        //     SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0x00, 0xFF);
        // }
        else
        {
            SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
        }
        SDL_Rect outlineRect = {(i)*(SCREEN_WIDTH/arraySize), SCREEN_HEIGHT-20, (SCREEN_WIDTH/arraySize)-1, -array_a[i]};
        
        SDL_RenderFillRect(gRenderer, &outlineRect);

    }
    SDL_RenderPresent(gRenderer);
}

void specialKeys()
{
        //User requests quit
        if(kevent.key.state == SDL_PRESSED)
        {
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
                case SDLK_PLUS:
                case SDLK_KP_PLUS:
                    if (kevent.key.state == SDL_PRESSED)
                    {
                        runningDelay = runningDelay + 1;
                        std::cout << "Changed running delay to: " << runningDelay << " ms" << std::endl;
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
                            std::cout << "Changed running delay to: " << runningDelay << " ms" << std::endl;
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
}

void specialKeyHandler()
{
    if(SDL_PollEvent(&kevent) !=0)
    {
        specialKeys();
    }
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
    int key = 0, i = 0;
    for(i = 0; arraySize > i; i++)
    {
        key = array_a[i];
        current_Sort = i - 1;

        while (current_Sort >= 0 && array_a[current_Sort] > key && !quit && sortingDone == 0)
        {
            visualize();
            SDL_Delay(runningDelay);
            specialKeyHandler();
            sortingCounter += 1;
            std::cout << sortingCounter << std::endl;

            array_a[current_Sort + 1] = array_a[current_Sort];
            current_Sort = current_Sort - 1;

        }
        array_a[current_Sort + 1] = key;
    }
    std::cout << "Done" << std::endl;
    std::cout << sortingCounter << std::endl;
    sortingDone = 1;
}

void bubbleSort()
{
    int tmp = 0, i = 0;
    bool swapped; 
    while(true && !quit && sortingDone == 0)
    {
        swapped = false;
        for (current_Sort = 0; current_Sort < arraySize-1; current_Sort++)
        {
            
            i = current_Sort + 1;

            visualize();
            SDL_Delay(runningDelay);
            specialKeyHandler();
            sortingCounter += 1;
            std::cout << sortingCounter << std::endl;

            if (array_a[current_Sort] > array_a[i])
            {
                tmp = array_a[current_Sort];
                array_a[current_Sort] = array_a[i];
                array_a[i] = tmp;
                swapped = true;
            }
            
        }
        if(!swapped)
        {
            std::cout << sortingCounter << std::endl;
            break;
        }
    }
}

void bubbleSortOptimized()
{
    int tmp = 0, i = 0;
    bool swapped; 
    int n = arraySize-1;
    while(true && !quit && sortingDone == 0)
    {
        swapped = false;
        for (current_Sort = 0; current_Sort < n; current_Sort++)
        {
            
            i = current_Sort + 1;

            visualize();
            SDL_Delay(runningDelay);
            specialKeyHandler();
            sortingCounter += 1;
            std::cout << sortingCounter << std::endl;

            if (array_a[current_Sort] > array_a[i])
            {
                tmp = array_a[current_Sort];
                array_a[current_Sort] = array_a[i];
                array_a[i] = tmp;
                swapped = true;
            }
            
        }
        n -= 1;
        if(!swapped)
        {
            std::cout << "Done" << std::endl;
            std::cout << sortingCounter << std::endl;
            break;
        }
    }
}
int mMerge(int array[], int const left, int const mid, int const right)
{
    auto const subArrayOne = mid - left +1;
    auto const subArrayTwo = right - mid;

    auto *leftArray = new int[subArrayOne],
         *rightArray = new int[subArrayTwo];

    // Copy data to temp arrays leftArray[] and rightArray[]
    for (auto i = 0; i < subArrayOne; i++)
        leftArray[i] = array[left + i];
    for (auto j = 0; j < subArrayTwo; j++)
        rightArray[j] = array[mid + 1 + j];
  
    current_Sort = 0, // Initial index of first sub-array
        current_Compare = 0; // Initial index of second sub-array
    int indexOfMergedArray = left; // Initial index of merged array

    // Merge the temp arrays back into array[left..right]
    while (current_Sort < subArrayOne && current_Compare < subArrayTwo) {
        if (leftArray[current_Sort] <= rightArray[current_Compare]) {
            array[indexOfMergedArray] = leftArray[current_Sort];
            current_Sort++;
        }
        else {
            array[indexOfMergedArray] = rightArray[current_Compare];
            current_Compare++;
        }
        indexOfMergedArray++;
        visualize();
        SDL_Delay(runningDelay);
        specialKeyHandler();
        sortingCounter += 1;
        std::cout << sortingCounter << std::endl;
    }
    // Copy the remaining elements of
    // left[], if there are any
    while (current_Sort < subArrayOne) {
        array[indexOfMergedArray] = leftArray[current_Sort];
        current_Sort++;
        indexOfMergedArray++;
        visualize();
        SDL_Delay(runningDelay);
        specialKeyHandler();
        sortingCounter += 1;
        std::cout << sortingCounter << std::endl;
    }
    // Copy the remaining elements of
    // right[], if there are any
    while (current_Compare < subArrayTwo) {
        array[indexOfMergedArray] = rightArray[current_Compare];
        current_Compare++;
        indexOfMergedArray++;
        visualize();
        SDL_Delay(runningDelay);
        specialKeyHandler();
        sortingCounter += 1;
        std::cout << sortingCounter << std::endl;
    }
}

void mSort(int A[], int const begin, int const end)
{

    if (begin>=end)
        return;
    
    auto mid = begin + (end - begin) / 2;
    mSort(A, begin, mid);
    mSort(A, mid + 1, end);
    mMerge(A, begin, mid, end);


}

void mergeSort()
{
    mSort(array_a, 0, arraySize-1);
    std::cout << sortingCounter << std::endl;

}






void printControls()
{
    std::system("clear");
    if(sortingCounter != 0)
    {
        std::cout << sortingCounter << std::endl;
        sortingCounter = 0;
    }
    std::cout << "To run a sorting algorythm type one of the following numbers: " << std::endl;
    std::cout << "0: Randomize the array" << std::endl;
    std::cout << "1: Use bubble sort" << std::endl;
    std::cout << "2: Use optimized bubble sort" << std::endl;
    std::cout << "3: Use insertion sort" << std::endl;
    std::cout << "4: Merge sort" << std::endl;
    std::cout << "+: increase delay by 1 ms" << std::endl;
    std::cout << "-: decrease delay by 1 ms" << std::endl;
    std::cout << std::endl;
    std::cout << "Running delay is set to: " << runningDelay << " ms" << std::endl;
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
                
                bubbleSort();
                SDL_Delay(2000);
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
                bubbleSortOptimized();
                SDL_Delay(2000);
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
                insertionSort();
                SDL_Delay(2000);
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

    printControls();
    //check initialization
    if(!init())
    {
        std::cout << "Failed to init! " << std::endl;
    }
    else
    {
        randomizeArray();
        //While application is running
        while (!quit)
        {   
            //Handle events on queue
            while(SDL_PollEvent(&kevent) !=0)
            {   
                //User requests quit
                if(kevent.key.state == SDL_PRESSED)
                {
                    specialKeys();
                    generalKeys();
                }
            }
        }
    }
    //Free resources and close SDL
    close();
    return 0;
}