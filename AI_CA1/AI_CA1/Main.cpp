#include "stdafx.h"
#include "Game.h"

int main()
{
	// Create Game
	Game * MainGame = new Game;

	// Initialise Game
	// Check if it is able to be initialised
	if (MainGame->Init(1280, 720, "Game"))
	{
		// Call Game Loop
		MainGame->Loop();
	}
	else
	{
		cout << "Failed to Initialise Game..." << endl;
		cout << "Exiting" << endl;
	}
	


	return 0;
}