#include "stdafx.h"
#include "Game.h"

int main()
{
	Game * game = new Game;
	cout << "Game Created" << endl;

	if (game->Init(1280, 720, "Space Station Rescue"))
	{
		cout << "Game Initialised" << endl;

		cout << "Game Loop Starting" << endl;
		game->Loop();
	}
	else
	{
		cout << "Failed to initialise game" << endl;
	}

	return 0;
}