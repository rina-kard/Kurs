#include "GameWindow.h"

int main() {
	GameWindow gameWindow;

	if (gameWindow.initialize()) {
		gameWindow.run();
	}

	return 0;
}