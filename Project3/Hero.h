#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class Fossil;

class Hero {
private:
	sf::Vector2f position;
	sf::CircleShape shape;
	sf::Sprite sprite;
	sf::Texture texture;
	bool textureLoaded;

	int collectedFossils;
	int totalValue;

	sf::Color originalColor;
	float effectTimer;
	bool isEffectActive;

public:
	Hero(float x, float y);

	bool loadTexture(const std::string& filename);
	void draw(sf::RenderWindow& window) const;
	void update(float deltaTime);

	bool move(sf::Vector2f direction, const std::vector<sf::FloatRect>& obstacles);
	bool canMove(sf::Vector2f newPos, const std::vector<sf::FloatRect>& obstacles) const;

	void collectFossil(Fossil& fossil);
	sf::FloatRect getBounds() const;
	sf::Vector2f getPosition() const;

	int getCollectedCount() const;
	int getTotalValue() const;

	void setColor(sf::Color color);
	void reset(float x, float y); // Добавленный метод
};