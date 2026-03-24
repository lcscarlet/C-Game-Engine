#pragma once
#ifndef GAME_H
#define GAME_H
#include <SDL.h>


class Game {
private:
	bool isRunning;
	SDL_Window* window;
	SDL_Renderer* renderer;

public:
	Game();
	~Game();
	void Initialize();
	void Run();
	void Setup();
	void ProcessInput();
	void Update();
	void Render();
	void Destroy();

	//might want to change this to uint or size_t later on
	int windowWidth;
	int windowHeight;

};

#endif