#ifndef EXPLOSION_H
#define EXPLOSION_H

#include <SFML/Graphics.hpp>

struct particle {
	float xcoord, ycoord;
	sf::ConvexShape debris;
	float angle;
	float Vx, Vy, xN, yN;
	int time;
};

class explosion{
private:
	float accfactor, dragFactor;
public:
	int type;  // Tells what kind of object is exploding.  0 is asteroid, 1 is player
	particle particles[6];
	explosion(float, float, int); // Takes in x and y coordinates with type
	bool asteroidExplode();
	bool playerExplode();
	bool ufoExplode();
};

#endif