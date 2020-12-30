#include "Application.h"

/*
TODO:
1) Make general class Entity and create them instead of Ball, then assign
2) Use chrono instead of sf::Time
*/

int Ball::s_id = 0;
int main()
{
	Application app;
	
	app.runLoop();
	
	return 0;
}