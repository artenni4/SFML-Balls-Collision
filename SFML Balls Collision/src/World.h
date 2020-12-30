#pragma once

#include <SFML/Graphics.hpp>
#include "Ball.h"

class World
{
public:
	World();
	~World();
	
	void update(float);
	std::vector<Ball>& getEntities() { return m_entities; }
	void addEntity(const Ball&);
private:
	std::vector<Ball> m_entities;
};