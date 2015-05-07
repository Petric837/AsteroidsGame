#include "explosion.h"
#include <SFML/Graphics.hpp>
#define _USE_MATH_DEFINES
#include <math.h>
#include "windows.h"

explosion::explosion(float x, float y, int t) {

	type = t;
	particles[1].time = GetTickCount();

	if (type == 0) {
		accfactor = 2.f;
		dragFactor = .02f;
	}

	else if (type == 1) {
		accfactor = 3.f;
		dragFactor = .01f;
	}

	else if (type == 2) {
		accfactor = 2.5f;
		dragFactor = .02f;
	}

	float tempAngle = 30;
	for (int i = 0; i < 6; i++) {
		particles[i].xcoord = x;
		particles[i].ycoord = y;

		if (type == 0) {
			particles[i].debris.setPointCount(3);
			particles[i].debris.setPoint(0, sf::Vector2f(0.f, 0.f));
			particles[i].debris.setPoint(1, sf::Vector2f(0.f, 5.f));
			particles[i].debris.setPoint(2, sf::Vector2f(0.f, 0.f));

			particles[i].debris.setFillColor(sf::Color(255, 153, 0));
			particles[i].debris.setOutlineColor(sf::Color(255, 153, 0));
			particles[i].debris.setOutlineThickness(2.f);

			particles[i].debris.setOrigin(sf::Vector2f(0.f, 1.f));
			particles[i].angle = rand() % 360;
		}

		else if (type == 1) {
			particles[i].debris.setPointCount(4);
			particles[i].debris.setPoint(0, sf::Vector2f(0.f, 0.f));
			particles[i].debris.setPoint(1, sf::Vector2f(25.f, 0.f));
			particles[i].debris.setPoint(2, sf::Vector2f(25.f, 1.f));
			particles[i].debris.setPoint(3, sf::Vector2f(0.f, 1.f));

			particles[i].debris.setFillColor(sf::Color(255, 255, 255));
			particles[i].debris.setOutlineColor(sf::Color(255, 255, 255));
			particles[i].debris.setOutlineThickness(.5f);

			particles[i].debris.setOrigin(sf::Vector2f(10.f, 3.f));
			particles[i].angle = rand() % 360;
		}

		else if (type == 2) {
			particles[i].debris.setPointCount(4);
			particles[i].debris.setPoint(0, sf::Vector2f(0.f, 0.f));
			particles[i].debris.setPoint(1, sf::Vector2f(10.f, 0.f));
			particles[i].debris.setPoint(2, sf::Vector2f(10.f, 10.f));
			particles[i].debris.setPoint(3, sf::Vector2f(0.f, 10.f));

			particles[i].debris.setFillColor(sf::Color(0, 255, 255));
			particles[i].debris.setOutlineColor(sf::Color(0, 255, 255));
			particles[i].debris.setOutlineThickness(.5f);

			particles[i].debris.setOrigin(sf::Vector2f(5.f, 5.f));
			particles[i].angle = tempAngle;
			tempAngle += 60;
		}

		particles[i].debris.setPosition(x, y);
		particles[i].debris.setRotation(particles[i].angle);

		particles[i].xN = static_cast<float>(sin(2 * M_PI * (particles[i].angle / 360)));
		particles[i].yN = static_cast<float>(cos(2 * M_PI * (particles[i].angle / 360)));

		particles[i].Vx = particles[i].xN * accfactor;
		particles[i].Vy = particles[i].yN * accfactor;
	}

}

bool explosion::asteroidExplode() {
	if (type != 0)     // Checks if it should perform this explosion
		return false;
	for (int i = 0; i < 6; i++) {
		particles[i].xcoord += particles[i].Vx;
		particles[i].ycoord += particles[i].Vy;
		particles[i].debris.setPosition(particles[i].xcoord, particles[i].ycoord);
		particles[i].Vx = particles[i].Vx - particles[i].Vx * dragFactor;
		particles[i].Vy = particles[i].Vy - particles[i].Vy * dragFactor;
	}
	return (GetTickCount() > particles[1].time + 850);
}

bool explosion::playerExplode() {
	if (type != 1)     // Checks if it should perform this explosion
		return false;
	for (int i = 0; i < 6; i++) {
		particles[i].xcoord += particles[i].Vx;
		particles[i].ycoord += particles[i].Vy;
		particles[i].debris.setPosition(particles[i].xcoord, particles[i].ycoord);
		particles[i].Vx = particles[i].Vx - particles[i].Vx * dragFactor;
		particles[i].Vy = particles[i].Vy - particles[i].Vy * dragFactor;
	}
	return (GetTickCount() > particles[1].time + 2800);
}

bool explosion::ufoExplode() {
	if (type != 2)     // Checks if it should perform this explosion
		return false;
	for (int i = 0; i < 6; i++) {
		particles[i].xcoord += particles[i].Vx;
		particles[i].ycoord += particles[i].Vy;
		particles[i].debris.setPosition(particles[i].xcoord, particles[i].ycoord);
		particles[i].Vx = particles[i].Vx - particles[i].Vx * dragFactor;
		particles[i].Vy = particles[i].Vy - particles[i].Vy * dragFactor;
	}
	return (GetTickCount() > particles[1].time + 1000);
}
