#ifndef ONEUP_H
#define ONEUP_H

#include "powerup.h" 
#include <SFML/Graphics.hpp>

class oneUp : public powerup{
public:

	oneUp(float, float);
	void activate(player &player);

};
#endif