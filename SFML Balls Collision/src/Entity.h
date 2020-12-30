#pragma once

#include <SFML/Graphics.hpp>

class Entity
{
public:
	Entity();

	virtual sf::Shape& getEntityShape() = 0;
	sf::Vector2f& getPosition() { return m_position; }
private:
	sf::Vector2f m_position;
};

