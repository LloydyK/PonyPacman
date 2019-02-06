#pragma once

enum Dir {
	NONE = 0,
	LEFT = 1,
	RIGHT = 2,
	UP = 3,
	DOWN = 4
};


struct Pacman {
	static const int START_LIFE;

	static float vx;
	static float vy;


	//координаты верхнего левого угла
	float x;
	float y;


	int HP;
	float radius;
	bool isHungry;
	int isDamaged;
	Dir moveDir;

	void checkBorder(float xLeft, float yTop, float xRight, float yBottom);
	void changeDir(int newDir);
	void move();
	void setPosition(float dx, float dy);
	bool canMove(const sf::RenderWindow & window, Dir mDir);
};