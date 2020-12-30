#include "Application.h"

#include <iostream>


Application::Application()
	: m_window(sf::VideoMode(ONE_METER * WINDOW_WIDTH, ONE_METER * WINDOW_HEIGHT), "Balls Collision", sf::Style::Close), m_world(), m_windowHeight(WINDOW_HEIGHT),
	m_windowWidth(WINDOW_WIDTH)
{
	std::cout << "Application class created\n" << "Window height = " << m_windowHeight
		<< " meters \n" << "Window width = " << m_windowWidth << " meters" << std::endl;

	
}


Application::~Application()
{
	
}

void Application::runLoop()
{
	sf::Clock clock;
	sf::Time deltaTime;

	while (m_window.isOpen())
	{
		deltaTime = clock.restart();

		m_world.update(deltaTime.asSeconds());
		render();

		handleEvents();
	}
}

void Application::render()
{
	m_window.clear(sf::Color(11, 150, 48, 255));

	for (int i = 0; i < m_world.getEntities().size(); i++)
	{
		m_window.draw(m_world.getEntities()[i].getEntityShape());
	}

	m_window.display();
}

void Application::handleEvents()
{
	sf::Event e;

	m_window.pollEvent(e);

	switch (e.type)
	{
	case sf::Event::MouseButtonPressed:
	{
		if (e.mouseButton.button == sf::Mouse::Button::Left)
		{
			for (auto& entity : m_world.getEntities())
			{
				sf::Vector2f pressedPoint;
				pressedPoint.x = e.mouseButton.x;
				pressedPoint.y = e.mouseButton.y;

				sf::Vector2f lengthVec = pressedPoint - entity.getPosition();

				if (sqrt(lengthVec.x*lengthVec.x + lengthVec.y*lengthVec.y) <= entity.getBallRadius())
				{
					//delete ball
					std::cout << "Ball with ID " << entity.getId() << " deleted" << std::endl;
					
					int i = 0;
					for (i = entity.getId() + 1; i < m_world.getEntities().size(); i++)
					{
						m_world.getEntities()[i].setId(i - 1);
					}

					Ball::setStaticId(i - 1);

					m_world.getEntities().erase(m_world.getEntities().begin() + entity.getId());

					m_shouldCreateBall = false;
					m_leftMousePressed = true;
					break; //from for loop
				}
				else if (sqrt(lengthVec.x*lengthVec.x + lengthVec.y*lengthVec.y) <= entity.getBallRadius() * 2) //too few space for another ball
				{
					std::cout << "Too few space!" << std::endl;
					m_shouldCreateBall = false;
					m_leftMousePressed = true;
				}

			}

			if (m_leftMousePressed == false)
			{
				m_leftMousePressed = true;
				m_shouldCreateBall = true;

				m_newBallPos.x = e.mouseButton.x;
				m_newBallPos.y = e.mouseButton.y;
			}
		}

		break;
	}
	case sf::Event::MouseButtonReleased:
	{
		if (e.mouseButton.button == sf::Mouse::Button::Left)
		{
			m_leftMousePressed = false;

			for (auto& entity : m_world.getEntities())
			{
				sf::Vector2f lengthVec = m_newBallPos - entity.getPosition();

				if (sqrt(lengthVec.x*lengthVec.x + lengthVec.y*lengthVec.y) <= entity.getBallRadius() * 2)
				{
					std::cout << "Cannot spawn ball here!" << std::endl;
					m_shouldCreateBall = false;
					break;
				}
			}

			if (m_shouldCreateBall)
			{

				sf::Vector2f ballVeo;
				ballVeo.x = e.mouseButton.x - m_newBallPos.x;
				ballVeo.y = e.mouseButton.y - m_newBallPos.y;
				ballVeo *= 1.5f; //add some speed

				float radius = ONE_METER * 0.0572f;
				srand(time(NULL));
				sf::Color col(rand() % 256, rand() % 256, rand() % 256, 255);
				physicsData p = { 0.170f, ballVeo, sf::Vector2f(0.0f, 0.0f) };

				Ball b(radius, m_newBallPos, col, p);

				m_world.addEntity(b);
			}
		}

		break;
	}
	case sf::Event::Closed:
	{
		m_window.close();
		break;
	}
	}
}