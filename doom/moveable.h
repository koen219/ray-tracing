#pragma once
#include "../../Starfighter/Starfighter/vector2D.h"
#include <SFML/Graphics.hpp>
class moveable
{
public:
	vector2D Position;
	double Rotation;
	char Type;
	moveable() {
		Position = vector2D(0.0, 0.0);
		Rotation = 0.0;
		Type = '0';
	}
	void draw(sf::RenderWindow*);
};

