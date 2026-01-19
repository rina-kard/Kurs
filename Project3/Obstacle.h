#pragma once
#include <SFML/Graphics.hpp>
#include <string>

enum class ObstacleType {
	WALL,
	ROCK,
	TREE,
	WATER
};

class Obstacle {
private:
	sf::FloatRect bounds;
	ObstacleType type;
	std::string name;
	sf::RectangleShape shape;
	sf::Sprite treeSprite;

	static sf::Texture* treeTexture;
	static bool treeTextureLoaded;

public:
	Obstacle(float x, float y, float width, float height,
		ObstacleType type, const std::string& name);

	static bool loadTreeTexture(const std::string& filename);

	void draw(sf::RenderWindow& window) const;
	bool intersects(const sf::FloatRect& rect) const;

	sf::FloatRect getBounds() const;
	ObstacleType getType() const;
	std::string getName() const;

	bool intersectsWith(const Obstacle& other) const;
};