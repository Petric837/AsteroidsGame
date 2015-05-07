#include "slowTime.h"
#include <SFML/Graphics.hpp>
#include "windows.h"
#include <iostream>

slowTime::slowTime(float xcoord, float ycoord)
{
	aura.setOutlineColor(sf::Color(231, 255, 3));
	aura.setFillColor(sf::Color(231, 255, 3));
	aura.setPosition(xcoord, ycoord);
	symbol.setPosition(xcoord - 15, ycoord - 15);

	symbol.setPointCount(6);
	symbol.setPoint(0, sf::Vector2f(0, 0));
	symbol.setPoint(1, sf::Vector2f(30, 0));
	symbol.setPoint(2, sf::Vector2f(15, 15));
	symbol.setPoint(3, sf::Vector2f(30, 30));
	symbol.setPoint(4, sf::Vector2f(0, 30));
	symbol.setPoint(5, sf::Vector2f(15, 15));
	symbol.setFillColor(sf::Color::White);
	symbol.setOutlineThickness(2);
	symbol.setOutlineColor(sf::Color(0, 0, 0));
	symbol.setOrigin(sf::Vector2f(15, 15));
}

void slowTime::activate(player& player)
{
	player.slowTimeTimer = GetTickCount();

}