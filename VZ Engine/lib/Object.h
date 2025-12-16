#pragma once
//#include "Utility.h"
#include "Map.h"

class Texture {
private:
    vector<vector<char>> img;
public:
    Texture() = delete;
    Texture(const vector<vector<char>>& image);
    Texture(size_t x, size_t y);
    Texture(initializer_list<initializer_list<char>> list);
    Texture(const Texture& other);
    Texture& operator=(const Texture& other);


    size_t sizeY() const;
    size_t sizeX() const;

    const char& operator()(size_t x, size_t y) const;
};


class Animation {
private:
    vector<Texture> sequence;
    int frame;
    Stopwatch frame_timer;

public:
    Animation() = delete;
    Animation(const initializer_list<Texture>& list);

    int FRAME() const;
    void FRAME(int frame);

    Stopwatch& FRAME_TIME();
    const Stopwatch& FRAME_TIME() const;

    const Texture& operator[](int index) const;

    size_t length() const;
};


class Object {
    int hp;
    int x;
    int y;
    bool collision;
    bool damageable;

    friend struct level;
protected:
    Animation sequence;

    int HP() const;
    void HP(int hp);

    int X() const;
    void X(int x);

    int Y() const;
    void Y(int Y);


    bool DAMAGEABLE() const;
    void DAMAGEABLE(bool damageable);


    int sizeX() const;
    int sizeY() const;

    int halfX() const;
    int halfY() const;

    bool collide(const Object& other) const;

    void update_horizontal(int deltaX, int deltaY, const Map& map, int size) const;

    void update_vertical(int deltaX, int deltaY, const Map& map, int size) const;

public:
    Object() = delete;
    Object(int hp, int x, int y, const Animation& sequence, bool collision, bool damageable);
    Object(int hp, int x, int y, const Texture& texture, bool collision, bool damageable);


    void display(const Map& map) const;

    void animation(int animation_speed);

    bool dead() const;

    void clear(const Map& map) const;

};