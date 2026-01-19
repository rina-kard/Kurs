#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Hero.h"
#include "FossilPlacer.h"
#include "Obstacle.h"
#include "MoneyCounter.h"
#include "Scoreboard.h"
#include "MiningProcessor.h"

class GameWindow {
private:
	sf::RenderWindow window;
	sf::View gameView;
	sf::View uiView;

	Hero hero;
	std::vector<Obstacle> obstacles;
	FossilPlacer fossilPlacer;
	MoneyCounter moneyCounter;
	Scoreboard scoreboard;
	MiningProcessor miningProcessor;

	sf::Font font;
	sf::FloatRect gameBounds;
	float fossilSpawnTimer;
	const float FOSSIL_SPAWN_INTERVAL = 5.0f;

	sf::Text fpsText;
	sf::Clock fpsClock;
	int frameCount;
	sf::Text gameOverText;
	bool gameOver;

public:
	GameWindow();
	~GameWindow();

	bool initialize();
	void run();

private:
	void processEvents();
	void update(float deltaTime);
	void render();

	void setupObstacles();
	void spawnInitialFossils();
	void checkCollisions();
	void checkWaterCollision();
	void restartGame();
};