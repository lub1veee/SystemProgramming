#include <windows.h>
#include <conio.h>
#include <iostream>
using namespace std;

int BufScr()
{
    HANDLE hStdOutOld, hStdOutNew;
    DWORD dwWritten; 
    hStdOutNew = CreateConsoleScreenBuffer(
        GENERIC_READ | GENERIC_WRITE, 
        0, 
        NULL, 
        CONSOLE_TEXTMODE_BUFFER, 
        NULL); 
    if (hStdOutNew == INVALID_HANDLE_VALUE)
    {
        _cputs("Create console screen buffer failed.\n");
        return GetLastError();
    }
    hStdOutOld = GetStdHandle(STD_OUTPUT_HANDLE);
    _cputs("Press any key to set new screen buffer active.\n");
    _getch();
    if (!SetConsoleActiveScreenBuffer(hStdOutNew))
    {
        _cputs("Set new console active screen buffer failed.\n");
        return GetLastError();
    }
    char text[] = "This is a new screen buffer.";
    if (!WriteConsole(
        hStdOutNew, 
        text, 
        sizeof(text), 
        &dwWritten, 
        NULL)) 
        _cputs("Write console output character failed.\n");
    char str[] = "\nPress any key to set old screen buffer.";
    if (!WriteConsole(
        hStdOutNew, 
        str, 
        sizeof(str), 
        &dwWritten, 
        NULL)) 
        _cputs("Write console output character failed.\n");
    _getch();
    if (!SetConsoleActiveScreenBuffer(hStdOutOld))
    {
        _cputs("Set old console active screen buffer failed.\n");
        return GetLastError();
    }
    _cputs("This is an old console screen buffer.\n");
    CloseHandle(hStdOutNew);
    _cputs("Press any key to finish.\n");
    _getch();
    return 0;
}

int BufInform()
{
    HANDLE hStdOut; 
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (!GetConsoleScreenBufferInfo(hStdOut, &csbi))
        std::cout << "Console screen buffer info failed." << std::endl;
    std::cout << "Console screen buffer info: " << std::endl << std::endl;
    std::cout << "A number of columns = " << csbi.dwSize.X << std::endl;
    std::cout << "A number of rows = " << csbi.dwSize.Y << std::endl;
    std::cout << "X cursor coordinate = " << csbi.dwCursorPosition.X << std::endl;
    std::cout << "Y cursor coordinate = " << csbi.dwCursorPosition.Y << std::endl;
    std::cout << "Attributes = " << std::hex << csbi.wAttributes << std::dec << std::endl;
    std::cout << "Window upper corner = "
        << csbi.srWindow.Left << ","
        << csbi.srWindow.Top << std::endl;
    std::cout << "Window lower corner = "
        << csbi.srWindow.Right << ","
        << csbi.srWindow.Bottom << std::endl;
    std::cout << "Maximum number of columns = "
        << csbi.dwMaximumWindowSize.X << std::endl;
    std::cout << "Maximum number of rows = "
        << csbi.dwMaximumWindowSize.Y << std::endl << std::endl;
    return 0;
}

int BufSet()
{
    COORD coord; 
    HANDLE hStdOut;
    hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    std::cout << "Enter new screen buffer size." << std::endl;
    std::cout << "A number of columns: ";
    std::cin >> coord.X;
    std::cout << "A number of rows: ";
    std::cin >> coord.Y;
    if (!SetConsoleScreenBufferSize(hStdOut, coord))
    {
        std::cout << "Set console screen buffer size failed." << std::endl;
        return GetLastError();
    }
    return 0;
}

int ReadWriteConsole()
{
    HANDLE hStdOut, hStdIn; 
    DWORD dwWritten, dwRead;
    char buffer[80]; 
    char str[] = "Input any string:";
    char c;
    hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    hStdIn = GetStdHandle(STD_INPUT_HANDLE);
    if (hStdOut == INVALID_HANDLE_VALUE || hStdIn == INVALID_HANDLE_VALUE)
    {
        cout << "Get standard handle failed." << endl;
        return GetLastError();
    }
    if (!WriteConsole(hStdOut, &str, sizeof(str), &dwWritten, NULL))
    {
        cout << "Write console failed." << endl;
        return GetLastError();
    }
    if (!ReadConsole(hStdIn, &buffer, sizeof(buffer), &dwRead, NULL))
    {
        cout << "Read console failed." << endl;
        return GetLastError();
    }
    cout << "Input any char to exit: ";
    cin >> c;
    return 0;
}

int SetCursor()
{
    char c;
    HANDLE hStdOut; 
    CONSOLE_CURSOR_INFO cci; 
    hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (!GetConsoleCursorInfo(hStdOut, &cci))
        cout << "Get console cursor info failed." << endl;
    cout << "Size of cursor in procents of char= " << cci.dwSize << endl;
    cout << "Visibility of cursor = " << cci.bVisible << endl;
    cout << "Input a new size of cursor (1-100): ";
    cin >> cci.dwSize;
    if (!SetConsoleCursorInfo(hStdOut, &cci))
        cout << "Set console cursor info failed." << endl;
    cout << "Input any char to make the cursor invisible: ";
    cin >> c;
    cci.bVisible = FALSE;
    if (!SetConsoleCursorInfo(hStdOut, &cci))
        cout << "Set console cursor info failed." << endl;
    cout << "Input any char to make the cursor visible: ";
    cin >> c;
    cci.bVisible = TRUE;
    if (!SetConsoleCursorInfo(hStdOut, &cci))
        cout << "Set console cursor info failed." << endl;
    return 0;
}

int Cursor()
{
    char c;
    HANDLE hStdOut; 
    COORD coord; 
    hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    cout << "Input new cursor position." << endl;
    cout << "X = ";
    cin >> coord.X;
    cout << "Y = ";
    cin >> coord.Y;
    if (!SetConsoleCursorPosition(hStdOut, coord))
    {
        cout << "Set cursor position failed." << endl;
        return GetLastError();
    }
    cout << "This is a new position." << endl;
    cout << "Input any char to exit: ";
    cin >> c;
    return 0;
}

int AtrConsol()
{
    char c;
    HANDLE hStdOut;
    WORD wAttribute; 
    DWORD dwLength; 
    DWORD dwWritten; 
    COORD coord; 
    CONSOLE_SCREEN_BUFFER_INFO csbi; 

    cout << "In order to fill console attributes, input any char: ";
    cin >> c;
    hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hStdOut == INVALID_HANDLE_VALUE)
    {
        cout << "Get standard handle failed." << endl;
        return GetLastError();
    }
    if (!GetConsoleScreenBufferInfo(hStdOut, &csbi))
    {
        cout << "Console screen buffer info failed." << endl;
        return GetLastError();
    }

    dwLength = csbi.dwSize.X * csbi.dwSize.Y;
    coord.X = 0;
    coord.Y = 0;
    wAttribute = BACKGROUND_BLUE | BACKGROUND_INTENSITY |
        FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
    if (!FillConsoleOutputAttribute(
        hStdOut, 
        wAttribute,
        dwLength, 
        coord, 
        &dwWritten)) 
    {
        cout << "Fill console output attribute failed." << endl;
        return GetLastError();
    }

    cout << "The fill attributes was changed." << endl;

    return 0;
}

int main()
{
    int choice;
    do
    {
        cout << "1. Create and activate screen buffer" << endl;
        cout << "2. Screen buffer info" << endl;
        cout << "3. Set screen buffer size" << endl;
        cout << "4. ReadConsole and WriteConsole" << endl;
        cout << "5. Cursor info" << endl;
        cout << "6. Set cursor position" << endl;
        cout << "7. Fill console attributes" << endl;
        cout << "0. Exit" << endl;
        cout << "Choice: ";
        cin >> choice;
        switch (choice)
        {
        case 1: BufScr(); break;
        case 2: BufInform(); break;
        case 3: BufSet(); break;
        case 4: ReadWriteConsole(); break;
        case 5: SetCursor(); break;
        case 6: Cursor(); break;
        case 7: AtrConsol(); break;
        }
        cout << endl;
    } while (choice != 0);
    return 0;
}