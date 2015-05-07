#ifndef JUGGERNAUT_H
#define JUGGERNAUT_H

#include "powerup.h" 
#include <SFML/Graphics.hpp>

class juggernaut : public powerup{
public:

	juggernaut(float, float);
	void activate(player& player);	

};
#endif