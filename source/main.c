// Simple citro2d untextured shape example
#include <citro2d.h>

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "Game.h"

// #define ENEMY_SIZE 10
// #define SCREEN_SIZE SetVector2f(400, 240)

//---------------------------------------------------------------------------------
int main(int argc, char* argv[]) {
//---------------------------------------------------------------------------------
	// Init libs
	Game g = InitGame(g);

	g.state = _main;

	// Main loop
	while (aptMainLoop() && g.state != _exitGame)
	{
		Input(&g);

		switch (g.state) {
		case _restart:
			g = RestartGame(g);
		case _main:
			StateMainMenu(&g);
			break;
		case _loselife:
			g = LoseHealth(g);
		case _game:
			StateGame(&g);
			break;
		case _gameover:
			StateGameOver(&g);			
			break;
		case _credits:
			StateCreditsMenu(&g);
			break;
		case _paused:
			StatePause(&g);
			break;
		default:
			DeInitGame(g);
			return 0;
			break;
		}

	}

	// Deinit libs
	DeInitGame(g);

	return 0;
}
