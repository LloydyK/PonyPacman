#include "pacman.h"

float Pacman::vx = 0.05; //горизонтальная скорость
float Pacman::vy = 0.05; //вертикальная скротость


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