#include "triShot.h"
#include <SFML/Graphics.hpp>
#include "windows.h"
#include <iostream>

triShot::triShot(float xcoord, float ycoord)
{
	aura.setOutlineColor(sf::Color(255, 140, 0));
	aura.setFillColor(sf::Color(255, 140, 0));
	aura.setPosition(xcoord, ycoord);
	symbol.setPosition(xcoord-27, ycoord-20);

	symbol.setPointCount(9);
	symbol.setPoint(0, sf::Vector2f(0, -2));
	symbol.setPoint(1, sf::Vector2f(6, 6));
	symbol.setPoint(2, sf::Vector2f(12, -8));
	symbol.setPoint(3, sf::Vector2f(18, 6));
	symbol.setPoint(4, sf::Vector2f(24, -2));
	symbol.setPoint(5, sf::Vector2f(24, 12));
	symbol.setPoint(6, sf::Vector2f(0, 12));
	symbol.setFillColor(sf::Color::White);
	symbol.setOutlineThickness(2);
	symbol.setOutlineColor(sf::Color(255, 140, 0));
	
}

void triShot::activate(player& player)
{

	player.triShotActive = 40;

}