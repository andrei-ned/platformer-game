#include "Game.h"
#include "MainMenuState.h"

using namespace DirectX;

Game::Game(D3DHandler& d3d, SpriteBatch& spriteBatch) : mCamera(spriteBatch, d3d.GetScreenViewport()) {
	mStateMachine.changeState<MainMenuState>();
}

Game::~Game() {
}

void Game::update(const float deltaTime) {
	mStateMachine.update(deltaTime);
}

void Game::render() {
	mStateMachine.render(mCamera);
}
