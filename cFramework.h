#include <Windows.h>
#include <string>
#include <vector>
#include <thread>
#include <future>

namespace cRead
{
    COORD GetConsoleCursorPosition(HANDLE hConsoleOutput);
    char read_console(HANDLE consoleHandle, int num, int y);
    int check_line(HANDLE consoleHandle);
    void v_readLine(HANDLE consoleHandle);
}

namespace cMisc
{
    static char tt[26];
    void v_outFile(const char* file, const char* data);
    void v_outDebug(const char* file, const char* data);
    const char* c_getTime();
    
}

// note that this will allocate a new console when created (if one doesnt already exist)
// and will free it when destroyed
class Console
{
public:
    Console();
    ~Console();
    HANDLE h_getHandle();
    BOOL b_setHandle(DWORD nStdHandle, HANDLE hHandle);
    void v_setColor(HANDLE hConsoleHandle, int color);

    void v_colOut(std::string text, unsigned char color);

    unsigned short s_getColor(HANDLE hConsole);

    void v_printSuccess(const char* text);
    void v_printSuccess(std::string text);

    void v_printError(const char* text);
    void v_printError(std::string text);
    
    void v_debugCout(const char* text);
    
    void v_printLoad(int rotations);

    void v_clearConsole();

    void v_setCursor(long size, bool visible);
    void v_setCursorPos(short x, short y);

    void v_setTitle(LPCSTR title);
    void v_setTitle(std::string title);
    void v_readLine(HANDLE consoleHandle);
    
    bool b_attachConsole();

    std::vector<int> r_getSize();
    
private:
    HANDLE hHandle;
    void v_printHeader();
    const char* headerTitle = "[brasilconsole]";
};

