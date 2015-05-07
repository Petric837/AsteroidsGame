#include "oneUp.h"
#include <SFML/Graphics.hpp>

oneUp::oneUp(float xcoord, float ycoord)
{
	aura.setOutlineColor(sf::Color::White);
	aura.setFillColor(sf::Color::Transparent);
	aura.setPosition(xcoord, ycoord);
	symbol.setPosition(xcoord - 27, ycoord - 24);

	symbol.setPointCount(6);
	symbol.setPoint(0, sf::Vector2f(0, 6));
	symbol.setPoint(1, sf::Vector2f(6, 0));
	symbol.setPoint(2, sf::Vector2f(12, 6));
	symbol.setPoint(3, sf::Vector2f(18, 0));
	symbol.setPoint(4, sf::Vector2f(24, 6));
	symbol.setPoint(5, sf::Vector2f(12, 18));
	symbol.setFillColor(sf::Color::Red);
	symbol.setOutlineThickness(2);
	symbol.setOutlineColor(sf::Color::White);

}

void oneUp::activate(player& player)
{


}