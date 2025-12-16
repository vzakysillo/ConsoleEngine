#include "World.h"

World::World(const initializer_list<level>& world) : world(world) {}

size_t World::size() const
{
    return world.size();
}

const level& World::operator[](size_t index) const
{
    return world[index];
}

level& World::operator[](size_t index)
{
    return world[index];
}
