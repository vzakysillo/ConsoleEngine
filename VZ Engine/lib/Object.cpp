#include "Object.h"



//TEXTURE REALIZATION
Texture::Texture(const vector<vector<char>>& image) :
    img(image) {}

Texture::Texture(size_t x, size_t y) : img(y, vector<char>(x, '\0')) {}

Texture::Texture(initializer_list<initializer_list<char>> list)
{
    for (auto row : list) {
        img.emplace_back(row);
    }
}

Texture::Texture(const Texture& other) : img(other.img) {}

Texture& Texture::operator=(const Texture& other)
{
    if (this != &other)
        img = other.img;

    return *this;
}

size_t Texture::sizeY() const
{
    return img.size();
}

size_t Texture::sizeX() const
{
    return img[0].size();
}

const char& Texture::operator()(size_t x, size_t y) const
{
    return img[y][x];
}



//ANIMATION REALIZAION
Animation::Animation(const initializer_list<Texture>& list) : sequence(list), frame(0), frame_timer() {}

int Animation::FRAME() const
{
    return frame;
}

void Animation::FRAME(int frame)
{
    this->frame = (frame > sequence.size() - 1 ? 0 : frame);
}

Stopwatch& Animation::FRAME_TIME()
{
    return frame_timer;
}

const Stopwatch& Animation::FRAME_TIME() const
{
    return frame_timer;
}

const Texture& Animation::operator[](int index) const
{
    return sequence[index];
}

size_t Animation::length() const
{
    return sequence.size();
}



//OBJECT REALIZATION
Object::Object(int hp, int x, int y, const Animation& sequence, bool collision, bool damageable)
    : hp(hp), x(x), y(y), sequence(sequence), collision(collision), damageable(damageable) {}

Object::Object(int hp, int x, int y, const Texture& texture, bool collision, bool damageable)
    : Object(hp, x, y, Animation({ texture }), collision, damageable) {}

int Object::HP() const
{
    return hp;
}

void Object::HP(int hp)
{
    this->hp = hp;
}

int Object::X() const
{
    return x;
}

void Object::X(int x)
{
    this->x = ((x > mWidth + halfX()) ? mWidth + halfX() : (x < -halfX() - 1) ? -halfX() - 1 : x);
}

int Object::Y() const
{
    return y;
}

void Object::Y(int y)
{
    this->y = ((y > mHeight + halfY()) ? mHeight + halfY() : (y < -halfY() - 1) ? -halfY() - 1 : y);
}

bool Object::DAMAGEABLE() const
{
    return damageable;
}

void Object::DAMAGEABLE(bool damageable)
{
    this->damageable = damageable;
}

int Object::sizeX() const
{
    return int(sequence[sequence.FRAME()].sizeX());
}

int Object::sizeY() const
{
    return int(sequence[sequence.FRAME()].sizeY());
}

int Object::halfX() const
{
    return sizeX() / 2;
}

int Object::halfY() const
{
    return sizeY() / 2;
}

void Object::display(const Map& map) const
{
    COORD c;
    for (int i = 0; i < sizeY(); i++)
    {
        for (int j = 0; j < sizeX(); j++)
        {
            c = { static_cast<short>(x + j - halfX()), static_cast<short>(y + i - halfY()) };
            if (map.valid_position(c))
                print((sequence[sequence.FRAME()](j, i) ? sequence[sequence.FRAME()](j, i) : map(c.X, c.Y).symbol), map(c.X, c.Y).color, c);
        }
    }
}

void Object::animation(int animation_speed)
{
    if (sequence.FRAME_TIME() >= animation_speed) {
        sequence.FRAME(sequence.FRAME() + 1);
        sequence.FRAME_TIME().reset();
    }
}

bool Object::collide(const Object& other) const
{
    if (other.collision != collision) return false;

    return
        (
        (abs(x - other.x) <= halfX() + other.halfX()) &&
        (abs(y - other.y) <= halfY() + other.halfY())
        );
}

void Object::update_horizontal(int deltaX, int deltaY, const Map& map, int size) const
{
    COORD c;

    for (int i = 0; i < size; i++)
    {
        c = { static_cast<short>(X() + deltaX + i), static_cast<short>(Y() + deltaY) };
        if (map.valid_position(c))
            //print(map(c.X, c.Y).symbol, BG_BLACK, c);
            print(map(c.X, c.Y).symbol, map(c.X, c.Y).color, c);
    }
}

void Object::update_vertical(int deltaX, int deltaY, const Map& map, int size) const
{
    COORD c;

    for (int i = 0; i < size; i++)
    {
        c = { static_cast<short>(X() + deltaX), static_cast<short>(Y() + deltaY + i) };
        if (map.valid_position(c))
            print(map(c.X, c.Y).symbol, map(c.X, c.Y).color, c);
        //print(map(c.X, c.Y).symbol, BG_BLACK, c);

    }
}

void Object::clear(const Map& map) const
{
    for (int i = 0; i < sizeY(); i++)
        update_horizontal(-halfX(), -halfY() - i + 2, map, sizeX());
}

bool Object::dead() const
{
    return HP() <= 0;
}
