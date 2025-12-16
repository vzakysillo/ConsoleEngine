#include "Map.h"


//MAP REALIZATION
Map::Map() : map(mHeight, vector<Tile>(mWidth)) {}

Map::Map(const string& path) : map(mHeight, vector<Tile>(mWidth)), path(path) { load(); }

void Map::load()
{
    ifstream fin(path, ios::binary);
    if (!fin)
        throw "Error: Invalid file name";

    for (size_t i = 0; i < mHeight; i++)
        for (size_t j = 0; j < mWidth; j++)
            fin.read(reinterpret_cast<char*>(&map[i][j]), sizeof(map[i][j]));

    fin.close();
}

void Map::display() const
{
    for (short i = 0; i < mHeight; i++) {
        for (short j = 0; j < mWidth; j++) {
            print(map[i][j].symbol, map[i][j].color, { j, i });
        }
    }
}

bool Map::valid_position(COORD c) const
{
    return (c.X >= 0 and c.Y >= 0) and (c.X < mWidth and c.Y < mHeight);
}

Tile& Map::operator()(size_t x, size_t y)
{
    return map[y][x];
}

const Tile& Map::operator()(int x, int y) const
{
    return map[y][x];
}
