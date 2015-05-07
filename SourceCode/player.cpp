#include "player.h"
#include <SFML/Graphics.hpp>
#define _USE_MATH_DEFINES
#include "windows.h"
#include <math.h>

player::player() {
	isAlive = true;
	shieldActive = false;
	juggernautShieldActive = false;
	juggernautShieldTimer = 0;
	triShotActive = 0;
	shieldTimer = 0;
	slowTimeTimer = 0;
	angle = 0;
	accfactor = .07;
	dragfactor = .012;
	Vx = 0;
	Vy = 0;
	xcoord = 500;
	ycoord = 400;
	ship.setPointCount(4);
	ship.setPoint(0, sf::Vector2f(17, 0));
	ship.setPoint(1, sf::Vector2f(0, 38));
	ship.setPoint(2, sf::Vector2f(17, 18));
	ship.setPoint(3, sf::Vector2f(35, 38));
	ship.setFillColor(sf::Color(0, 0, 0));
	ship.setOrigin(17, 19);
	ship.setOutlineThickness(2);
	ship.setOutlineColor(sf::Color(255, 255, 255));
	ship.setPosition(xcoord, ycoord);

	shield.setRadius(35);
	shield.setFillColor(sf::Color::Transparent);
	shield.setOutlineColor(sf::Color(0, 204, 204));
	shield.setOutlineThickness(2.f);
	shield.setOrigin(35.f, 35.f);

	juggernautShield.setRadius(50);
	juggernautShield.setFillColor(sf::Color::Transparent);
	juggernautShield.setOutlineColor(sf::Color(68, 140, 0));
	juggernautShield.setOutlineThickness(4.f);
	juggernautShield.setOrigin(50.f, 50.f);
}

void player::accelerate() {
	// Create a normalized vector in the direction of travel
	float xN = static_cast<float>(sin(2 * M_PI * (angle / 360)));
	float yN = static_cast<float>(cos(2 * M_PI * (angle / 360)));

	// Add to velocity vector
	Vx += xN * accfactor;
	Vy -= yN * accfactor;
}

void player::positionUpdate() {

	if (isAlive) {

		xcoord += Vx;
		ycoord += Vy;
		ship.setPosition(xcoord, ycoord);

		Vx = Vx - Vx * dragfactor;
		Vy = Vy - Vy * dragfactor;

		if (GetTickCount() > shieldTimer + 3500)
			shieldActive = false;

		if (shieldActive)
			shield.setPosition(xcoord, ycoord);

		if (GetTickCount() > juggernautShieldTimer + 5000)
			juggernautShieldActive = false;


		//Flashes when nearly over
		if (GetTickCount() > juggernautShieldTimer + 3800)
			juggernautShield.setOutlineColor(sf::Color::Transparent);
		if (GetTickCount() > juggernautShieldTimer + 4000)
			juggernautShield.setOutlineColor(sf::Color(68, 140, 0));
		if (GetTickCount() > juggernautShieldTimer + 4200)
			juggernautShield.setOutlineColor(sf::Color::Transparent);
		if (GetTickCount() > juggernautShieldTimer + 4400)
			juggernautShield.setOutlineColor(sf::Color(68, 140, 0));
		if (GetTickCount() > juggernautShieldTimer + 4600)
			juggernautShield.setOutlineColor(sf::Color::Transparent);
		if (GetTickCount() > juggernautShieldTimer + 4800)
			juggernautShield.setOutlineColor(sf::Color(68, 140, 0));

		if (juggernautShieldActive)
			juggernautShield.setPosition(xcoord, ycoord);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			angle -= 1.5f;
			ship.setRotation(angle);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			angle += 1.5f;
			ship.setRotation(angle);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			accelerate();

		if (xcoord < 0) {
			ship.setPosition(998.f, ycoord);
			xcoord = 998.f;
		}
		if (xcoord > 1000) {
			ship.setPosition(2.f, ycoord);
			xcoord = 2.f;
		}
		if (ycoord < 0) {
			ship.setPosition(xcoord, 798.f);
			ycoord = 798.f;
		}
		if (ycoord > 800) {
			ship.setPosition(xcoord, 2);
			ycoord = 2;
		}

	}

	else {         // Acceleration is set to 0 when dead
		Vx = 0.f;
		Vy = 0.f;
	}
}

void player::reset() {
	isAlive = true;
	xcoord = 500;
	ycoord = 400;
	angle = 0;
	Vx = 0;
	Vy = 0;
	ship.setPosition(xcoord, ycoord);
	ship.setRotation(angle);
}
