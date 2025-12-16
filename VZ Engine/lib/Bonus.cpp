#include "Bonus.h"


//BONUS REALIZATION
int Bonus::TYPE() const
{
	return type;
}

void Bonus::TYPE(int type)
{
	this->type = type;
}

int Bonus::VALUE() const
{
	return value;
}

void Bonus::VALUE(int value)
{
	this->value = value;
}

Bonus::Bonus(int x, int y, Texture& texture, int type, int value, WORD colour)
	: Object(1, x, y, texture, 1, false), type(type), value(value), colour(colour) {}

void Bonus::display(const Map& map) const
{
	COORD c;
	for (int i = 0; i < sizeY(); i++)
	{
		for (int j = 0; j < sizeX(); j++)
		{
			c = { static_cast<short>(X() + j - halfX()), static_cast<short>(Y() + i - halfY()) };
			if (map.valid_position(c))
				print((sequence[sequence.FRAME()](j, i) ? sequence[sequence.FRAME()](j, i) : map(c.X, c.Y).symbol), colour, c);
		}
	}
}

