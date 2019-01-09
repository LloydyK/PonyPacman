#pragma once

enum Dir {
	NONE = 0,
	LEFT = 1,
	RIGHT = 2,
	UP = 3,
	DOWN = 4
};


struct Pacman {

	static float vx;
	static float vy;

	float x;
	float y;
	float radius;
	bool isHungry;
	int isDamaged;
	Dir moveDir;

	void checkBorder(float xLeft, float yTop, float xRight, float yBottom);
	void changeDir(int newDir);
	void move();
	void setPosition(float dx, float dy);
};