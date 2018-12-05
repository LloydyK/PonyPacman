#include "util.h"
float Distance(sf::Vector2f a, sf::Vector2f b) {
	float ax = a.x - b.x;
	float ay = a.y - b.y;
	//квадратный корень
	float r = sqrt(ax*ax + ay*ay);
	return r;
}