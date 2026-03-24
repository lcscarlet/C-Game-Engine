#include "game.h"
#include <SDL.h>
#include <iostream>
#include <SDL_image.h>
#include <glm/glm.hpp>

Game::Game() {
	isRunning = false;
}

Game::~Game() {
	// TODO! 
}

void Game::Initialize() {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
	std::cerr << "Error initalizing SDL." << std::endl;
		return;
	}
	SDL_DisplayMode displayMode;
	SDL_GetCurrentDisplayMode(0, &displayMode);
	windowWidth = 800; //displayMode.w;
	windowHeight = 600; //displayMode.h;

	window = SDL_CreateWindow(
		NULL, 
		SDL_WINDOWPOS_CENTERED, 
		SDL_WINDOWPOS_CENTERED,
		windowWidth,
		windowHeight,
		SDL_WINDOW_BORDERLESS);
	if (!window) {
		std::cerr << "Error creating SDL window." << std::endl;
		return;
	}
	
	// SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
	// might want to change this later to use vsync and hardware acceleration
	 renderer = SDL_CreateRenderer(window, -1, 0);
	if (!renderer) {
		std::cerr << "Error creating SDL renderer." << std::endl;
		return;
	}

	//change this later to 80% of current display mode resolution
	SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
	
	isRunning = true;
}

void Game::Run() {
	Setup();
	while (isRunning) {
		ProcessInput();
		Update();
		Render();
	}
}

void Game::ProcessInput() {
	SDL_Event sdlEvent;
	while (SDL_PollEvent(&sdlEvent))
		switch (sdlEvent.type) {
		case SDL_QUIT:
			isRunning = false;
			break;
		case SDL_KEYDOWN:
			if (sdlEvent.key.keysym.sym == SDLK_ESCAPE)
				isRunning = false;
			break;

		};
}	

glm::vec2 playerPosition;
glm::vec2 playerVelocity;

void Game::Setup(){
	playerPosition = glm::vec2(10.0, 20.0);
	playerVelocity = glm::vec2(0.5, 0.0);
}

void Game::Update() {
	playerPosition.x += playerVelocity.x;
	playerPosition.y += playerVelocity.y;
}

void Game::Render() {
	SDL_SetRenderDrawColor(renderer, 21, 21, 21, 255);
	SDL_RenderClear(renderer);

	//PNG texture loading and rendering will go here
	SDL_Surface* surface = IMG_Load(".assets/images/tank-tiger-right.png");
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	//Destination rectangle to place a texture
	SDL_Rect dstRect = {static_cast<int>(playerPosition.x), 
						static_cast<int>(playerPosition.y), 
						32, 
						32 };

	SDL_RenderCopy(renderer, texture, NULL, &dstRect);

	SDL_DestroyTexture(texture);

	SDL_RenderPresent(renderer);
}

void Game::Destroy() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}