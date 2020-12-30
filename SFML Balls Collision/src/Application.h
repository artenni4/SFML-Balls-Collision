#pragma once

#include "World.h"

class Application
{
public:
	Application();
	~Application();

	void runLoop();
private:
	float m_windowHeight;
	float m_windowWidth;

	void render();
	void handleEvents();

	World m_world;

	sf::RenderWindow m_window;

	//for adding ball
	bool m_leftMousePressed;
	bool m_shouldCreateBall;
	sf::Vector2f m_newBallPos;
};

