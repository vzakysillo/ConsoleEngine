#pragma once
#include "PLayer.h"

#define hHeight 5

class Hud {
public:
	void setup(const Player& player);
	void display(const Player& player);
};