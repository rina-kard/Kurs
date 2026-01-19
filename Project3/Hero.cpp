#include "Hero.h"
#include "Fossil.h"
#include <iostream>

Hero::Hero(float x, float y) :
	position(x, y),
	collectedFossils(0),
	totalValue(0),
	textureLoaded(false),
	originalColor(sf::Color(0, 150, 255)),
	effectTimer(0.0f),
	isEffectActive(false) {

	shape.setRadius(20.0f);
	shape.setPosition(position);
	shape.setFillColor(originalColor);
	shape.setOutlineThickness(2.0f);
	shape.setOutlineColor(sf::Color::White);
	shape.setOrigin(20.0f, 20.0f);
}

bool Hero::loadTexture(const std::string& filename) {
	if (texture.loadFromFile(filename)) {
		textureLoaded = true;
		sprite.setTexture(texture);

		float scaleX = 40.0f / texture.getSize().x;
		float scaleY = 40.0f / texture.getSize().y;
		sprite.setScale(scaleX, scaleY);

		sprite.setPosition(position.x - 20.0f, position.y - 20.0f);
		std::cout << "Hero texture loaded successfully from: " << filename << std::endl;
		return true;
	}
	std::cout << "Failed to load hero texture from: " << filename << std::endl;
	return false;
}

void Hero::draw(sf::RenderWindow& window) const {
	if (textureLoaded) {
		window.draw(sprite);
	}
	else {
		window.draw(shape);
	}
}

void Hero::update(float deltaTime) {
	shape.setPosition(position);
	if (textureLoaded) {
		sprite.setPosition(position.x - 20.0f, position.y - 20.0f);
	}

	if (isEffectActive) {
		effectTimer -= deltaTime;
		if (effectTimer <= 0.0f) {
			isEffectActive = false;
			shape.setFillColor(originalColor);
		}
	}
}

bool Hero::move(sf::Vector2f direction, const std::vector<sf::FloatRect>& obstacles) {
	sf::Vector2f newPos = position + direction;

	if (canMove(newPos, obstacles)) {
		position = newPos;
		return true;
	}
	return false;
}

bool Hero::canMove(sf::Vector2f newPos, const std::vector<sf::FloatRect>& obstacles) const {
	float radius = shape.getRadius();
	sf::FloatRect newBounds(
		newPos.x - radius,
		newPos.y - radius,
		radius * 2.0f,
		radius * 2.0f
	);

	for (const auto& obstacle : obstacles) {
		if (newBounds.intersects(obstacle)) {
			return false;
		}
	}

	const float windowWidth = 1200.0f;
	const float windowHeight = 800.0f;

	if (newPos.x < radius || newPos.y < radius ||
		newPos.x > windowWidth - radius || newPos.y > windowHeight - radius) {
		return false;
	}

	return true;
}

void Hero::collectFossil(Fossil& fossil) {
	if (!fossil.isCollected()) {
		fossil.collect();
		collectedFossils++;
		totalValue += fossil.getValue();

		if (!textureLoaded) {
			shape.setFillColor(sf::Color(255, 255, 100));
			isEffectActive = true;
			effectTimer = 0.3f;
		}
	}
}

sf::FloatRect Hero::getBounds() const {
	if (textureLoaded) {
		return sprite.getGlobalBounds();
	}
	else {
		float radius = shape.getRadius();
		return sf::FloatRect(
			position.x - radius,
			position.y - radius,
			radius * 2.0f,
			radius * 2.0f
		);
	}
}

sf::Vector2f Hero::getPosition() const {
	return position;
}

int Hero::getCollectedCount() const {
	return collectedFossils;
}

int Hero::getTotalValue() const {
	return totalValue;
}

void Hero::setColor(sf::Color color) {
	originalColor = color;
	shape.setFillColor(color);
}

// Добавленный метод reset
void Hero::reset(float x, float y) {
	position = sf::Vector2f(x, y);
	collectedFossils = 0;
	totalValue = 0;
	originalColor = sf::Color(0, 150, 255);
	effectTimer = 0.0f;
	isEffectActive = false;

	shape.setPosition(position);
	shape.setFillColor(originalColor);
	shape.setOrigin(20.0f, 20.0f);

	if (textureLoaded) {
		sprite.setPosition(position.x - 20.0f, position.y - 20.0f);
	}
}