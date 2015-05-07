#include "ufo.h"
#include <SFML/Graphics.hpp>
#include <Windows.h>
#define _USE_MATH_DEFINES
#include <math.h>

ufo::ufo() {
	destroyed = false;
	shootReady = false;
	shootDelay = false;
	turn = (rand() % 700) + 50;
	speed = (rand() % 11 + 8) * .05;
	size = (rand() % 8 + 22) * .1;
	if (rand() % 2 == 0) {
		xcoord = -30;
		xdirection = 0;
	}
	else {
		xcoord = 1030;
		xdirection = 1;
	}
	ycoord = rand() % 800;
	ydirection = rand() % 2;
	ship.setPointCount(16);
	ship.setPoint(0, sf::Vector2f(0, 10));
	ship.setPoint(1, sf::Vector2f(20, 10));
	ship.setPoint(2, sf::Vector2f(17, 5));
	ship.setPoint(3, sf::Vector2f(3, 5));
	ship.setPoint(4, sf::Vector2f(0, 10));
	ship.setPoint(5, sf::Vector2f(5, 10));
	ship.setPoint(6, sf::Vector2f(7, 14));
	ship.setPoint(7, sf::Vector2f(13, 14));
	ship.setPoint(8, sf::Vector2f(15, 10));
	ship.setPoint(9, sf::Vector2f(20, 10));
	ship.setPoint(10, sf::Vector2f(17, 5));
	ship.setPoint(11, sf::Vector2f(14, 5));
	ship.setPoint(12, sf::Vector2f(12, 0));
	ship.setPoint(13, sf::Vector2f(8, 0));
	ship.setPoint(14, sf::Vector2f(6, 5));
	ship.setPoint(15, sf::Vector2f(3, 5));
	ship.setOrigin(10, 10);
	ship.setScale(size, size);
	ship.setFillColor(sf::Color(0, 0, 0));
	ship.setOutlineColor(sf::Color(0, 204, 204));
	ship.setOutlineThickness(.5f);
	ship.setPosition(xcoord, ycoord);
}

void ufo::positionUpdate() {
	if (xcoord < -40 || xcoord > 1040)
		destroyed = true;

	if (xdirection == 0)
		xcoord += speed;
	else if (xdirection == 1)
		xcoord -= speed;

	if (ycoord > 760)
		ydirection = 0;
	if (ycoord < 40)
		ydirection = 1;

	if (ydirection == 0) {
		ycoord -= 1;
		if (ycoord < turn) {
			ydirection = 1;
			int temp = 750 - turn;
			turn = (rand() % temp) + turn;
		}
	}
	else if (ydirection == 1) {
		ycoord += 1;
		if (ycoord > turn) {
			ydirection = 0;
			int temp = turn - 50;
			turn = rand() % temp + 50;
		}
	}

	ship.setPosition(xcoord, ycoord);

	if (!shootDelay) {
		shootTimer = GetTickCount() + 2000;
		shootDelay = true;
	}
	else {
		if (GetTickCount() > shootTimer) {
			shootReady = true;
			shootDelay = false;
		}
	}

}

float ufo::shootAngle(float playerX, float playerY) {
	float angle;

	float xDiff = playerX - xcoord;
	float yDiff = playerY - ycoord;

	angle = atan(yDiff / xDiff) * 180 / M_PI;

	if (xcoord > playerX)
		angle += 270;

	else
		angle += 90;

	return (rand() % 51 + angle - 25);

}