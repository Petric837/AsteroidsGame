#include "powerup.h"
#include <SFML/Graphics.hpp>

powerup::powerup()
{
	//xcoord = (rand() % 800 + 200) - 100;
	//ycoord = (rand() % 600 + 200) - 100;
	//aura.setPosition(xcoord, ycoord);

	aura.setRadius(20);
	//aura.setFillColor(sf::Color(255, 140, 0));
	aura.setOutlineThickness(3);
	aura.setOrigin(35.f, 35.f);
		
	
}

