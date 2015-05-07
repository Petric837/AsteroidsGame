#ifndef TRISHOT_H
#define TRISHOT_H

#include "powerup.h" 
#include <SFML/Graphics.hpp>

class triShot : public powerup{
public:

	triShot(float,float);
	void activate(player& player);

};
#endif