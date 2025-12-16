#pragma once
#include "Object.h"

class Sprite : public Object {
private:
	int dx;
	int dy;
	int speed;
	Stopwatch speed_time;
	friend struct level;
	friend class World;
	friend class Weapon;
protected:
	int DX() const;
	void DX(int dx);

	int DY() const;
	void DY(int dy);

	int SPEED() const;
	void SPEED(int speed);

	Stopwatch& SPEED_TIME();
	const Stopwatch& SPEED_TIME() const;

	void move();

	Sprite(int hp, int dx, int dy, int x, int y, const Animation& sequence, bool collision, int speed);
public:
	Sprite() = delete;

	Sprite(int hp, int x, int y, const Animation& sequence, bool collision, int speed);

	void update(const Map& map) const;

	virtual void movement() = 0;

	void animation();

	int border_collision() const;
	
};