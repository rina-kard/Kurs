#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class MoneyCounter {
private:
	int money;
	sf::Text moneyText;
	sf::Font font;

public:
	MoneyCounter();

	void addMoney(int amount);
	bool spendMoney(int amount);
	void reset();

	int getMoney() const;

	void updateText();
	void draw(sf::RenderWindow& window, float x, float y);

	std::string getFormattedString() const;
};