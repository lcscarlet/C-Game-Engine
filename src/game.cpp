#include "game.h"
#include <SDL.h>
#include <iostream>
#include <SDL_image.h>
#include <glm/glm.hpp>
#include "logger.h"

#include "ECS.h"





Game::Game() {
	isRunning = false;
	Logger::Log("Game constructor called.");

}

Game::~Game() {
	Logger::Log("Game destructor called.");
}

void Game::Initialize() {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
	Logger::Err("Error initalizing SDL.");
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
		Logger::Err("Error creating SDL window.";
		return;
	}
	
	// SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
	// might want to change this later to use vsync and hardware acceleration
	 renderer = SDL_CreateRenderer(window, -1, 0);
	if (!renderer) {
		Logger::Err("Error creating SDL renderer.");
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

// glm::vec2 playerPosition;
// glm::vec2 playerVelocity;

void Game::Setup(){
	//tank = registry.CreateEntity();
	//tank.AddComponent<TransformComponent>();
	//tank.AddCompnent<BoxColliderComponent>();
	//tank.AddComponent<SpriteComponent>(".assets/images/tank.png");

	// playerPosition = glm::vec2(10.0, 20.0);
	// playerVelocity = glm::vec2(10.0, 5.0);
}


void Game::Update() {

	//setup for delta time. this SDL delay segment enforces the FPS limit from game.h
	//it might be unnessecary but I don't want the game to generate thousands of frames
	// even with delta time.
	int timeToWait = MILLISECS_PER_FRAME - (SDL_GetTicks() - millisecsPreviousFrame);
	if (timeToWait > 0 && timeToWait <= MILLISECS_PER_FRAME) {
		SDL_Delay(timeToWait);
	}

	double deltaTime = (SDL_GetTicks() - millisecsPreviousFrame) / 1000.0;

	//TODO: MovementSystem.Update();
	//CollionSystem.Update();
	//DamageSystem.Update();
	// 
	// 
	// 
	//playerPosition.x += 20 * deltaTime;

	//Previous frame timing
	int millisecsPreviousFrame = SDL_GetTicks();
	
	//playerPosition.x += playerVelocity.x *deltaTime;
	//playerPosition.y += playerVelocity.y *deltaTime;
}

void Game::Render() {
	SDL_SetRenderDrawColor(renderer, 21, 21, 21, 255);
	SDL_RenderClear(renderer);

	SDL_RenderPresent(renderer);
}

void Game::Destroy() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}