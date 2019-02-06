#include <SFML/Graphics.hpp>
#include "pacman.h"
using namespace sf;

float Pacman::vx = 0.05; //горизонтальная скорость
float Pacman::vy = 0.05; //вертикальная скротость

const int Pacman::START_LIFE = 10;

void Pacman::checkBorder(float xLeft, float yTop, float xRight, float yBottom) {
	if (y > yBottom - radius) {
		y = yBottom - radius;
	}
	else if (y < yTop) {
		y = yTop;
	}
	if (x < xLeft) {
		x = xLeft;
	}
	else if (x > xRight - radius) {
		x = xRight - radius;
	}
}

void Pacman::changeDir(int newDir) {
	moveDir = (Dir)newDir;
}

void Pacman::move() {

	if (moveDir == Dir::LEFT) { x -= vx; }
	if (moveDir == Dir::RIGHT) { x += vx; }
	if (moveDir == Dir::UP) { y -= vy; }
	if (moveDir == Dir::DOWN) { y += vy; }
}

void Pacman::setPosition(float dx, float dy) {
	x += dx;
	y += dy;
}

bool Pacman::canMove(const RenderWindow & window, Dir mDir) {
	float centerX = x + radius;
	float centerY = y + radius;
	if (mDir == RIGHT) {
		float tochP = centerX + Pacman::vx + radius;
		if (tochP > window.getSize().x) {
			return false;
		}
	}
	if (mDir == LEFT) {
		float tochP = centerX - Pacman::vx - radius;
		if (0 > tochP) {
			return false;
		}
	}
	if (mDir == UP) {
		float tochP = centerY - Pacman::vy - radius;
		if (tochP < 0) {
			return false;
		}
	}
	if (mDir == DOWN) {
		float tochP = centerY + Pacman::vy + radius;
		if (window.getSize().y < tochP) {
			return false;
		}
	}
	return true;
}
