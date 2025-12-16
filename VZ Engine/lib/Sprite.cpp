#include "Sprite.h"



//SPRITE REALIZATION
Sprite::Sprite(int hp, int x, int y, const Animation& sequence, bool collision, int speed) :
	Sprite(hp, 0, 0, x, y, sequence, collision, speed) {}

Sprite::Sprite(int hp, int dx, int dy, int x, int y, const Animation& sequence, bool collision, int speed) :
	Object(hp, x, y, sequence, collision, true), dx(dx), dy(dy), speed(speed), speed_time(){}

int Sprite::SPEED() const
{
	return speed;
}

void Sprite::SPEED(int speed)
{
	this->speed = speed;
}

int Sprite::DX() const
{
	return dx;
}

void Sprite::DX(int dx)
{
	this->dx = dx;
}

int Sprite::DY() const
{
	return dy;
}

void Sprite::DY(int dy)
{
	this->dy = dy;
}

Stopwatch& Sprite::SPEED_TIME()
{
	return speed_time;
}

const Stopwatch& Sprite::SPEED_TIME() const
{
	return speed_time;
}

void Sprite::move()
{
	speed_time.update();
	if (speed_time >= 1000 / speed) {
		speed_time.reset();
		X(X() + dx);
		Y(Y() + dy);
	}
}

void Sprite::update(const Map& map) const
{
	if (dx == 1)
		update_vertical(-sizeX() / 2 - 1, -sizeY() / 2, map, sizeY());
	else if (dx == -1) 
		update_vertical(sizeX() / 2 + 1, -sizeY() / 2, map, sizeY());
	else if (dy == 1)
		update_horizontal(-sizeX() / 2, -sizeY() / 2 - 1, map, sizeX());
	else if (dy == -1)
		update_horizontal(-sizeX() / 2, sizeY() / 2 + 1, map, sizeX());

	//UPPER LINE
	//update_horizontal(-sizeX() / 2, -sizeY() / 2 - 1, map, sizeX());

	//LOWER LINE
	//update_horizontal(-sizeX() / 2, sizeY() / 2 + 1, map, sizeX());

	//LEFT LINE
	//update_vertical(-sizeX() / 2 - 1, -sizeY() / 2, map, sizeY());

	//RIGHT LINE
	//update_vertical(sizeX() / 2 + 1, -sizeY() / 2, map, sizeY());
}

void Sprite::animation()
{
	if (dx or dy) {
		sequence.FRAME_TIME().update();
		Object::animation(1000 / speed * 2);
	}
	else {
		sequence.FRAME_TIME().reset();
		sequence.FRAME(0);
	}
}

int Sprite::border_collision() const
{

	if (DX() == 1 and X() >= mWidth)
		return 3;
	if (DX() == -1 and X() < 0)
		return 1;
	if (DY() == 1 and Y() >= mHeight)
		return 4;
	if (DY() == -1 and Y() < 0)
		return 2;

	return 0;
}
