#pragma once
#include <stack>
#include <SFML\Graphics.hpp>

class GameState;

using namespace sf;

class Game
{
public:
	/*Constructors and Destructor*/
	Game();
	~Game();

	//Stack holding game states
	std::stack<GameState*> states;

	RenderWindow window;

	//Methods associated with GameState stack
	void pushState(GameState* state);
	void popState();
	void changeState(GameState* state);
	GameState* peekState();

	//Main game loop
	void gameLoop();
};

