
#ifndef BULLET_H
#define BULLET_H

#include "player.h"
#include <math.h>
#include <SFML/Graphics.hpp>

class Bullet {
    public:
		float xcoord, ycoord;
		float Vx, Vy;
		int createdTime, ttl;	// ttl = time to live

        Bullet(float x, float y, float angle);

		void updatePosition();
		bool lifespan();

		sf::ConvexShape bullet;		
};

#endif