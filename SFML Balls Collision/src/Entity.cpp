#include "Entity.h"
#include <iostream>

Entity::Entity()
	: m_position(sf::Vector2f(0.0f, 0.0f))
{
	std::cout << "Basic constructor" << std::endl;
}

