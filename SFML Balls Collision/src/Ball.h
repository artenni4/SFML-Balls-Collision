#pragma once

#include <SFML/Graphics.hpp>

struct physicsData {
	float m_mass;
	sf::Vector2f m_veolocity;
	sf::Vector2f m_acceleration;
};

class Ball
{
public:
	Ball();
	Ball(float radius, const sf::Vector2f& position,
		const sf::Color& color, const physicsData& physicalData);

	Ball(float, float, float, const sf::Color& = sf::Color::Black, const physicsData& = { 1.0f, sf::Vector2f(0, 0), sf::Vector2f(0, 0) });

	const sf::CircleShape& getEntityShape() { return m_shape; };
	const physicsData& getPhisicalData() { return m_physicalData; }
	float getBallRadius() { return m_ballRadius; }
	const sf::Vector2f& getPosition() { return m_position; }
	const sf::Vector2f& getPositionLast() { return m_positionLast; }
	int getId() { return m_id; }

	void setBallRadius(float);
	void setPosition(const sf::Vector2f&);
	void setPosition(float, float);
	void setPositionLast(const sf::Vector2f&);
	void setPhisicalData(const physicsData&);
	void setVeolocity(const sf::Vector2f&);
	void setAcceleration(const sf::Vector2f&);
	void setMass(float);

	static void setStaticId(int id) { s_id = id; }
	void setId(int id) { m_id = id; }

private:
	static int s_id;

	//For render
	sf::CircleShape m_shape;
	sf::Vector2f m_position;
	sf::Vector2f m_positionLast;
	float m_ballRadius;
	int m_id;

	//For phisics
	physicsData m_physicalData;
};
