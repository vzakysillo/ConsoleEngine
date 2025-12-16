#pragma once
#include "Object.h"

class Bonus : public Object {
	int type;
	int value;
	WORD colour;
	friend struct level;
protected:
	int TYPE() const;
	void TYPE(int type);

	int VALUE() const;
	void VALUE(int value);

public:
	Bonus(int x, int y, Texture& texture, int type, int value, WORD colour);

	void display(const Map& map) const;

};
