#ifndef UI_H
#define UI_H

#include <SFML/Graphics.hpp>
#include <string>

class UI {
private:
	std::string playerNames[10];
	int playerScores[10];
public:
	sf::Font alienFont;
	sf::Font ethnocen;
	sf::Text gameTitle;
	sf::Text start;
	sf::Text highscore;
	sf::Text highscoreTitle;
	sf::Text continueText;
	sf::Text names[10];
	sf::Text scores[10];
	sf::Text lives;
	sf::Text score;
	sf::Text level;
	sf::Text newHighScore;
	sf::Text nameEntry;
	sf::Text typedName;
	UI();
	void createScoreTable();
	bool isHighScore(int);
	void insertScore(int);
	void updateName();
	void updateScore(int);
	void updateLevel(int);
	sf::ConvexShape life[3];
	std::string name;
};

#endif