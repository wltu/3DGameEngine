#include"Game.h"

int main() {
	Game game("Nice", 1920, 1080, 4, 4, true);

	// Main Loop
	while (!game.getWindowShouldClose()) {
		game.update();
		game.render();
	}

	return 0;
}