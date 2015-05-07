#ifndef POWERUP_H
#define POWERUP_H
#include "player.h"

#include <SFML/Graphics.hpp>

class powerup{
public:
	
	// Spawn point
	float xcoord, ycoord;

	powerup();
	virtual void activate(player& player) = 0;

	sf::CircleShape aura;
	sf::ConvexShape symbol;
};
#endif