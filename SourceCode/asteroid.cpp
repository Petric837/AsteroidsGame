#include "asteroid.h"
#include <SFML/Graphics.hpp>
#define _USE_MATH_DEFINES
#include <math.h>
#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <random>


asteroid::asteroid(int bound) {

	asteroidSize = 1;
	angle = rand() % 360;
	accfactor = (rand() % 4 + 7)*.1;
	origAcc = accfactor;

	rock.setOutlineColor(sf::Color(255, 255, 255));


	// Choosing spawn point
	
		//int bound = rand() % 4;
		if (bound == 1) {
			xcoord = rand() % 1000;
			ycoord = rand() % 100;
		}
		if (bound == 2) {
			xcoord = 900 + rand() % 100;
			ycoord = rand() % 800;
		}
		if (bound == 3) {
			xcoord = rand() % 1000;
			ycoord = 700 + rand() % 100;
		}
		if (bound == 4) {
			xcoord = rand() % 100;
			ycoord = rand() % 800;
		}

		rock.setPointCount(12);
		
		int variation = rand() % 3 + 1;
		switch (variation)
		{
		case 1:
			rock.setPoint(0, sf::Vector2f(70, 50));
			rock.setPoint(1, sf::Vector2f(100, 30));
			rock.setPoint(2, sf::Vector2f(110, 50));
			rock.setPoint(3, sf::Vector2f(100, 70));
			rock.setPoint(4, sf::Vector2f(120, 90));
			rock.setPoint(5, sf::Vector2f(110, 100));
			rock.setPoint(6, sf::Vector2f(100, 120));
			rock.setPoint(7, sf::Vector2f(70, 120));
			rock.setPoint(8, sf::Vector2f(60, 110));
			rock.setPoint(9, sf::Vector2f(30, 100));
			rock.setPoint(10, sf::Vector2f(30, 50));
			rock.setPoint(11, sf::Vector2f(50, 30));
			break;
		case 2:
			rock.setPoint(0, sf::Vector2f(60, 50));
			rock.setPoint(1, sf::Vector2f(50, 30));
			rock.setPoint(2, sf::Vector2f(80, 23));
			rock.setPoint(3, sf::Vector2f(110, 37));
			rock.setPoint(4, sf::Vector2f(110, 58));
			rock.setPoint(5, sf::Vector2f(92, 70));
			rock.setPoint(6, sf::Vector2f(114, 92));
			rock.setPoint(7, sf::Vector2f(85, 110));
			rock.setPoint(8, sf::Vector2f(76, 100));
			rock.setPoint(9, sf::Vector2f(50, 110));
			rock.setPoint(10, sf::Vector2f(38, 83));
			rock.setPoint(11, sf::Vector2f(40, 50));
			break;
		case 3:
			rock.setPoint(0, sf::Vector2f(70, 50));
			rock.setPoint(1, sf::Vector2f(90, 30));
			rock.setPoint(2, sf::Vector2f(110, 50));
			rock.setPoint(3, sf::Vector2f(90, 60));
			rock.setPoint(4, sf::Vector2f(110, 80));
			rock.setPoint(5, sf::Vector2f(105, 100));
			rock.setPoint(6, sf::Vector2f(66, 96));
			rock.setPoint(7, sf::Vector2f(40, 110));
			rock.setPoint(8, sf::Vector2f(30, 80));
			rock.setPoint(9, sf::Vector2f(40, 70));
			rock.setPoint(10, sf::Vector2f(22, 52));
			rock.setPoint(11, sf::Vector2f(41, 27));
			break;
		}
		rock.setFillColor(sf::Color(0, 0, 0));
		rock.setOrigin(70, 70);
		rock.setOutlineThickness(2);
		//rock.setOutlineColor(sf::Color(0, 204, 102));
		rock.setPosition(xcoord, ycoord);


		// Create a normalized vector in the direction of travel
		float xN = static_cast<float>(sin(2 * M_PI * (angle / 360)));
		float yN = static_cast<float>(cos(2 * M_PI * (angle / 360)));

		// Add to velocity vector (using minus for y because Direct2D uses 0,0 as the top-left corner instead of bottom-left)
		Vx = xN *accfactor;
		Vy = yN *accfactor;
	
}

asteroid::asteroid(float x, float y, int size){
	
	asteroidSize = size;
	xcoord = x;
	ycoord = y;
	angle = rand() % 360;

	// Create a normalized vector in the direction of travel
	float xN = static_cast<float>(sin(2 * M_PI * (angle / 360)));
	float yN = static_cast<float>(cos(2 * M_PI * (angle / 360)));


	rock.setPointCount(12); 
	int variation = rand() % 3 + 1;
	switch (asteroidSize){
	case 2:
		switch (variation)
		{
		case 1:
			rock.setPoint(0, sf::Vector2f(35, 25));
			rock.setPoint(1, sf::Vector2f(50, 15));
			rock.setPoint(2, sf::Vector2f(55, 25));
			rock.setPoint(3, sf::Vector2f(50, 35));
			rock.setPoint(4, sf::Vector2f(60, 45));
			rock.setPoint(5, sf::Vector2f(55, 50));
			rock.setPoint(6, sf::Vector2f(50, 60));
			rock.setPoint(7, sf::Vector2f(35, 60));
			rock.setPoint(8, sf::Vector2f(30, 55));
			rock.setPoint(9, sf::Vector2f(15, 50));
			rock.setPoint(10, sf::Vector2f(15, 25));
			rock.setPoint(11, sf::Vector2f(25, 15));
			break;
		case 2:
			rock.setPoint(0, sf::Vector2f(30, 25));
			rock.setPoint(1, sf::Vector2f(25, 15));
			rock.setPoint(2, sf::Vector2f(40, 11));
			rock.setPoint(3, sf::Vector2f(56, 18));
			rock.setPoint(4, sf::Vector2f(53, 27));
			rock.setPoint(5, sf::Vector2f(46, 35));
			rock.setPoint(6, sf::Vector2f(58, 46));
			rock.setPoint(7, sf::Vector2f(45, 56));
			rock.setPoint(8, sf::Vector2f(39, 50));
			rock.setPoint(9, sf::Vector2f(25, 55));
			rock.setPoint(10, sf::Vector2f(19, 41));
			rock.setPoint(11, sf::Vector2f(20, 25));
			break;
		case 3:
			rock.setPoint(0, sf::Vector2f(35, 24));
			rock.setPoint(1, sf::Vector2f(44, 14));
			rock.setPoint(2, sf::Vector2f(57, 28));
			rock.setPoint(3, sf::Vector2f(46, 32));
			rock.setPoint(4, sf::Vector2f(56, 42));
			rock.setPoint(5, sf::Vector2f(52, 50));
			rock.setPoint(6, sf::Vector2f(33, 47));
			rock.setPoint(7, sf::Vector2f(21, 57));
			rock.setPoint(8, sf::Vector2f(15, 40));
			rock.setPoint(9, sf::Vector2f(20, 37));
			rock.setPoint(10, sf::Vector2f(11, 26));
			rock.setPoint(11, sf::Vector2f(23, 13));
			break;
		}
		rock.setFillColor(sf::Color(0, 0, 0));
		rock.setOrigin(40, 40);
		rock.setOutlineThickness(2);
		//rock.setOutlineColor(sf::Color(160, 0, 85));
		rock.setPosition(xcoord, ycoord);
		accfactor = (13 + rand() % 5)*.1;
		origAcc = accfactor;
		Vx = xN *accfactor;
		Vy = yN *accfactor;
		break;
	case 3:
		switch (variation)
		{
		case 1:
			rock.setPoint(0, sf::Vector2f(17, 12));
			rock.setPoint(1, sf::Vector2f(25, 8));
			rock.setPoint(2, sf::Vector2f(27, 25));
			rock.setPoint(3, sf::Vector2f(25, 17));
			rock.setPoint(4, sf::Vector2f(30, 23));
			rock.setPoint(5, sf::Vector2f(27, 25));
			rock.setPoint(6, sf::Vector2f(25, 33));
			rock.setPoint(7, sf::Vector2f(18, 30));
			rock.setPoint(8, sf::Vector2f(15, 33));
			rock.setPoint(9, sf::Vector2f(8, 30));
			rock.setPoint(10, sf::Vector2f(8, 13));
			rock.setPoint(11, sf::Vector2f(13, 8));
			break;
		case 2:
			rock.setPoint(0, sf::Vector2f(15, 13));
			rock.setPoint(1, sf::Vector2f(13, 8));
			rock.setPoint(2, sf::Vector2f(20, 6));
			rock.setPoint(3, sf::Vector2f(28, 9));
			rock.setPoint(4, sf::Vector2f(28, 14));
			rock.setPoint(5, sf::Vector2f(23, 18));
			rock.setPoint(6, sf::Vector2f(29, 23));
			rock.setPoint(7, sf::Vector2f(23, 27));
			rock.setPoint(8, sf::Vector2f(17, 25));
			rock.setPoint(9, sf::Vector2f(13, 27));
			rock.setPoint(10, sf::Vector2f(9, 21));
			rock.setPoint(11, sf::Vector2f(10, 13));
			break;
		case 3:
			rock.setPoint(0, sf::Vector2f(16, 12));
			rock.setPoint(1, sf::Vector2f(22, 7));
			rock.setPoint(2, sf::Vector2f(27, 14));
			rock.setPoint(3, sf::Vector2f(26, 18));
			rock.setPoint(4, sf::Vector2f(28, 22));
			rock.setPoint(5, sf::Vector2f(26, 24));
			rock.setPoint(6, sf::Vector2f(17, 28));
			rock.setPoint(7, sf::Vector2f(12, 28));
			rock.setPoint(8, sf::Vector2f(8, 20));
			rock.setPoint(9, sf::Vector2f(10, 19));
			rock.setPoint(10, sf::Vector2f(6, 14));
			rock.setPoint(11, sf::Vector2f(13, 7));
			break;
		}
		rock.setFillColor(sf::Color(0, 0, 0));
		rock.setOrigin(20, 20);
		rock.setOutlineThickness(2);
		//rock.setOutlineColor(sf::Color(178, 102, 255));
		rock.setPosition(xcoord, ycoord);
		accfactor = (16 + rand() % 5)*.1;
		origAcc = accfactor;
		Vx = xN *accfactor;
		Vy = yN *accfactor;
		break;
	
	}
}

asteroid::~asteroid()
{
	std::cout << "died";


}


void asteroid::positionUpdate() {

	float xN = static_cast<float>(sin(2 * M_PI * (angle / 360)));
	float yN = static_cast<float>(cos(2 * M_PI * (angle / 360)));

	Vx = xN *accfactor;
	Vy = yN *accfactor;

	xcoord += Vx;
	ycoord += Vy;
	rock.setPosition(xcoord, ycoord);

	if (xcoord < 0) {
		rock.setPosition(998, ycoord);
		xcoord = 998;
	}
	if (xcoord > 1000) {
		rock.setPosition(2, ycoord);
		xcoord = 2;
	}
	if (ycoord < 0) {
		rock.setPosition(xcoord, 798);
		ycoord = 798;
	}
	if (ycoord > 800) {
		rock.setPosition(xcoord, 2);
		ycoord = 2;
	}
}

float asteroid::getOrigAcc() {
	return origAcc;
}

void asteroid::setAccFactor(float newAcc) {
	accfactor = newAcc;
}