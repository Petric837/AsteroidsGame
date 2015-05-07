#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>

class player{
private:
	// Velocity
	float Vx, Vy;
public:
	float accfactor, dragfactor;
	float xcoord, ycoord, angle;  // Position of ship and angle
	bool isAlive; // Tells if player is alive or going through death sequence
	bool shieldActive;
	bool juggernautShieldActive;
	bool timeActive; 
	int triShotActive;
	int shieldTimer; // Time til shield runs out
	int juggernautShieldTimer;
	int slowTimeTimer; // Time until slow time powerup runs out
	player();
	void accelerate();  // Controls most movement of ship
	void positionUpdate();  // Deals with momentum and keeps track of position
	sf::ConvexShape ship;
	sf::CircleShape juggernautShield;
	sf::CircleShape shield;
	void reset();
};


#endif