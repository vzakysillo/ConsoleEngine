#pragma once
#include <Windows.h>
#include <iostream>
#include <chrono>
#include <initializer_list>
#include <list>
#include <vector>
#include <string>
#include <fstream>

using namespace std;
using namespace chrono;


void set_cursor(COORD c);
void set_colour(WORD colour);
void cursor_visible(bool status);
void print(char character, WORD colour, COORD c);
void cprint(const char* str, WORD colour, COORD c);


class Stopwatch {
private:
	high_resolution_clock::time_point start;
	high_resolution_clock::time_point end;
public:
	Stopwatch();

	size_t time() const;
	void reset();
	void update();


	bool operator>(int other) const;
	bool operator==(int other) const;
	bool operator>=(int other) const;

};

class FPS_counter {
private:
	Stopwatch timer;
	size_t frames;
	size_t fps;
public:
	FPS_counter();

	size_t FPS() const;
	void update();
	void show_info() const {
		char title[64];
		sprintf_s(title, sizeof(title), "FPS = %zd", fps);
		SetConsoleTitleA(title);
	}
};

enum Color {
	FG_BLACK = 0x00,
	FG_BLUE = 0x01,
	FG_GREEN = 0x02,
	FG_CYAN = 0x03,
	FG_RED = 0x04,
	FG_MAGENTA = 0x05,
	FG_YELLOW = 0x06,
	FG_WHITE = 0x07,
	FG_bBLACK = 0x08,
	FG_bBLUE = 0x09,
	FG_bGREEN = 0xA,
	FG_bCYAN = 0xB,
	FG_bRED = 0xC,
	FG_bMAGENTA = 0xD,
	FG_bYELLOW = 0xE,
	FG_bWHITE = 0xF,

	BG_BLACK = 0x00,
	BG_BLUE = 0x10,
	BG_GREEN = 0x20,
	BG_CYAN = 0x30,
	BG_RED = 0x40,
	BG_MAGENTA = 0x50,
	BG_YELLOW = 0x60,
	BG_WHITE = 0x70,
	BG_bBLACK = 0x80,
	BG_bBLUE = 0x90,
	BG_bGREEN = 0xA0,
	BG_bCYAN = 0xB0,
	BG_bRED = 0xC0,
	BG_bMAGENTA = 0xD0,
	BG_bYELLOW = 0xE0,
	BG_bWHITE = 0xF0,
};
