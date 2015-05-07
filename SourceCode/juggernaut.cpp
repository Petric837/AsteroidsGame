#include "juggernaut.h"
#include <SFML/Graphics.hpp>
#include "windows.h"
#include <iostream>

juggernaut::juggernaut(float xcoord, float ycoord)
{
	aura.setOutlineColor(sf::Color(68, 140, 0));
	aura.setFillColor(sf::Color(68, 140, 0));
	aura.setPosition(xcoord, ycoord);
	symbol.setPosition(xcoord-15, ycoord-15);

	symbol.setPointCount(5);
	symbol.setPoint(0, sf::Vector2f(0, 0));
	symbol.setPoint(1, sf::Vector2f(24, 0));
	symbol.setPoint(2, sf::Vector2f(24, 16));
	symbol.setPoint(3, sf::Vector2f(12, 26));
	symbol.setPoint(4, sf::Vector2f(0, 16));
	symbol.setFillColor(sf::Color::White);
	symbol.setOutlineThickness(2);
	symbol.setOutlineColor(sf::Color::White);
	symbol.setOrigin(sf::Vector2f(12, 10));
}

void juggernaut::activate(player& player)
{
	//std::cout << "im the juggernaut bitch\n";
	player.juggernautShield.setOutlineColor(sf::Color(68, 140, 0));
	player.juggernautShieldActive = true;
	player.juggernautShieldTimer = GetTickCount();

	
}