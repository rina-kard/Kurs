#include "Fossil.h"
#include <iostream>

int Fossil::totalCreated = 0;
int Fossil::totalCollected = 0;
sf::Texture* Fossil::moneyTexture = nullptr;
bool Fossil::textureLoaded = false;

Fossil::Fossil() : position(0, 0), value(0), collected(false) {
	if (textureLoaded && moneyTexture) {
		sprite.setTexture(*moneyTexture);
		float scaleX = 40.0f / moneyTexture->getSize().x;
		float scaleY = 40.0f / moneyTexture->getSize().y;
		sprite.setScale(scaleX, scaleY);
		sprite.setPosition(position);
	}
	else {
		std::cout << "Warning: Money texture not loaded\n";
	}
	totalCreated++;
}

Fossil::Fossil(float x, float y, int val) :
	position(x, y), value(val), collected(false) {

	if (textureLoaded && moneyTexture) {
		sprite.setTexture(*moneyTexture);
		float scaleX = 40.0f / moneyTexture->getSize().x;
		float scaleY = 40.0f / moneyTexture->getSize().y;
		sprite.setScale(scaleX, scaleY);
		sprite.setPosition(position);
	}
	else {
		std::cout << "Warning: Money texture not loaded\n";
	}
	totalCreated++;
}

Fossil::~Fossil() {}

bool Fossil::loadTexture(const std::string& filename) {
	if (!moneyTexture) {
		moneyTexture = new sf::Texture();
	}

	if (moneyTexture->loadFromFile(filename)) {
		textureLoaded = true;
		std::cout << "Money texture loaded successfully from: " << filename << std::endl;
		return true;
	}
	else {
		textureLoaded = false;
		std::cout << "Failed to load money texture from: " << filename << std::endl;
		return false;
	}
}

void Fossil::draw(sf::RenderWindow& window) const {
	if (!collected) {
		if (textureLoaded && moneyTexture) {
			window.draw(sprite);
		}
		else {
			sf::RectangleShape shape;
			shape.setPosition(position);
			shape.setSize(sf::Vector2f(40, 40));
			shape.setFillColor(sf::Color(255, 215, 0));
			shape.setOutlineThickness(2);
			shape.setOutlineColor(sf::Color(139, 69, 19));
			window.draw(shape);
		}
	}
}

sf::Vector2f Fossil::getPosition() const {
	return position;
}

int Fossil::getValue() const {
	return value;
}

bool Fossil::isCollected() const {
	return collected;
}

void Fossil::collect() {
	collected = true;
	totalCollected++;
}

sf::FloatRect Fossil::getBounds() const {
	if (textureLoaded && moneyTexture) {
		return sprite.getGlobalBounds();
	}
	else {
		return sf::FloatRect(position.x, position.y, 40, 40);
	}
}

int Fossil::getTotalCreated() {
	return totalCreated;
}

int Fossil::getTotalCollected() {
	return totalCollected;
}