#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Scoreboard {
private:
	int score;
	sf::Text scoreText;
	sf::Font font;

public:
	Scoreboard(int initialScore = 0);
	Scoreboard(const Scoreboard& other);
	~Scoreboard();

	Scoreboard& operator=(const Scoreboard& other);

	void addScore(int points);
	void reset();

	int getScore() const;

	void updateText();
	void draw(sf::RenderWindow& window, float x, float y);

	std::string getFormattedString() const;
};