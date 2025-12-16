#pragma once
#include "Combat.h"

class Enemy : public Sprite {
    vector<COORD> trajectory;
    size_t trajectoryIndex = 0;
    friend struct level;
public:
    Enemy(int hp, int x, int y, const Animation& sequence, bool collision, int speed, const vector<COORD>& trajectory);

    void movement() override;

    void update(const Map& map) const;

    void clear(const Map& map) const;

    void display(const Map& map) const;

};