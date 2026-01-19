#pragma once
#include <vector>
#include <random>
#include "Fossil.h"
#include "Obstacle.h"

class FossilPlacer {
private:
	std::vector<Fossil*> fossils;
	int placedCount;
	static const int MAX_FOSSILS = 10;

	std::mt19937 rng;
	std::uniform_int_distribution<int> valueDist;
	std::uniform_real_distribution<float> posDist;

public:
	FossilPlacer();
	~FossilPlacer();

	Fossil* placeFossil(float minX, float maxX, float minY, float maxY,
		const std::vector<sf::FloatRect>& obstacles,
		const sf::FloatRect& heroBounds);

	void removeCollectedFossils();
	void drawAll(sf::RenderWindow& window);

	std::vector<Fossil*>& getFossils();
	int getPlacedCount() const;

	void demonstratePlacementNew();
};