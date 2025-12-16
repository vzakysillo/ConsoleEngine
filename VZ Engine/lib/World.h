#pragma once
#include "Enemy.h"

struct level {
    Map map;
    vector<Object> objs;
    vector<Enemy> enms;
    level(const Map& map, const vector<Object>& objs, const vector<Enemy>& enms) : map(map), objs(objs), enms(enms) {}
};


class World {
private:
    vector<level> world;
public:
    World() = delete;
    World(const initializer_list<level>& world);

    size_t size() const;

    const level& operator[](size_t index) const;
    level& operator[](size_t index);
};