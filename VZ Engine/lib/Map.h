#pragma once
#include "Utility.h"


#define mWidth 120
#define mHeight 30


struct Tile
{
	char symbol;
	WORD color : 8;
	Tile() : symbol(' '), color(FG_WHITE) {}
};


class Map {
private:
	vector<vector<Tile>> map;
	string path;
public:
	Map();
	Map(const string& path);

	void load();

	void display() const;

	bool valid_position(COORD c) const;

	Tile& operator()(size_t x, size_t y);
	const Tile& operator()(int x, int y) const;

};

