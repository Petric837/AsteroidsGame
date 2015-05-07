#ifndef ASTEROID_H
#define ASTEROID_H

#include <SFML/Graphics.hpp>

class asteroid {
private:
	
	// Angle and rotation speed
	float angle;
	// Velocity vectors
	float Vx, Vy, accfactor, origAcc; //dragfactor;
public:
	//3 possible sizes
	int asteroidSize;
	// Location of asteroid
	float xcoord, ycoord;
	asteroid(int);// for large size asteroids
	asteroid::asteroid(float , float, int); //overloaded for smaller asteroids
	~asteroid();
	void positionUpdate();  // Keeps track of position of asteroid
	sf::ConvexShape rock;
	float getOrigAcc();
	void setAccFactor(float);
};
#endif