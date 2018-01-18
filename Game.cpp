#include <stack>

#include <SFML\Graphics.hpp>
#include <SFML\System.hpp>

#include "Game.h"
#include "GameState.h"

/*Constructors and Destructor*/
Game::Game()
{
	this->window.create(sf::VideoMode(800, 600), "CitySim");
	this->window.setFramerateLimit(60);
}


Game::~Game()
{
	//Deleting everything from GameState stack
	while (!this->states.empty())
	{
		popState();
	}
}

//Methods associated with GameState stack
void Game::pushState(GameState * state)
{
	this->states.push(state);

	return;
}

void Game::popState()
{
	delete this->states.top();
	this->states.pop();

	return;
}

void Game::changeState(GameState * state)
{
	if (!this->states.empty())
	{
		popState();
	}
	pushState(state);

	return;
}

GameState * Game::peekState()
{
	if (this->states.empty())
	{
		return nullptr;
	}
	return this->states.top();
}


//Main game loop
void Game::gameLoop()
{
	//Main game clock
	Clock clock;

	while (this->window.isOpen())
	{
		//Elapse time between frames
		Time elapsed = clock.restart();
		//Delta time in seconds
		float dt = elapsed.asSeconds();

		//Handling different states
		if (peekState() == nullptr) continue;

		//Handle input
		peekState()->handleInput();

		//Update according to state
		peekState()->update(dt);

		//Clear window
		this->window.clear(Color::Black);
		
		//Draw next frame
		peekState()->draw(dt);

		//Display frame
		this->window.display();
	}
}
