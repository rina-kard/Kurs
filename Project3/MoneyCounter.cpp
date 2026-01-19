#include "MoneyCounter.h"

MoneyCounter::MoneyCounter() : money(0) {
	if (!font.loadFromFile("arial.ttf")) {
		font.loadFromFile("C:/Windows/Fonts/arial.ttf");
	}

	moneyText.setFont(font);
	moneyText.setCharacterSize(24);
	moneyText.setFillColor(sf::Color::Yellow);
	updateText();
}

void MoneyCounter::addMoney(int amount) {
	money += amount;
	updateText();
}

bool MoneyCounter::spendMoney(int amount) {
	if (money >= amount) {
		money -= amount;
		updateText();
		return true;
	}
	return false;
}

void MoneyCounter::reset() {
	money = 0;
	updateText();
}

int MoneyCounter::getMoney() const {
	return money;
}

void MoneyCounter::updateText() {
	moneyText.setString("Money: $" + std::to_string(money));
}

void MoneyCounter::draw(sf::RenderWindow& window, float x, float y) {
	moneyText.setPosition(x, y);
	window.draw(moneyText);
}

std::string MoneyCounter::getFormattedString() const {
	return "$" + std::to_string(money);
}