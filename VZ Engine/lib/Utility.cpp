#include "Utility.h"


//AUXILIARY FUNCs
void set_cursor(COORD c) {
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void set_colour(WORD colour) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colour);
}

void cursor_visible(bool status)
{
    CONSOLE_CURSOR_INFO structCursorInfo;
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &structCursorInfo);
    structCursorInfo.bVisible = status;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &structCursorInfo);
}

void print(char character, WORD colour, COORD c)
{
    DWORD waste;
    WriteConsoleOutputAttribute(GetStdHandle(STD_OUTPUT_HANDLE), &colour, 1, c, &waste);
    WriteConsoleOutputCharacterA(GetStdHandle(STD_OUTPUT_HANDLE), &character, 1, c, &waste);
}

void cprint(const char* str, WORD colour, COORD c)
{
    set_cursor(c);
    set_colour(colour);
    cout << str;
}


//STOPWATCH REALIZATION
Stopwatch::Stopwatch() : start(high_resolution_clock::now()), end(start) {}

size_t Stopwatch::time() const
{
    return duration_cast<milliseconds>(end - start).count();
}

void Stopwatch::reset()
{
    start = end = high_resolution_clock::now();
}

void Stopwatch::update()
{
    end = high_resolution_clock::now();
}

bool Stopwatch::operator>(int other) const
{
    return time() > other;
}

bool Stopwatch::operator==(int other) const
{
    return time() == other;
}

bool Stopwatch::operator>=(int other) const
{
    return(*this == other) or (*this > other);
}



//FPS_COUNTER REALIZATION
FPS_counter::FPS_counter() : timer(), frames(0), fps(0) {}

size_t FPS_counter::FPS() const
{
    return fps;
}

void FPS_counter::update()
{
    if (timer >= 1000) {
        timer.reset();
        fps = frames;
        frames = 0;
    }
    else {
        timer.update();
        frames++;
    }
}
