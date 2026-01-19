#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Fossil {
private:
	sf::Vector2f position;
	int value;
	bool collected;
	sf::Sprite sprite;

	static sf::Texture* moneyTexture;
	static bool textureLoaded;
	static int totalCreated;
	static int totalCollected;

public:
	Fossil();
	Fossil(float x, float y, int val);
	~Fossil();

	static bool loadTexture(const std::string& filename);

	void draw(sf::RenderWindow& window) const;
	sf::Vector2f getPosition() const;
	int getValue() const;
	bool isCollected() const;
	void collect();

	sf::FloatRect getBounds() const;

	static int getTotalCreated();
	static int getTotalCollected();
};