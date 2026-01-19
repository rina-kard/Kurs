#include "FossilPlacer.h"
#include <iostream>
#include <new>
#include <algorithm>

FossilPlacer::FossilPlacer() :
	placedCount(0),
	rng(std::random_device()()),
	valueDist(10, 100),
	posDist(50.0f, 750.0f) {}

FossilPlacer::~FossilPlacer() {
	for (auto fossil : fossils) {
		delete fossil;
	}
	fossils.clear();
}

Fossil* FossilPlacer::placeFossil(float minX, float maxX, float minY, float maxY,
	const std::vector<sf::FloatRect>& obstacles,
	const sf::FloatRect& heroBounds) {

	if (fossils.size() >= MAX_FOSSILS) {
		return nullptr;
	}

	for (int attempt = 0; attempt < 100; attempt++) {
		float x = posDist(rng) * (maxX - minX) / 800.0f + minX;
		float y = posDist(rng) * (maxY - minY) / 600.0f + minY;
		int value = valueDist(rng);

		sf::FloatRect fossilBounds(x, y, 40, 40);

		bool collision = false;
		if (fossilBounds.intersects(heroBounds)) {
			continue;
		}

		for (const auto& obstacle : obstacles) {
			if (fossilBounds.intersects(obstacle)) {
				collision = true;
				break;
			}
		}

		for (const auto& existingFossil : fossils) {
			if (!existingFossil->isCollected()) {
				sf::FloatRect existingBounds = existingFossil->getBounds();
				if (fossilBounds.intersects(existingBounds)) {
					collision = true;
					break;
				}
			}
		}

		if (!collision) {
			Fossil* newFossil = new Fossil(x, y, value);
			fossils.push_back(newFossil);
			placedCount++;
			return newFossil;
		}
	}

	return nullptr;
}

void FossilPlacer::removeCollectedFossils() {
	fossils.erase(
		std::remove_if(fossils.begin(), fossils.end(),
			[](Fossil* fossil) {
		if (fossil->isCollected()) {
			delete fossil;
			return true;
		}
		return false;
	}),
		fossils.end()
		);
}

void FossilPlacer::drawAll(sf::RenderWindow& window) {
	for (auto fossil : fossils) {
		fossil->draw(window);
	}
}

std::vector<Fossil*>& FossilPlacer::getFossils() {
	return fossils;
}

int FossilPlacer::getPlacedCount() const {
	return placedCount;
}

void FossilPlacer::demonstratePlacementNew() {
	const int size = sizeof(Fossil);
	char* buffer = new char[size];

	Fossil* fossil = new (buffer) Fossil(200, 200, 75);

	std::cout << "Ископаемое создано через placement new" << std::endl;

	fossil->~Fossil();

	delete[] buffer;
}