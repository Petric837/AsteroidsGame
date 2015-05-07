#include "UI.h"
#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <string>

UI::UI() {
	alienFont.loadFromFile("alienFont.ttf");
	ethnocen.loadFromFile("ethnocen.ttf");

	gameTitle.setString("Asteroids");
	gameTitle.setFont(alienFont);
	gameTitle.setCharacterSize(90);
	gameTitle.setColor(sf::Color(0, 255, 0));
	gameTitle.setPosition(253.f, 170.f);

	start.setString("Start");
	start.setFont(ethnocen);
	start.setCharacterSize(35);
	start.setColor(sf::Color(255, 255, 255));
	start.setPosition(410.f, 450.f);

	highscore.setString("Highscores");
	highscore.setFont(ethnocen);
	highscore.setCharacterSize(35);
	highscore.setColor(sf::Color(255, 255, 255));
	highscore.setPosition(330.f, 550.f);

	highscoreTitle.setString("Highscores");
	highscoreTitle.setFont(ethnocen);
	highscoreTitle.setCharacterSize(45);
	highscoreTitle.setColor(sf::Color(255, 255, 255));
	highscoreTitle.setPosition(50.f, 40.f);

	continueText.setString("(Press space to continue)");
	continueText.setFont(ethnocen);
	continueText.setCharacterSize(14);
	continueText.setColor(sf::Color(255, 255, 255));
	continueText.setPosition(560.f, 60.f);

	lives.setString("Lives:");
	lives.setFont(ethnocen);
	lives.setCharacterSize(20);
	lives.setColor(sf::Color(255, 255, 255));
	lives.setPosition(50.f, 10.f);

	score.setString("Score: 0");
	score.setFont(ethnocen);
	score.setCharacterSize(20);
	score.setColor(sf::Color(255, 255, 255));
	score.setPosition(750.f, 10.f);

	level.setString("Level: 1");
	level.setFont(ethnocen);
	level.setCharacterSize(20);
	level.setColor(sf::Color(255, 255, 255));
	level.setPosition(440.f, 10.f);

	newHighScore.setString("New HighScore!");
	newHighScore.setFont(ethnocen);
	newHighScore.setCharacterSize(40);
	newHighScore.setColor(sf::Color(255, 255, 255));
	newHighScore.setPosition(275.f, 250.f);

	nameEntry.setString("Enter Name:");
	nameEntry.setFont(ethnocen);
	nameEntry.setCharacterSize(25);
	nameEntry.setColor(sf::Color(255, 255, 255));
	nameEntry.setPosition(250.f, 425.f);

	typedName.setFont(ethnocen);
	typedName.setCharacterSize(25);
	typedName.setColor(sf::Color(255, 255, 255));
	typedName.setPosition(510.f, 425.f);

	float x = 150.f;
	for (int i = 0; i < 3; i++) {
		life[i].setPointCount(6);
		life[i].setPoint(0, sf::Vector2f(0, 5));
		life[i].setPoint(1, sf::Vector2f(6, 0));
		life[i].setPoint(2, sf::Vector2f(12, 4));
		life[i].setPoint(3, sf::Vector2f(18, 0));
		life[i].setPoint(4, sf::Vector2f(24, 5));
		life[i].setPoint(5, sf::Vector2f(12, 16));
		life[i].setFillColor(sf::Color::Red);
		life[i].setOutlineThickness(2);
		life[i].setOutlineColor(sf::Color::White);
		life[i].setPosition(x, 12.f);
		x += 35.f;
	}
}

void UI::createScoreTable() {
	std::fstream file;
	std::string record;
	std::string name;
	std::string score;
	int temp;
	file.open("highscores.txt");
	for (int i = 0; i < 10; i++) {
		std::getline(file, record);
		for (int j = 0; j < record.length(); j++) {
			if (record.at(j) == '-')
				temp = j;
		}
		name = record.substr(0, temp);
		score = record.substr((temp + 1), (record.length() - (temp + 1)));
		names[i].setString(name);
		scores[i].setString(score);
		playerScores[i] = std::stoi(score);
		playerNames[i] = name;
	}

	file.close();

	float ycoord = 150.f;
	for (int i = 0; i < 10; i++) {
		names[i].setFont(ethnocen);
		names[i].setCharacterSize(25);
		names[i].setColor(sf::Color(255,255,255));
		names[i].setPosition(80.f, ycoord);
		scores[i].setFont(ethnocen);
		scores[i].setCharacterSize(25);
		scores[i].setColor(sf::Color(255, 255, 255));
		scores[i].setPosition(600.f, ycoord);
		ycoord += 60.f;
	}
}

void UI::updateScore(int x) {
	score.setString("Score: " + std::to_string(x));
}

void UI::updateLevel(int x) {
	level.setString("Level: " + std::to_string(x));
}

bool UI::isHighScore(int pScore) {

	return (pScore > playerScores[9]);

}

void UI::updateName() {
	typedName.setString(name);
}

void UI::insertScore(int newScore) {

	int tableSpot;
	for (int i = 0; i < 10; i++) {
		if (newScore > playerScores[i]) {
			tableSpot = i;
			break;
		}
	}

	int j = 0;
	for (int i = 9; i >= 0; i--) {
		if (i == tableSpot) {
			playerNames[i] = name;
			playerScores[i] = newScore;
			break;
		}
		else {
			playerNames[i] = playerNames[i-1];
			playerScores[i] = playerScores[i-1];
		}
	}

	std::ofstream outfile("highscores.txt");

	for (int i = 0; i < 10; i++) {
		outfile << playerNames[i] << "-" << playerScores[i] << std::endl;
	}

	outfile.close();

}
