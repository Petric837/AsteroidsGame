#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "player.h"
#include "bullet.h"
#include "UI.h"
#include "asteroid.h"
#include "ufo.h"
#include "explosion.h"
#include "windows.h"
#include "powerup.h"
#include "juggernaut.h"
#include "slowTime.h"
#include "triShot.h"
#include "oneUp.h"
#include <time.h>
#include <vector>
#include <algorithm>

int main()
{
	//	set an AA level, because i can
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	sf::RenderWindow window(sf::VideoMode(1000, 800), "Asteroids", sf::Style::Default, settings);
	window.setFramerateLimit(100);

	//	sets applications icon
	sf::Image Icon;
	Icon.loadFromFile("icon.bmp");
	window.setIcon(32, 32, Icon.getPixelsPtr());

	int gamestate = 0;  // Controls state of the game
	srand(time(NULL));

	std::vector<Bullet*> bullets;
	std::vector<asteroid*> asteroidList;
	std::vector<explosion*> expList;
	std::vector<powerup*> poweruplist;

	//	loads music, and streams it
	sf::Music music;
	music.openFromFile("tune.ogg");
	music.setVolume(50);
	music.setLoop(true);
	music.play();

	//	loads sounds for shooting, destroying asteroids, and destroying the ship
	sf::SoundBuffer laser_buffer;
	laser_buffer.loadFromFile("photon.ogg");
	sf::Sound laser;
	laser.setBuffer(laser_buffer);

	sf::SoundBuffer asteroid_buffer;
	asteroid_buffer.loadFromFile("asteroid_explosion.ogg");
	sf::Sound asteroid_explosion;
	asteroid_explosion.setBuffer(asteroid_buffer);

	sf::SoundBuffer ship_buffer;
	ship_buffer.loadFromFile("ship_explosion.ogg");
	sf::Sound ship_explosion;
	ship_explosion.setBuffer(ship_buffer);

	//	loading the background image, will be drawn in every gamestate
	sf::Texture background;
	background.loadFromFile("background.png");
	background.setRepeated(true);
	sf::Sprite sprite;
	sprite.setTexture(background);

Begin:

	player * p = new player;
	UI * m = new UI;
	m->createScoreTable();

	ufo * u = NULL;
	bool ufoAppear = false;
	int ufoTimer;
	Bullet * ufoBullet = NULL;

	int level = 1; int lifeCount = 3; int score = 0;
	bool pause = true;

	int asteroidMax = 2;
	int powerupMax = 1;

	asteroidList.push_back(new asteroid(1));
	asteroidList.push_back(new asteroid(2));
	asteroidList.push_back(new asteroid(3));

	while (window.isOpen()) {

		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.clear();



		/********************  Main Menu Stage  ********************/
		if (gamestate == 0) {
			window.draw(sprite);
			asteroidList[0]->positionUpdate();
			asteroidList[1]->positionUpdate();
			asteroidList[2]->positionUpdate();
			window.draw(asteroidList[0]->rock);
			window.draw(asteroidList[1]->rock);
			window.draw(asteroidList[2]->rock);
			window.draw(m->gameTitle);
			window.draw(m->start);
			window.draw(m->highscore);

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) &&    // If highscore button is clicked
				sf::Mouse::getPosition(window).x > m->highscore.getGlobalBounds().left &&
				sf::Mouse::getPosition(window).x < m->highscore.getGlobalBounds().left + m->highscore.getGlobalBounds().width &&
				sf::Mouse::getPosition(window).y > m->highscore.getGlobalBounds().top &&
				sf::Mouse::getPosition(window).y < m->highscore.getGlobalBounds().top + m->highscore.getGlobalBounds().height)
				gamestate = 1;

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) &&  // If start button is clicked
				sf::Mouse::getPosition(window).x > m->start.getGlobalBounds().left &&
				sf::Mouse::getPosition(window).x < m->start.getGlobalBounds().left + m->start.getGlobalBounds().width &&
				sf::Mouse::getPosition(window).y > m->start.getGlobalBounds().top &&
				sf::Mouse::getPosition(window).y < m->start.getGlobalBounds().top + m->start.getGlobalBounds().height) {
				gamestate = 2;  // Enter game stage
				asteroidList.erase(asteroidList.begin());
				asteroidList.erase(asteroidList.begin());  // Erase menu asteroids
				asteroidList.erase(asteroidList.begin());

			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
				gamestate = 2;  // Enter game stage
				asteroidList.erase(asteroidList.begin());
				asteroidList.erase(asteroidList.begin());  // Erase menu asteroids
				asteroidList.erase(asteroidList.begin());
			}
		}



		/********************  HighScore Stage  ********************/
		if (gamestate == 1) {
			window.draw(sprite);
			asteroidList[0]->positionUpdate();
			asteroidList[1]->positionUpdate();
			asteroidList[2]->positionUpdate();
			window.draw(asteroidList[0]->rock);
			window.draw(asteroidList[1]->rock);
			window.draw(asteroidList[2]->rock);
			window.draw(m->highscoreTitle);
			window.draw(m->continueText);
			for (int i = 0; i < 10; i++) {
				window.draw(m->names[i]);
				window.draw(m->scores[i]);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
				gamestate = 0;
		}



		/********************  Level Setup Stage  ********************/
		if (gamestate == 2) {
			window.clear();
			window.draw(sprite);

			//	Clear any powerups that werent picked up in the last round
			poweruplist.clear();
			
			


			while (asteroidList.size() < asteroidMax) {   // Create asteroids dependent on the max number of asteroids
				asteroidList.push_back(new asteroid(rand() % 4 + 1));
			}

			if (u != NULL) {
				delete u;
				u = NULL;
			}
			ufoAppear = false;

			p->reset();  // Reset the player's position
			for (int i = 0; i < asteroidList.size(); i++) {
				window.draw(asteroidList[i]->rock);
			}
			window.draw(p->ship);
			window.draw(m->lives);
			for (int i = 0; i < lifeCount; i++) {
				window.draw(m->life[i]);
			}
			window.draw(m->score);
			window.draw(m->level);
			window.display();
			if (pause) {
				int x = GetTickCount();
				while (GetTickCount() < x + 2000) {}  // Stops the game for the player to get ready
				gamestate = 3;
				pause = false;
			}
			else pause = true;
		}




		/********************  Game Stage  ********************/
		if (gamestate == 3) {
			window.draw(sprite);
			p->positionUpdate();  // Updates position of player
			int powerupTimer = GetTickCount();

			// Updates asteroid positions
			for (int i = 0; i < asteroidList.size(); i++)
			{
				asteroidList[i]->positionUpdate(); \
					window.draw(asteroidList[i]->rock);
			}


			//	updates any power ups that are on screen
			for (int i = 0; i < poweruplist.size(); i++)
			{
				window.draw(poweruplist[i]->aura);
				window.draw(poweruplist[i]->symbol);
			}

			/***********************
			*      UFO Handler     *
			************************/
			if (!ufoAppear) {
				ufoTimer = GetTickCount() + (rand() % 12000 + 8000);
				ufoAppear = true;
			}

			else {
				if (GetTickCount() > ufoTimer && u == NULL)
					u = new ufo;
				else if (GetTickCount() > ufoTimer) {
					u->positionUpdate();

					if (u->shootReady) {
						laser.play();
						ufoBullet = new Bullet(u->xcoord, u->ycoord, u->shootAngle(p->xcoord, p->ycoord));
						bullets.push_back(ufoBullet);
						u->shootReady = false;
					}

					window.draw(u->ship);

					if (u->destroyed) {
						delete u;
						u = NULL;
						ufoAppear = false;
					}
				}
			}



			/**************************
			*      Bullet Handler     *
			***************************/
			static bool stateLastFrame = false;		//bool to determine if key has been pressed within the last frame

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && p->isAlive) {  // Space bar shoots if player is alive
				if (!stateLastFrame) {
					laser.play();
					if (p->triShotActive > 0) {
						bullets.push_back(new Bullet(p->xcoord, p->ycoord, p->angle));	//	middle bullet
						bullets.push_back(new Bullet(p->xcoord, p->ycoord, (p->angle - 50)));	//	left bullet
						bullets.push_back(new Bullet(p->xcoord, p->ycoord, (p->angle + 50)));	//	right bullet
						p->triShotActive -= 1;
					}
					else 
						bullets.push_back(new Bullet(p->xcoord, p->ycoord, p->angle));  // Adds bullet to vector
				}
				stateLastFrame = true;
			}
			else
				stateLastFrame = false;


			for (int i = 0; i < bullets.size(); i++) {

				// every frame, iterate through the vector and update where it will be on screen
				bullets[i]->updatePosition();

				//	every frame, itterate through the vector and draw its updated position
				window.draw(bullets[i]->bullet);

				// clear bullet from vector if it has exceeded its lifetime
				if (bullets[i]->lifespan()) {
					bullets.erase(bullets.begin() + i);
				}

			}


			/************************************
			*      Bullet Collision Handler     *
			*************************************/
			for (int i = 0; i < bullets.size(); i++) {   // Checks all bullets for collisions
				for (int j = 0; j < asteroidList.size(); j++) {  // Checks all asteroids
					if (bullets[i]->bullet.getGlobalBounds().intersects(asteroidList[j]->rock.getGlobalBounds())) { // Bullet hits asteroid
						asteroid_explosion.play();
						

						/************************************
						*         Power up generator        *
						*************************************/

						int pow = rand() % 100 + 1;
						//std::cout << pow << std::endl;
						if (pow >= 1 && pow <= 10) {	//	10% chance on asteroid destruction to drop a powerup

							pow = rand() % 4 + 1;	//	33% chance to be either a triShot, juggernaut, or +1 life power up

							switch (pow) {
								case 1:
									poweruplist.push_back(new triShot(asteroidList[j]->xcoord, asteroidList[j]->ycoord));
									break;
								case 2:
									poweruplist.push_back(new juggernaut(asteroidList[j]->xcoord, asteroidList[j]->ycoord));
									break;
								case 3:
									poweruplist.push_back(new oneUp(asteroidList[j]->xcoord, asteroidList[j]->ycoord));
									break;
								case 4:
									poweruplist.push_back(new slowTime(asteroidList[j]->xcoord, asteroidList[j]->ycoord));
									break;
								default:
									std::cout << "default\n";
							}
						}

						bullets.erase(bullets.begin() + i);   // Remove bullet

						if (asteroidList[j]->asteroidSize != 3) {  // If asteroid is size 1 or 2, break into two smaller rocks
							asteroidList.push_back(new asteroid(asteroidList[j]->xcoord, asteroidList[j]->ycoord, asteroidList[j]->asteroidSize + 1));
							asteroidList.push_back(new asteroid(asteroidList[j]->xcoord, asteroidList[j]->ycoord, asteroidList[j]->asteroidSize + 1));
						}

						expList.push_back(new explosion(asteroidList[j]->xcoord, asteroidList[j]->ycoord, 0));  // Create explosion
						asteroidList.erase(asteroidList.begin() + j);   // Erase asteroid that was hit
						score += 5;    // Update score
						m->updateScore(score);
						goto end;  // Exit nested for loops
					}
				}

				if (u != NULL) { // If ufo is present
					// Bullet hits UFO
					if (bullets[i]->bullet.getGlobalBounds().intersects(u->ship.getGlobalBounds()) && bullets[i] != ufoBullet) {
						ship_explosion.play();
						u->destroyed = true;
						bullets.erase(bullets.begin() + i);   // Remove Bullet
						expList.push_back(new explosion(u->xcoord, u->ycoord, 2));
					}
				}
			}
		end:


			/***************************************************************
			*      Asteroid - Player Collision While Juggernaut Active     *
			***************************************************************/
			for (int i = 0; i < asteroidList.size(); i++)
			{
				if (asteroidList[i]->rock.getGlobalBounds().intersects(p->ship.getGlobalBounds()) && p->juggernautShieldActive)
				{
					if (asteroidList[i]->asteroidSize != 3) {  // If asteroid is size 1 or 2, break into two smaller rocks
						asteroidList.push_back(new asteroid(asteroidList[i]->xcoord, asteroidList[i]->ycoord, asteroidList[i]->asteroidSize + 1));
						asteroidList.push_back(new asteroid(asteroidList[i]->xcoord, asteroidList[i]->ycoord, asteroidList[i]->asteroidSize + 1));
					}
					expList.push_back(new explosion(asteroidList[i]->xcoord, asteroidList[i]->ycoord, 0));  // Create explosion
					asteroidList.erase(asteroidList.begin() + i);   // Erase asteroid that was hit
					score += 5;    // Update score
					m->updateScore(score);
				}
			}


			/***************************************
			*      Asteroid - Player Collision     *
			****************************************/
			for (int i = 0; i < asteroidList.size(); i++) {   // Check all asteroids
				// Collision between asteroid and player
				if (asteroidList[i]->rock.getGlobalBounds().intersects(p->ship.getGlobalBounds()) && !p->shieldActive && p->isAlive) {
					ship_explosion.play();
					p->isAlive = false;   // Player is dead
					expList.push_back(new explosion(p->xcoord, p->ycoord, 1));  // Create explosion
					lifeCount--;  // Decrement life
				}

				// Collision between asteroid and UFO
				if (u != NULL) {
					if (asteroidList[i]->rock.getGlobalBounds().intersects(u->ship.getGlobalBounds())) {
						ship_explosion.play();
						u->destroyed = true;
						expList.push_back(new explosion(u->xcoord, u->ycoord, 2));
					}
				}
			}



			/***********************************
			*      UFO - Player Collisions     *
			************************************/
			if (u != NULL) {
				// UFO and Player collide
				if (u->ship.getGlobalBounds().intersects(p->ship.getGlobalBounds()) && !p->shieldActive && p->isAlive) {
					ship_explosion.play();
					p->isAlive = false;   // Player is dead
					expList.push_back(new explosion(p->xcoord, p->ycoord, 1));  // Create explosion
					lifeCount--;  // Decrement life

					u->destroyed = true;
					expList.push_back(new explosion(u->xcoord, u->ycoord, 2));
				}

				// UFO hits Player with bullet
				if (ufoBullet != NULL) {
					if (p->ship.getGlobalBounds().intersects(ufoBullet->bullet.getGlobalBounds()) && !p->shieldActive && p->isAlive) {
						ship_explosion.play();
						p->isAlive = false;   // Player is dead
						expList.push_back(new explosion(p->xcoord, p->ycoord, 1));  // Create explosion
						lifeCount--;  // Decrement life

						for (int i = 0; i < bullets.size(); i++) {
							if (bullets[i] == ufoBullet)
								bullets.erase(bullets.begin() + i);  // Remove ufo bullet
						}
					}
				}
			}

			/***************************************
			*      Powerup - Player Collision     *
			****************************************/
			for (int i = 0; i < poweruplist.size(); i++) {   // Check all powerups
				// Collision 
				if (poweruplist[i]->aura.getGlobalBounds().intersects(p->ship.getGlobalBounds())) {
					poweruplist[i]->activate(*p);
					if (poweruplist[i] == dynamic_cast<oneUp*>(poweruplist[i])) {
						if (lifeCount < 3)
							lifeCount++;
					}
					poweruplist.erase(poweruplist.begin() + i);   // Erase powerup that was hit

					goto end2;
				}
			}
		end2:

			/******************************
			*      Explosion Handler     *
			******************************/
			if (expList.size() != 0) {
				for (int i = 0; i < expList.size(); i++) {
					for (int j = 0; j < 6; j++) {
						window.draw(expList[i]->particles[j].debris);  // Draw all explosion particles
					}

					if (expList[i]->asteroidExplode()) {    // Asteroid explosion animation is done
						expList.erase(expList.begin() + i);  // Remove explosion
						break;
					}

					else if (expList[i]->ufoExplode()) {    // UFO explosion animation is done
						expList.erase(expList.begin() + i);  // Remove explosion
						break;
					}

					else if (expList[i]->playerExplode()) {   // Player explosion animation is done
						if (lifeCount == 0) {     // End game if all lives are gone
							if (m->isHighScore(score))
								gamestate = 5;
							else
								gamestate = 4;
						}
						expList.erase(expList.begin() + i);   // Remove explosion
						p->isAlive = true;                 // Player is alive
						p->shieldActive = true;            // Shield is active
						p->shieldTimer = GetTickCount();   // Starts timer on shield
						break;
					}
				}
			}


			if (GetTickCount() < p->slowTimeTimer + 3500) {
				for (int i = 0; i < asteroidList.size(); i++) {
					asteroidList[i]->setAccFactor(asteroidList[i]->getOrigAcc() * .25);
				}
			} else {
				for (int i = 0; i < asteroidList.size(); i++) {
					asteroidList[i]->setAccFactor(asteroidList[i]->getOrigAcc());
				}
			}

			if (p->juggernautShieldActive)
			{
				window.draw(p->juggernautShield);
				p->accfactor = .03;
			}
			else
				p->accfactor = .07;


			if (p->shieldActive)
				window.draw(p->shield);

			if (p->isAlive)
				window.draw(p->ship);

			window.draw(m->lives);
			for (int i = 0; i < lifeCount; i++) {
				window.draw(m->life[i]);
			}
			window.draw(m->score);
			window.draw(m->level);

			if (asteroidList.size() == 0) {  // When all asteroids are destroyed
				asteroidMax += 1;
				level++;
				m->updateLevel(level);
				bullets.clear();
				gamestate = 2;  // Load next level
			}

		}	//	end of gamestate 3




		/********************  Cleanup Stage  ********************/
		if (gamestate == 4) {
			bool x = false;
			if (m->isHighScore(score))
				x = true;
			delete p;
			delete m;
			delete u;
			delete ufoBullet;
			bullets.clear();
			asteroidList.clear();
			poweruplist.clear();
			expList.clear();
			if (x)
				gamestate = 1;
			else
				gamestate = 0;
			goto Begin;
		}



		if (gamestate == 5) {
			window.draw(sprite);

			for (int i = 0; i < asteroidList.size(); i++) {
				asteroidList[i]->positionUpdate();
				window.draw(asteroidList[i]->rock);
			}
			m->updateName();
			window.draw(m->newHighScore);
			window.draw(m->nameEntry);
			window.draw(m->typedName);

			static bool stateLastFrame = false;

			if (event.type == sf::Event::TextEntered) {

				if (!stateLastFrame) {
					char c = static_cast<char>(event.text.unicode);
					if (((c >= 'A' && c <= 'z') || (c >= '0' && c <= '9')) && m->name.length() <= 10)
						m->name += c;

					if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace) && m->name.length() > 0)
						m->name = m->name.substr(0, m->name.length() - 1);
				}

				stateLastFrame = true;
			}

			else stateLastFrame = false;

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && m->name.length() > 0) {
				m->insertScore(score);
				gamestate = 4;
			}

		}



		window.display();

		//	close the window with Escape key
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			window.close();

	}

	return 0;
}
