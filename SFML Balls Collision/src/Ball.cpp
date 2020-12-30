#include "Ball.h"

#include <iostream>

Ball::Ball()
{

}

Ball::Ball(float radius, const sf::Vector2f& pos, const sf::Color& color, const physicsData& phyData)
	: m_ballRadius(radius), m_position(pos), m_id(s_id++)
{
	m_shape.setFillColor(color);
	m_shape.setOutlineThickness(1.0f);
	m_shape.setOutlineColor(sf::Color::Black);
	m_shape.setPosition(sf::Vector2f(pos.x - radius, pos.y - radius));
	m_shape.setRadius(radius);

	setPhisicalData(phyData);

	std::cout << "Created ball id=" << m_id << std::endl;
	std::cout << "Radius = " << m_ballRadius / ONE_METER << " meters" << std::endl;

}

Ball::Ball(float radius, float posX, float posY, const sf::Color& color, const physicsData& phyData)
{
	Ball::Ball(radius, sf::Vector2f(posX, posY), color, phyData);
}

void Ball::setBallRadius(float radius)
{
	m_ballRadius = radius;
	m_shape.setRadius(radius);
}

void Ball::setPosition(const sf::Vector2f & pos)
{
	m_position = pos;
	m_shape.setPosition(sf::Vector2f(pos.x - m_ballRadius, pos.y - m_ballRadius));
}

void Ball::setPosition(float posX, float posY)
{
	m_position = sf::Vector2f(posX, posY);
	m_shape.setPosition(sf::Vector2f(posX - m_ballRadius, posY - m_ballRadius));
}

void Ball::setPositionLast(const sf::Vector2f& pos)
{
	m_positionLast = pos;
}

void Ball::setPhisicalData(const physicsData& data)
{
	m_physicalData.m_acceleration = data.m_acceleration;
	m_physicalData.m_mass = data.m_mass;
	m_physicalData.m_veolocity = data.m_veolocity;
}

void Ball::setVeolocity(const sf::Vector2f& v)
{
	m_physicalData.m_veolocity = v;
}

void Ball::setAcceleration(const sf::Vector2f& a)
{
	m_physicalData.m_acceleration = a;
}

void Ball::setMass(float m)
{
	m_physicalData.m_mass = m;
}

