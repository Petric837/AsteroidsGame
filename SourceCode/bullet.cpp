


#include <iostream>
#include "Bullet.h"
#define _USE_MATH_DEFINES
#include "windows.h"
#include <math.h>


Bullet::Bullet(float shipX, float shipY, float angle) {
	//	creates a bullet shape
	bullet.setPointCount(3);
	bullet.setPoint(0, sf::Vector2f(4, 0));
	bullet.setPoint(1, sf::Vector2f(2, 2));
	bullet.setPoint(2, sf::Vector2f(0,0));
	bullet.setFillColor(sf::Color(255, 255, 255));
	bullet.setPosition(shipX, shipY);

	//std::cout << "x: " << shipX << ", " << "y: " << shipY << "angle: " << angle << std::endl;
	
	//	variables for calculating trajectory, setting the position of the bullet, and setting velocity
	float xN = static_cast<float>(sin(2 * M_PI * (angle / 360)));
	float yN = static_cast<float>(-cos(2 * M_PI * (angle / 360)));
	xcoord = shipX;
	ycoord = shipY;
	Vx = xN * 6.9f;
	Vy = yN * 6.9f;
	
	//	time when each bullet is created so we can destroy it later
	createdTime = GetTickCount();
	ttl = 1200;
	
}
//	function that updates position
//	will be called every frame of the game(in main.cpp), to re-position the bullet accordingly
void Bullet::updatePosition() {
	xcoord += Vx;
	ycoord += Vy;
	bullet.setPosition(xcoord, ycoord);
}

bool Bullet::lifespan() {

	return (GetTickCount() - createdTime >= ttl);
}
