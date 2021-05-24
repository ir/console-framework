// ConsoleOutput.cpp : This file contains the 'main' function. 
/*
* 
*/
#include <iostream>
#include "cFramework.h"
#include "enums.h"
#include <time.h>
#include "cgui.h"

bool running = false;

void console_title(Console console) // retarded animation 
{
    std::string name_arr = { "" };
    std::string name_anim = { "-koohlisarb" }; // 11
    double l = (((console.r_getSize()[0] / 3) - (179 / 3)) / 1.8);
    for (int i = 0; i < l; i++)
        name_arr.append("-");
    int counter = 0;
    int orig = 0;
    int lala = orig;
    while (running)
    {
        console.v_setTitle(name_arr);
        name_arr[lala] = name_anim[(name_anim.length() - counter) - 1];
        if (orig == name_arr.length() - 11)
            orig = 0;
            
        if ((name_anim.length() - counter) - 1 <= 0) // https://tenor.com/view/troll-pilled-gif-19289988
        {
            
            name_arr[orig] = '-';
            counter = 0;
            orig++;
            lala = orig;
            Sleep(1000);
        }
        else
        {
            counter++;
            lala++;
            Sleep(250);
        }
    }
}

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

    console.v_colOut(" LOADING DONE\n", DarkGreen);

    //console.v_setTitle("LOADING DONE"); // setting the title

    console.v_colOut("New Color\n", White); 

    running = true;
    std::thread t1(console_title, console);
    
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
        
        /*if (GetAsyncKeyState(VK_F4) & 1)
            console.v_readLine(hConsole);
            
        if (GetAsyncKeyState(VK_F5) & 1)
            std::cout << "Hello\n";

        if (GetAsyncKeyState(VK_F6) & 1)
            std::cout << "This is a random string\n";

        if (GetAsyncKeyState(VK_F7) & 1)
            std::cout << "This is a string with multiple spaces\n";

        if (GetAsyncKeyState(VK_F8) & 1)
            console.b_attachConsole();*/
            
    }
    console.v_setColor(hConsole, White); // setting color back to white
    running = false;
    t1.detach();
    FreeConsole();
    PostMessageA(GetConsoleWindow(), WM_CLOSE, 0, 0);
    
    return 0;
}

