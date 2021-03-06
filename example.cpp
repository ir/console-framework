// ConsoleOutput.cpp : This file contains the 'main' function. 

/*
*  Done:
*   Set and get current color of the console text
*   Print success and failure
*   Clear Console
*   Loading box
*   Set Title  
*   Simple Attach Console Function
*   Colored Output
*   Get Console Size
*   Read a line from console output
*   Debug output (to console & to file)
*   
*   WIP/Maybe:
*       Gui system
* 
*/

#include <iostream>
#include "cFramework.h"
#include "enums.h"

int readKey()
{
    for (int i = 0; i < 180; i++)
        if (GetAsyncKeyState(i) & 1)
            return i;
    return -1;
}

int main() 
{
    Console console = Console(); // create new console obj
    HANDLE hConsole = console.h_getHandle(); // get the handle
    
    console.v_setColor(hConsole, Cream); // setting the color of all of the console, view enums.h
    
    std::cout << "The quick brown fox jumps over the lazy dog." << std::endl;
    
    console.v_printSuccess("Something succeeded"); // printing success
    console.v_printError("Something failed"); // printing error

    console.v_printLoad(1); // printing loading box, arg is the amount of rotations

    console.v_colOut(" LOADING DONE\n", DarkGreen); // prints colored text

    console.v_setTitle("LOADING DONE"); // setting the title

    console.v_colOut("New Color\n", White); 
    
    std::cout << "Original Color\n";
    
    int vec_size[2] = { console.r_getSize()[0], console.r_getSize()[1] };
    std::cout << "The size of the console is: " << vec_size[0] << "x" << vec_size[1] << std::endl;
    
    cMisc::v_outFile("Text.txt", "This is a test\nThis is another line of text");

    console.v_debugCout("This is a debug message\n");
    
    while (!GetAsyncKeyState(VK_ESCAPE) & 1)
    {
        int key = readKey();
        switch (key)
        {
        case VK_F4: 
            console.v_readLine(hConsole); Sleep(50); break;
        case VK_F5: 
            std::cout << "Hello\n"; break;
        case VK_F6: 
            std::cout << "This is a random string\n"; break;
        case VK_F7: 
            std::cout << "This is a string with multiple spaces\n"; break;
        case VK_F8: 
            console.b_attachConsole(); break;
        case VK_F9: 
            console.v_clearConsole(); break;
        }
  
    }
    
    console.v_setColor(hConsole, White); 
    FreeConsole();
    return 0;
}

