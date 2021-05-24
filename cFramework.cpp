#include "cFramework.h"
#include <iostream>
#include "enums.h"
#include <fstream>
#include <stdio.h>

// outputs data to file
void cMisc::v_outFile(const char* file, const char* data)
{
    std::ofstream ofile(file);
    if (ofile.is_open())
    {
        ofile << data << "\n";
        ofile.close();
    }
    return;
}

const char* cMisc::c_getTime()
{
    auto timenow = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    ctime_s(cMisc::tt, sizeof(cMisc::tt), &timenow);
    return cMisc::tt;
}

// outputs debug message to file, appending a new line each time
void cMisc::v_outDebug(const char* file, const char* data)
{
    std::ofstream ofile(file, std::ios::app);
    std::ifstream ifile;
    std::string t = cMisc::c_getTime(); t = t.substr(4, 18);
    ifile.open(file);
    if (ifile.is_open())
    {
        ofile << "[debug] " << t << ": " << data;
        ifile.close();
        ofile.close();
    }
    return;
}

void Console::v_debugCout(const char* data)
{
    std::string op = data;
    Console::v_colOut("[debug] " + op, LightBlue);
    
    cMisc::v_outDebug("debug.log", data);
}

// sets the color of the color, check enums.h for all of the colors
void Console::v_setColor(HANDLE hConsoleHandle, int color)
{
    SetConsoleTextAttribute(hConsoleHandle, color);
}

// returns the current color of the console text, returns 65535 (max unsigned short) if fails
unsigned short Console::s_getColor(HANDLE hConsole) 
{
    unsigned short ret{}; // buffer
    CONSOLE_SCREEN_BUFFER_INFO info;
    if (!GetConsoleScreenBufferInfo(hConsole, &info))
        return 65535;
    ret = info.wAttributes; // assigns attribute to buffer
    return ret;
}

void Console::v_colOut(std::string text, unsigned char color)
{
    unsigned short ocolor = s_getColor(GetStdHandle(STD_OUTPUT_HANDLE)); // save previous color
    v_setColor(GetStdHandle(STD_OUTPUT_HANDLE), color);
    std::cout << text;
    v_setColor(GetStdHandle(STD_OUTPUT_HANDLE), ocolor);
}

// prints green text signifying that something was successful
void Console::v_printSuccess(const char* text)
{
    unsigned short ocolor = s_getColor(GetStdHandle(STD_OUTPUT_HANDLE)); // save previous color
    v_setColor(GetStdHandle(STD_OUTPUT_HANDLE), LightGreen); 
    std::string output = "[+] "; output += text;
    std::cout << output << std::endl;
    v_setColor(GetStdHandle(STD_OUTPUT_HANDLE), ocolor); // restore previous color
}

// prints green text signifying that something was successful
void Console::v_printSuccess(std::string text)
{
    unsigned short ocolor = s_getColor(GetStdHandle(STD_OUTPUT_HANDLE)); // save previous color
    v_setColor(GetStdHandle(STD_OUTPUT_HANDLE), LightGreen);

    std::cout << "[+] " + text << std::endl;

    v_setColor(GetStdHandle(STD_OUTPUT_HANDLE), ocolor); // restore previous color
}

// prints red text signifying that something failed
void Console::v_printError(const char* text)
{
    unsigned short ocolor = s_getColor(GetStdHandle(STD_OUTPUT_HANDLE)); // save previous color
    v_setColor(GetStdHandle(STD_OUTPUT_HANDLE), Red);
    std::string output = "[-] "; output += text;
    std::cout << output << std::endl;

    v_setColor(GetStdHandle(STD_OUTPUT_HANDLE), ocolor); // restore previous color
}

// prints red text signifying that something failed
void Console::v_printError(std::string text)
{
    unsigned short ocolor = s_getColor(GetStdHandle(STD_OUTPUT_HANDLE)); // save previous color
    v_setColor(GetStdHandle(STD_OUTPUT_HANDLE), Red);

    std::cout << "[-] " + text << std::endl;

    v_setColor(GetStdHandle(STD_OUTPUT_HANDLE), ocolor); // restore previous color
}

// prints a loading box
void Console::v_printLoad(int rotations)
{
    std::cout << "[-]" << std::flush;
    for (int i = 0; i < rotations; i++) {
        Sleep(150);
        std::cout << "\b\b\b[\\]" << std::flush;
        Sleep(150);
        std::cout << "\b\b\b[|]" << std::flush;
        Sleep(150);
        std::cout << "\b\b\b[/]" << std::flush;
        Sleep(150);
        std::cout << "\b\b\b[-]" << std::flush;
    }
}

void Console::v_printHeader()
{
    Console::v_colOut(Console::headerTitle, 33); 
    Console::v_colOut("\n--------------------\n", Gold);
    Console::v_setColor(hHandle, White);
}

bool Console::b_attachConsole()
{
    int x; std::cout << "PID: "; std::cin >> x;
    FreeConsole();
    if (AttachConsole(x))
    {
        std::cout << "Attached to " << x << std::endl;
        return true;
    }
    else
    {
        AllocConsole();
        std::cout << "Failed to attach to " << x << std::endl;
        return false;
    }
    
}

void Console::v_setCursorPos(short x, short y) 
{
    COORD dwPos;
    dwPos.X = x;
    dwPos.Y = y;
    SetConsoleCursorPosition(hHandle, dwPos);
}

void Console::v_setCursor(long size, bool visible) 
{
    CONSOLE_CURSOR_INFO cursorInfo;
    cursorInfo.dwSize = size;
    cursorInfo.bVisible = visible;
}

// returns the current size of the console, -1 if fails 
std::vector<int> Console::r_getSize()
{
    HWND hWnd = GetConsoleWindow();
    RECT rect; std::vector<int> size;
    if (GetWindowRect(hWnd, &rect))
    {
        size.push_back(rect.right - rect.left);
        size.push_back(rect.bottom - rect.top);
        return size;
    }
    size.push_back(-1);
    return size;
}

// sets the title of the console
void Console::v_setTitle(LPCSTR title)
{
    if (GetConsoleWindow() == 0)
        return;

    SetConsoleTitleA(title);
}

// sets the title of the console
void Console::v_setTitle(std::string title)
{
    if (GetConsoleWindow() == 0)
        return;

    SetConsoleTitleA(title.c_str());
}

void Console::v_clearConsole()
{
    static HANDLE ConsoleHandle;
    if (!ConsoleHandle)
        ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFO* pConsoleScreenInfo = new CONSOLE_SCREEN_BUFFER_INFO();

    if (!GetConsoleScreenBufferInfo(ConsoleHandle, pConsoleScreenInfo))
        return;
    DWORD CharsWritten;
    FillConsoleOutputCharacterA(ConsoleHandle, ' ', pConsoleScreenInfo->dwSize.X * pConsoleScreenInfo->dwSize.Y, { 0, 0 }, &CharsWritten);
    SetConsoleCursorPosition(ConsoleHandle, { 0, 0 });
}

/*
* STD_INPUT_HANDLE  (DWORD) -10	input.   Initially, this is the console input buffer,         CONIN$.
* STD_OUTPUT_HANDLE (DWORD) -11	output.  Initially, this is the active console screen buffer, CONOUT$.
* STD_ERROR_HANDLE  (DWORD) -12	error.   Initially, this is the active console screen buffer, CONOUT$.
*/
BOOL Console::b_setHandle(DWORD nStdHandle, HANDLE hHandle)
{
    if(SetStdHandle(nStdHandle,hHandle))
        return true;
    return false;
}

// returns the handle of the console
HANDLE Console::h_getHandle()
{
    return GetStdHandle(STD_OUTPUT_HANDLE);
}

Console::Console()
{
    if (GetConsoleWindow() == 0) // if console doesnt exit
        AllocConsole();
    if(hHandle != NULL)
        hHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    Console::v_printHeader();
}

Console::~Console()
{
    if(GetConsoleWindow() != 0) 
        FreeConsole();
}
