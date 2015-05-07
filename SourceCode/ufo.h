#ifndef UFO_H
#define UFO_H

#include <SFML/Graphics.hpp>

class ufo {
private:
	float turn, size;
	int xdirection, ydirection;
	double speed;
	int shootTimer;
	bool shootDelay;
public:
	float xcoord, ycoord;
	ufo();
	sf::ConvexShape ship;
	void positionUpdate();
	bool destroyed;
	float shootAngle(float, float);
	bool shootReady;
};

#endif