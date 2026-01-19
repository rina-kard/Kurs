#include "Obstacle.h"
#include <iostream>
#include <random>

sf::Texture* Obstacle::treeTexture = nullptr;
bool Obstacle::treeTextureLoaded = false;

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_real_distribution<> sizeDist(0.8, 1.5);

Obstacle::Obstacle(float x, float y, float width, float height,
	ObstacleType type, const std::string& name) :
	bounds(x, y, width, height), type(type), name(name) {

	shape.setPosition(x, y);

	float actualWidth = width;
	float actualHeight = height;

	if (type == ObstacleType::TREE && treeTextureLoaded && treeTexture) {
		float sizeMultiplier = sizeDist(gen);
		actualWidth = width * sizeMultiplier;
		actualHeight = height * sizeMultiplier;

		bounds = sf::FloatRect(x, y, actualWidth, actualHeight);
		shape.setSize(sf::Vector2f(actualWidth, actualHeight));

		treeSprite.setTexture(*treeTexture);
		float scaleX = actualWidth / treeTexture->getSize().x;
		float scaleY = actualHeight / treeTexture->getSize().y;
		treeSprite.setScale(scaleX, scaleY);
		treeSprite.setPosition(x, y);
	}
	else {
		shape.setSize(sf::Vector2f(actualWidth, actualHeight));

		switch (type) {
		case ObstacleType::WALL:
			shape.setFillColor(sf::Color(100, 100, 100));
			shape.setOutlineColor(sf::Color(70, 70, 70));
			break;
		case ObstacleType::ROCK:
			shape.setFillColor(sf::Color(120, 120, 120));
			shape.setOutlineColor(sf::Color(80, 80, 80));
			break;
		case ObstacleType::TREE:
			shape.setFillColor(sf::Color(34, 139, 34));
			shape.setOutlineColor(sf::Color(0, 100, 0));
			break;
		case ObstacleType::WATER:
			shape.setFillColor(sf::Color(0, 0, 139, 200));
			shape.setOutlineColor(sf::Color(255, 0, 0));
			shape.setOutlineThickness(3);
			break;
		}

		if (type != ObstacleType::WATER) {
			shape.setOutlineThickness(2);
		}
	}
}

bool Obstacle::loadTreeTexture(const std::string& filename) {
	if (!treeTexture) {
		treeTexture = new sf::Texture();
	}

	if (treeTexture->loadFromFile(filename)) {
		treeTextureLoaded = true;
		std::cout << "Tree texture loaded successfully from: " << filename << std::endl;
		return true;
	}
	else {
		treeTextureLoaded = false;
		std::cout << "Failed to load tree texture from: " << filename << std::endl;
		return false;
	}
}

void Obstacle::draw(sf::RenderWindow& window) const {
	if (type == ObstacleType::TREE && treeTextureLoaded && treeTexture) {
		window.draw(treeSprite);
	}
	else {
		window.draw(shape);
	}
}

bool Obstacle::intersects(const sf::FloatRect& rect) const {
	return bounds.intersects(rect);
}

bool Obstacle::intersectsWith(const Obstacle& other) const {
	return bounds.intersects(other.bounds);
}

sf::FloatRect Obstacle::getBounds() const {
	return bounds;
}

ObstacleType Obstacle::getType() const {
	return type;
}

std::string Obstacle::getName() const {
	return name;
}