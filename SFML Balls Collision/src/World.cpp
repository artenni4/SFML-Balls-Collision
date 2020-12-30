#include "World.h"

#include <iostream>

#define PI 3.14159265f

World::World()
	: m_entities(0)
{
	std::cout << "World class created" << std::endl;

	float radius = ONE_METER * 0.0572f;
	sf::Vector2f pos = sf::Vector2f(ONE_METER*0.4f, ONE_METER*1.0f);
	physicsData physData = {
		0.170f, //Mass, in kg
		sf::Vector2f(ONE_METER*0.3f, ONE_METER*1.0f), //veolocity, in m/s
		sf::Vector2f(ONE_METER*0.0, ONE_METER*0.0f)  //acceleration, in m/s^2
	};

	m_entities.push_back(Ball(radius, pos, sf::Color::White, physData));
}

World::~World()
{

}

int operator* (sf::Vector2f a, sf::Vector2f b)
{
	return a.x * b.x + a.y * b.y;
}

void World::update(float deltaTimeSeconds)
{
	float rollingResistance;

	for (auto& entity : m_entities)
	{
		//1) Forces
		//трение качения
		if (entity.getPhisicalData().m_veolocity.x != 0.0f || entity.getPhisicalData().m_veolocity.y != 0.0f)
		{
			float weight = entity.getPhisicalData().m_mass * 9.81f;
			float coefficient = 100000.0f / 10.0f / 100.0f; // in meters = 10 mm / 10 / 100

			rollingResistance = coefficient / (entity.getBallRadius() * ONE_METER) * weight;

			float angle;
			if (entity.getPhisicalData().m_veolocity.x != 0)
			{
				angle = atan(entity.getPhisicalData().m_veolocity.y / entity.getPhisicalData().m_veolocity.x);
			}
			else
			{
				if (entity.getPhisicalData().m_veolocity.y > 0)
				{
					angle = -PI / 2;
				}
				else
				{
					angle = PI / 2;
				}
			}


			float newXAcceleration, newYAcceleration;
			newXAcceleration = cos((angle < 0) ? -angle : angle) * rollingResistance;
			newYAcceleration = sin((angle < 0) ? -angle : angle) * rollingResistance;

			//newXAcceleration = cos(angle) * rollingResistance;
			//newYAcceleration = sin(angle) * rollingResistance;

			
			newXAcceleration = (entity.getPhisicalData().m_veolocity.x > 0) ? -newXAcceleration : newXAcceleration;
			newYAcceleration = (entity.getPhisicalData().m_veolocity.y > 0) ? -newYAcceleration : newYAcceleration;

			entity.setAcceleration(sf::Vector2f(newXAcceleration * ONE_METER, newYAcceleration * ONE_METER));

		}
		else
		{
			entity.setAcceleration(sf::Vector2f(0.0f, 0.0f));
		}
		//2) change position

		entity.setPositionLast(entity.getPosition());
		//sf::Vector2f lastPos = entity.getPosition();
		
		//3) update position

		entity.setPosition(entity.getPositionLast() + (entity.getPhisicalData().m_veolocity * deltaTimeSeconds) + (entity.getPhisicalData().m_acceleration * deltaTimeSeconds
			* deltaTimeSeconds * 0.5f));


		//4) update veolocity
		entity.setVeolocity(entity.getPhisicalData().m_veolocity + (entity.getPhisicalData().m_acceleration * deltaTimeSeconds));
		if ((int)entity.getPhisicalData().m_veolocity.x == 0)
			entity.setVeolocity(sf::Vector2f(0.0f, entity.getPhisicalData().m_veolocity.y));
		if ((int)entity.getPhisicalData().m_veolocity.y == 0)
			entity.setVeolocity(sf::Vector2f(entity.getPhisicalData().m_veolocity.x, 0.0f));



		//5) collision detection
		//edges
		float energyLoss = 0.91f;
		if (entity.getPosition().x + entity.getBallRadius() >= WINDOW_WIDTH * ONE_METER || entity.getPosition().x - entity.getBallRadius() <= 0)
		{
			if (entity.getPosition().x + entity.getBallRadius() >= WINDOW_WIDTH * ONE_METER)
			{
				entity.setPosition(WINDOW_WIDTH * ONE_METER - entity.getBallRadius(), entity.getPosition().y);
			}
			else
			{
				entity.setPosition(0 + entity.getBallRadius(), entity.getPosition().y);
			}
			entity.setVeolocity(sf::Vector2f(-1*entity.getPhisicalData().m_veolocity.x * energyLoss, entity.getPhisicalData().m_veolocity.y * energyLoss));
		}
		if (entity.getPosition().y + entity.getBallRadius() >= WINDOW_HEIGHT * ONE_METER || entity.getPosition().y - entity.getBallRadius() <= 0)
		{
			if (entity.getPosition().y + entity.getBallRadius() >= WINDOW_HEIGHT * ONE_METER)
			{
				entity.setPosition(entity.getPosition().x, WINDOW_HEIGHT * ONE_METER - entity.getBallRadius());
			}
			else
			{
				entity.setPosition(entity.getPosition().x, 0 + entity.getBallRadius());
			}
			entity.setVeolocity(sf::Vector2f(entity.getPhisicalData().m_veolocity.x * energyLoss, -1*entity.getPhisicalData().m_veolocity.y * energyLoss));
		}

		//other balls
		for (auto& collisioner : m_entities)
		{
			if (collisioner.getId() == entity.getId())
			{
				continue;
			}

			sf::Vector2f distanse = collisioner.getPosition() - entity.getPosition();
			if (sqrt(distanse.x*distanse.x + distanse.y*distanse.y) <= entity.getBallRadius() + collisioner.getBallRadius()) //if collide
			{
				//1 is entity
				//2 is collisioner
	

				sf::Vector2f newVeo1, newVeo2;
				sf::Vector2f currVeo1 = entity.getPhisicalData().m_veolocity;
				sf::Vector2f currVeo2 = collisioner.getPhisicalData().m_veolocity;

				newVeo1 = currVeo1 - (2 * collisioner.getPhisicalData().m_mass / (collisioner.getPhisicalData().m_mass + entity.getPhisicalData().m_mass) *
					((currVeo1 - currVeo2)*(entity.getPosition() - collisioner.getPosition())) /
					((entity.getPosition() - collisioner.getPosition())*(entity.getPosition() - collisioner.getPosition())) *
					(entity.getPosition() - collisioner.getPosition()));

				newVeo2 = currVeo2 - (2 * entity.getPhisicalData().m_mass / (entity.getPhisicalData().m_mass + collisioner.getPhisicalData().m_mass) *
					((currVeo2 - currVeo1)*(collisioner.getPosition() - entity.getPosition())) /
					((collisioner.getPosition() - entity.getPosition())*(collisioner.getPosition() - entity.getPosition())) *
					(collisioner.getPosition() - entity.getPosition()));

				entity.setVeolocity(newVeo1);
				collisioner.setVeolocity(newVeo2);


				break; //выход из цикла, возможно потом переделать
			}
		}

	}
}

void World::addEntity(const Ball& b)
{
	m_entities.push_back(b);
}



