#include "cFramework.h"
#include <iostream>

void Console::v_readLine(HANDLE consoleHandle)
{
    std::thread read_thread(cRead::v_readLine, consoleHandle);
    read_thread.detach();
}

void cRead::v_readLine(HANDLE consoleHandle) // "main" function
{
    //while (bot_running) // if you call from thread and this is false, make sure to free thread
    {
        if (GetConsoleWindow() == 0)
            return;

        //HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
        int prev = 0;
        if (GetConsoleCursorPosition(consoleHandle).Y > prev)
        {
            auto r = std::async(std::launch::async, cRead::check_line, consoleHandle);
            prev = GetConsoleCursorPosition(consoleHandle).Y;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    }
}

COORD cRead::GetConsoleCursorPosition(HANDLE hConsoleOutput)
{
    CONSOLE_SCREEN_BUFFER_INFO cbsi;
    if (GetConsoleScreenBufferInfo(hConsoleOutput, &cbsi))
    {
        return cbsi.dwCursorPosition;
    }
    else
    {
        // the function failed. call GetLastError() for details
        COORD invalid = { 0, 0 };
        return invalid;
    }
}

char cRead::read_console(HANDLE consoleHandle, int num, int y)
{
    char characterFromConsole;

    COORD positionInBuffer;
    positionInBuffer.X = num; // column number
    positionInBuffer.Y = y; // row number

    DWORD numberOfCharactersReaded = 0;

    DWORD numberOfCharactersToRead = 1;

    ReadConsoleOutputCharacterA(
        consoleHandle,
        &characterFromConsole,
        numberOfCharactersToRead,
        positionInBuffer,
        &numberOfCharactersReaded);

    return characterFromConsole;
}


int cRead::check_line(HANDLE consoleHandle)
{
    int prev = cRead::GetConsoleCursorPosition(consoleHandle).Y;
    std::string joao;
    
    //if (bot_running)
    {
        for (int i = 0; i < 128; i++)
        {
            if (read_console(consoleHandle, i, prev - 1) == '\0' || \
                read_console(consoleHandle, i, prev - 1) == '\n')
                break;
            else
                joao += read_console(consoleHandle, i, prev - 1);
        }
    }

    int a = joao.find_last_not_of(" ") + 1;
   
    joao.erase(std::remove(joao.begin() + a, joao.end(), ' '), joao.end());
    joao.erase(std::remove(joao.begin(), joao.end(), '\n'), joao.end());
    
    if (joao.compare("Hello") == 0) // example string to find 
    {
        std::cout << "Found Hello\n";
    }

    else if (joao.compare("Yeo") == 0)
    {
        std::cout << "Found Yeo\n";
    }

    else if (joao.compare("This is a string with multiple spaces") == 0)
    {
        std::cout << "Found this random string\n";
    }

    return GetConsoleCursorPosition(consoleHandle).Y;
}
