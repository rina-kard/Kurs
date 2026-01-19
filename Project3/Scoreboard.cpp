#include "Scoreboard.h"

Scoreboard::Scoreboard(int initialScore) : score(initialScore) {
	if (!font.loadFromFile("arial.ttf")) {
		font.loadFromFile("C:/Windows/Fonts/arial.ttf");
	}

	scoreText.setFont(font);
	scoreText.setCharacterSize(24);
	scoreText.setFillColor(sf::Color::Green);
	updateText();
}

Scoreboard::Scoreboard(const Scoreboard& other) : score(other.score) {
	font = other.font;
	scoreText.setFont(font);
	scoreText.setCharacterSize(other.scoreText.getCharacterSize());
	scoreText.setFillColor(other.scoreText.getFillColor());
	updateText();
}

Scoreboard::~Scoreboard() {}

Scoreboard& Scoreboard::operator=(const Scoreboard& other) {
	if (this != &other) {
		score = other.score;
		font = other.font;
		scoreText.setFont(font);
		scoreText.setCharacterSize(other.scoreText.getCharacterSize());
		scoreText.setFillColor(other.scoreText.getFillColor());
		updateText();
	}
	return *this;
}

void Scoreboard::addScore(int points) {
	score += points;
	updateText();
}

void Scoreboard::reset() {
	score = 0;
	updateText();
}

int Scoreboard::getScore() const {
	return score;
}

void Scoreboard::updateText() {
	scoreText.setString("Score: " + std::to_string(score));
}

void Scoreboard::draw(sf::RenderWindow& window, float x, float y) {
	scoreText.setPosition(x, y);
	window.draw(scoreText);
}

std::string Scoreboard::getFormattedString() const {
	return std::to_string(score) + " pts";
}