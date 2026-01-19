#include "GameWindow.h"
#include <iostream>

GameWindow::GameWindow() :
	window(sf::VideoMode(1200, 800), "Mining Fossils"),
	hero(200.0f, 200.0f),
	gameBounds(0, 0, 1200, 800),
	fossilSpawnTimer(0.0f),
	frameCount(0),
	gameOver(false) {

	gameView.setSize(1200.0f, 800.0f);
	gameView.setCenter(600.0f, 400.0f);

	uiView.setSize(1200.0f, 800.0f);
	uiView.setCenter(600.0f, 400.0f);
}

GameWindow::~GameWindow() {}

bool GameWindow::initialize() {
	if (!font.loadFromFile("arial.ttf")) {
		font.loadFromFile("C:/Windows/Fonts/arial.ttf");
	}

	// Загружаем текстуру для денег
	if (!Fossil::loadTexture("dollar.png")) {
		if (!Fossil::loadTexture("./dollar.png")) {
			if (!Fossil::loadTexture("Project3/dollar.png")) {
				std::cout << "Could not load fossil texture. Using default squares.\n";
			}
		}
	}

	// Загружаем текстуру для деревьев
	if (!Obstacle::loadTreeTexture("tree.png")) {
		if (!Obstacle::loadTreeTexture("./tree.png")) {
			Obstacle::loadTreeTexture("Project3/tree.png");
		}
	}

	// Загружаем текстуру для героя
	if (!hero.loadTexture("hero.png")) {
		if (!hero.loadTexture("./hero.png")) {
			hero.loadTexture("Project3/hero.png");
		}
	}

	fpsText.setFont(font);
	fpsText.setCharacterSize(18);
	fpsText.setFillColor(sf::Color::White);
	fpsText.setPosition(10.0f, 10.0f);

	gameOverText.setFont(font);
	gameOverText.setCharacterSize(48);
	gameOverText.setFillColor(sf::Color::Red);
	gameOverText.setString("GAME OVER\nTouched water!\nPress R to restart");
	gameOverText.setOrigin(gameOverText.getLocalBounds().width / 2,
		gameOverText.getLocalBounds().height / 2);
	gameOverText.setPosition(600.0f, 400.0f);

	setupObstacles();
	spawnInitialFossils();

	return true;
}

void GameWindow::setupObstacles() {
	obstacles.clear();

	// Границы окна
	obstacles.emplace_back(0.0f, 0.0f, 1200.0f, 20.0f, ObstacleType::WALL, "Top wall");
	obstacles.emplace_back(0.0f, 780.0f, 1200.0f, 20.0f, ObstacleType::WALL, "Bottom wall");
	obstacles.emplace_back(0.0f, 20.0f, 20.0f, 760.0f, ObstacleType::WALL, "Left wall");
	obstacles.emplace_back(1180.0f, 20.0f, 20.0f, 760.0f, ObstacleType::WALL, "Right wall");

	// Внутренние стены - расставлены вручную, чтобы избежать пересечений
	obstacles.emplace_back(100.0f, 100.0f, 150.0f, 20.0f, ObstacleType::WALL, "Maze wall 1");
	obstacles.emplace_back(250.0f, 100.0f, 20.0f, 120.0f, ObstacleType::WALL, "Maze wall 2");
	obstacles.emplace_back(270.0f, 240.0f, 20.0f, 80.0f, ObstacleType::WALL, "Maze wall 4");

	// Центральный лабиринт
	obstacles.emplace_back(400.0f, 200.0f, 20.0f, 200.0f, ObstacleType::WALL, "Center wall 1");
	obstacles.emplace_back(400.0f, 200.0f, 150.0f, 20.0f, ObstacleType::WALL, "Center wall 2");
	obstacles.emplace_back(400.0f, 350.0f, 150.0f, 20.0f, ObstacleType::WALL, "Center wall 4");

	// Правый лабиринт
	obstacles.emplace_back(700.0f, 150.0f, 20.0f, 200.0f, ObstacleType::WALL, "Right maze 1");
	obstacles.emplace_back(700.0f, 150.0f, 150.0f, 20.0f, ObstacleType::WALL, "Right maze 2");
	obstacles.emplace_back(850.0f, 150.0f, 20.0f, 250.0f, ObstacleType::WALL, "Right maze 3");


	// Нижний лабиринт
	obstacles.emplace_back(200.0f, 500.0f, 200.0f, 20.0f, ObstacleType::WALL, "Bottom maze 1");
	obstacles.emplace_back(200.0f, 500.0f, 20.0f, 150.0f, ObstacleType::WALL, "Bottom maze 2");
	obstacles.emplace_back(200.0f, 650.0f, 250.0f, 20.0f, ObstacleType::WALL, "Bottom maze 3");
	obstacles.emplace_back(450.0f, 550.0f, 20.0f, 100.0f, ObstacleType::WALL, "Bottom maze 4");

	// Камни (убедимся, что они не на стартовой позиции и не пересекаются со стенами)
	obstacles.emplace_back(150.0f, 400.0f, 40.0f, 40.0f, ObstacleType::ROCK, "Rock 1");
	obstacles.emplace_back(350.0f, 450.0f, 35.0f, 35.0f, ObstacleType::ROCK, "Rock 2");
	obstacles.emplace_back(600.0f, 300.0f, 45.0f, 45.0f, ObstacleType::ROCK, "Rock 3");
	obstacles.emplace_back(800.0f, 450.0f, 40.0f, 40.0f, ObstacleType::ROCK, "Rock 4");
	obstacles.emplace_back(1000.0f, 200.0f, 50.0f, 50.0f, ObstacleType::ROCK, "Rock 5");
	obstacles.emplace_back(950.0f, 600.0f, 35.0f, 35.0f, ObstacleType::ROCK, "Rock 6");

	// Деревья (будут использовать текстуру tree.png если она загружена)
	obstacles.emplace_back(250.0f, 600.0f, 35.0f, 35.0f, ObstacleType::TREE, "Tree 1");
	obstacles.emplace_back(500.0f, 100.0f, 40.0f, 40.0f, ObstacleType::TREE, "Tree 2");
	obstacles.emplace_back(750.0f, 500.0f, 45.0f, 45.0f, ObstacleType::TREE, "Tree 3");
	obstacles.emplace_back(900.0f, 350.0f, 40.0f, 40.0f, ObstacleType::TREE, "Tree 4");

	// Озера (опасные)
	obstacles.emplace_back(50.0f, 550.0f, 120.0f, 30.0f, ObstacleType::WATER, "Dangerous Lake 1");
	obstacles.emplace_back(650.0f, 100.0f, 80.0f, 25.0f, ObstacleType::WATER, "Dangerous Pond 1");
	obstacles.emplace_back(1000.0f, 500.0f, 150.0f, 30.0f, ObstacleType::WATER, "Dangerous River");
	obstacles.emplace_back(500.0f, 500.0f, 80.0f, 40.0f, ObstacleType::WATER, "Poison Lake");
	obstacles.emplace_back(800.0f, 200.0f, 60.0f, 60.0f, ObstacleType::WATER, "Toxic Pool");

	// Вертикальные препятствия
	obstacles.emplace_back(550.0f, 450.0f, 20.0f, 100.0f, ObstacleType::WALL, "Vertical wall 1");
	obstacles.emplace_back(800.0f, 250.0f, 20.0f, 120.0f, ObstacleType::WALL, "Vertical wall 2");
	obstacles.emplace_back(1050.0f, 300.0f, 20.0f, 150.0f, ObstacleType::WALL, "Vertical wall 3");

	// Горизонтальные препятствия
	obstacles.emplace_back(600.0f, 550.0f, 120.0f, 20.0f, ObstacleType::WALL, "Horizontal wall 1");
	obstacles.emplace_back(850.0f, 400.0f, 100.0f, 20.0f, ObstacleType::WALL, "Horizontal wall 2");
	obstacles.emplace_back(200.0f, 300.0f, 80.0f, 20.0f, ObstacleType::WALL, "Horizontal wall 3");

	// Дополнительные препятствия (убедимся, что они не на стартовой позиции)
	obstacles.emplace_back(150.0f, 150.0f, 30.0f, 30.0f, ObstacleType::ROCK, "Rock 7");
	obstacles.emplace_back(750.0f, 100.0f, 30.0f, 30.0f, ObstacleType::TREE, "Tree 5");
	obstacles.emplace_back(950.0f, 100.0f, 40.0f, 40.0f, ObstacleType::ROCK, "Rock 8");
	obstacles.emplace_back(1100.0f, 600.0f, 35.0f, 35.0f, ObstacleType::TREE, "Tree 6");
	obstacles.emplace_back(50.0f, 300.0f, 70.0f, 20.0f, ObstacleType::WALL, "Wall corner");
	obstacles.emplace_back(1000.0f, 100.0f, 20.0f, 100.0f, ObstacleType::WALL, "Wall column");

	sf::FloatRect heroStartRect(180, 180, 40, 40);
	for (const auto& obstacle : obstacles) {
		if (obstacle.getBounds().intersects(heroStartRect)) {
			std::cout << "WARNING: Hero starting position intersects with obstacle: "
				<< obstacle.getName() << std::endl;
		}
	}
}

void GameWindow::spawnInitialFossils() {
	std::vector<sf::FloatRect> obstacleBounds;
	for (const auto& obstacle : obstacles) {
		obstacleBounds.push_back(obstacle.getBounds());
	}

	for (int i = 0; i < 10; i++) {
		fossilPlacer.placeFossil(50.0f, 1150.0f, 50.0f, 750.0f,
			obstacleBounds, hero.getBounds());
	}
}

void GameWindow::run() {
	sf::Clock clock;
	float lastTime = 0.0f;

	while (window.isOpen()) {
		float currentTime = clock.getElapsedTime().asSeconds();
		float deltaTime = currentTime - lastTime;
		lastTime = currentTime;

		frameCount++;
		if (currentTime - fpsClock.getElapsedTime().asSeconds() >= 1.0f) {
			fpsText.setString("FPS: " + std::to_string(frameCount));
			frameCount = 0;
			fpsClock.restart();
		}

		processEvents();
		if (!gameOver) {
			update(deltaTime);
		}
		render();
	}
}

void GameWindow::processEvents() {
	sf::Event event;
	while (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			window.close();
		}

		if (event.type == sf::Event::KeyPressed) {
			if (event.key.code == sf::Keyboard::R) {
				restartGame();
			}

			if (!gameOver) {
				sf::Vector2f direction(0.0f, 0.0f);
				float speed = 5.0f;

				std::vector<sf::FloatRect> obstacleBounds;
				for (const auto& obstacle : obstacles) {
					if (obstacle.getType() != ObstacleType::WATER) {
						obstacleBounds.push_back(obstacle.getBounds());
					}
				}

				if (event.key.code == sf::Keyboard::W ||
					event.key.code == sf::Keyboard::Up) {
					direction.y = -speed;
				}
				else if (event.key.code == sf::Keyboard::S ||
					event.key.code == sf::Keyboard::Down) {
					direction.y = speed;
				}
				else if (event.key.code == sf::Keyboard::A ||
					event.key.code == sf::Keyboard::Left) {
					direction.x = -speed;
				}
				else if (event.key.code == sf::Keyboard::D ||
					event.key.code == sf::Keyboard::Right) {
					direction.x = speed;
				}
				else if (event.key.code == sf::Keyboard::C) {
					static int colorIndex = 0;
					sf::Color colors[] = {
						sf::Color(255, 100, 100),
						sf::Color(100, 255, 100),
						sf::Color(100, 100, 255),
						sf::Color(255, 255, 100),
						sf::Color(255, 100, 255)
					};
					colorIndex = (colorIndex + 1) % 5;
				}

				if (direction.x != 0 || direction.y != 0) {
					hero.move(direction, obstacleBounds);
					checkWaterCollision();
					if (!gameOver) {
						checkCollisions();
					}
				}
			}
		}
	}
}

void GameWindow::update(float deltaTime) {
	if (gameOver) return;

	fossilSpawnTimer += deltaTime;
	if (fossilSpawnTimer >= FOSSIL_SPAWN_INTERVAL) {
		fossilSpawnTimer = 0.0f;

		std::vector<sf::FloatRect> obstacleBounds;
		for (const auto& obstacle : obstacles) {
			if (obstacle.getType() != ObstacleType::WATER) {
				obstacleBounds.push_back(obstacle.getBounds());
			}
		}

		fossilPlacer.placeFossil(50.0f, 1150.0f, 50.0f, 750.0f,
			obstacleBounds, hero.getBounds());
	}

	fossilPlacer.removeCollectedFossils();
	hero.update(deltaTime);
}

void GameWindow::checkCollisions() {
	if (gameOver) return;

	auto& fossils = fossilPlacer.getFossils();

	for (auto fossil : fossils) {
		if (!fossil->isCollected()) {
			if (hero.getBounds().intersects(fossil->getBounds())) {
				miningProcessor.processMining(hero, *fossil, moneyCounter);
				scoreboard.addScore(fossil->getValue());
			}
		}
	}
}

void GameWindow::checkWaterCollision() {
	if (gameOver) return;

	for (const auto& obstacle : obstacles) {
		if (obstacle.getType() == ObstacleType::WATER) {
			if (hero.getBounds().intersects(obstacle.getBounds())) {
				gameOver = true;
				return;
			}
		}
	}
}

void GameWindow::restartGame() {
	gameOver = false;

	// Используем метод reset вместо создания нового объекта
	hero.reset(200.0f, 200.0f);

	// ВАЖНО: Восстанавливаем исходный цвет
	hero.setColor(sf::Color(0, 150, 255));

	moneyCounter.reset();
	scoreboard.reset();
	miningProcessor.resetStatistics();

	auto& fossils = fossilPlacer.getFossils();
	for (auto fossil : fossils) {
		delete fossil;
	}
	fossils.clear();
	spawnInitialFossils();
}

void GameWindow::render() {
	window.clear(sf::Color(30, 30, 60));

	window.setView(gameView);

	for (const auto& obstacle : obstacles) {
		obstacle.draw(window);
	}

	fossilPlacer.drawAll(window);
	hero.draw(window);

	window.setView(uiView);

	moneyCounter.draw(window, 1000.0f, 20.0f);
	scoreboard.draw(window, 1000.0f, 50.0f);

	sf::Text statsText;
	statsText.setFont(font);
	statsText.setCharacterSize(20);
	statsText.setFillColor(sf::Color::White);
	statsText.setPosition(20.0f, 40.0f);
	statsText.setString("Collected: " + std::to_string(hero.getCollectedCount()) +
		"\nTotal value: $" + std::to_string(hero.getTotalValue()) +
		"\nOperations: " + std::to_string(miningProcessor.getProcessedOperations()) +
		"\n\nWARNING: Water is dangerous!");
	window.draw(statsText);

	sf::Text instructionText;
	instructionText.setFont(font);
	instructionText.setCharacterSize(18);
	instructionText.setFillColor(sf::Color::Cyan);
	instructionText.setPosition(20.0f, 180.0f);
	instructionText.setString("Controls: WASD/Arrows\nR - Restart\nAvoid water!");
	window.draw(instructionText);

	sf::Text obstacleCountText;
	obstacleCountText.setFont(font);
	obstacleCountText.setCharacterSize(16);
	obstacleCountText.setFillColor(sf::Color::Yellow);
	obstacleCountText.setPosition(20.0f, 700.0f);

	int waterCount = 0;
	for (const auto& obstacle : obstacles) {
		if (obstacle.getType() == ObstacleType::WATER) {
			waterCount++;
		}
	}

	obstacleCountText.setString("Obstacles: " + std::to_string(obstacles.size()) +
		"\nDangerous lakes: " + std::to_string(waterCount));
	window.draw(obstacleCountText);

	window.draw(fpsText);

	if (gameOver) {
		sf::RectangleShape overlay(sf::Vector2f(1200.0f, 800.0f));
		overlay.setFillColor(sf::Color(0, 0, 0, 180));
		window.draw(overlay);
		window.draw(gameOverText);

		sf::Text finalStats;
		finalStats.setFont(font);
		finalStats.setCharacterSize(24);
		finalStats.setFillColor(sf::Color::White);
		finalStats.setPosition(600.0f, 550.0f);
		finalStats.setOrigin(finalStats.getLocalBounds().width / 2, 0);
		finalStats.setString("Final score: " + std::to_string(scoreboard.getScore()) +
			"\nMoney collected: $" + std::to_string(moneyCounter.getMoney()) +
			"\nFossils collected: " + std::to_string(hero.getCollectedCount()));
		window.draw(finalStats);
	}

	window.display();
}