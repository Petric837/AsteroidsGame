#ifndef SLOWTIME_H
#define SLOWTIME_H

#include "powerup.h" 
#include <SFML/Graphics.hpp>

class slowTime : public powerup{
public:

	slowTime(float, float);
	void activate(player& player);

};
#endif