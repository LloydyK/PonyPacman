#pragma once
#include <SFML\Graphics.hpp>
#include "pacman.h"
#include "util.h"
#include <iostream>
using namespace std;
using namespace sf;
struct GameScene {
	bool PauseReleased = false;
	bool Pause = false;
	bool isPressedFirst(Keyboard::Key pauseKey, const Event & event) {

		if (event.key.code != pauseKey) {
			return false;
		}

		if (event.type == Event::KeyPressed && PauseReleased == false) {
			PauseReleased = true;
			return true;
		}

		if (event.type == Event::KeyReleased) {
			PauseReleased = false;
		}

		return false;
	}
	void SwitchPause() {
		Pause = !Pause;
	}
	float HpRadiusX = 25;
	float HpRadiusY = 40;
	float HpPosX = 25;
	float HpPosY = 25;
	
	int mineCount = 4;
	CircleShape mine[4];
	Texture mines[25];
	
	const int applesCount = 10;
	CircleShape apples[10];
	Texture appleText[10];

	RectangleShape HP;
	RectangleShape krug;
	RectangleShape pauseShape;
	RectangleShape fon;
	Texture pacmans[2];
	
	Texture HPtext[5];
	Texture pauseTexture;
	int minPacSize = 20;
	int maxPacSize = 60;

	GameScene(Pacman & item, int fonNum) {
		float radius = getRadius(item);
		krug = RectangleShape(sf::Vector2f(radius,radius));
		krug.setFillColor(Color::White);
		krug.setPosition(Vector2f(item.x, item.y));
		HP = RectangleShape(Vector2f(HpRadiusX, HpRadiusY));
		HP.setFillColor(Color::White);
		
		//HP.setPosition(Vector2f(HpPosX, HpPosY));
		float windSize = 500.f;
		fon.setPosition(0, 0);
		fon = RectangleShape(sf::Vector2f(windSize, windSize));

		pauseShape = RectangleShape(sf::Vector2f(windSize*0.5, windSize*0.5));
		pauseShape.setPosition(Vector2f(windSize*0.25, windSize*0.25));
		pauseTexture.loadFromFile("textures/paused.png");
		pauseTexture.setSmooth(true);
		pauseShape.setTexture(&pauseTexture);
		

		if (fonNum == 3) {
			loadPac(0, "textures/avatar.png");
			loadPac(1, "textures/avatar.png");
		}
		else {
			loadPac(0, "textures/pacman0.png");
			loadPac(1, "textures/pacman1.png");
		}
		//mineCreateDebug();
		mineCreate();


		appCreate();
	}
	float getRadius(Pacman & pac) {
		int StartRad = 15;
		float Koeff = 0.45;
		return (StartRad + pac.HP * Koeff);
	}
	void setAvatar(bool isPony, Pacman &pacman) {
		if (isPony) {
			loadPac(0, "textures/avatar.png");
			loadPac(1, "textures/avatar.png");
		}
		else {
			loadPac(0, "textures/pacman0.png");
			loadPac(1, "textures/pacman1.png");
		}
		float size = 2 * getRadius(pacman);
		krug = RectangleShape(sf::Vector2f(size, size));
	}
	int changeHP(Pacman & pacman, int damage) {
		pacman.HP + damage;
		return damage;
	}
	float trim(float value, float min, float max) {
		if (value <= min) {
			return min;
		}
		if (value >= max) {
			return max;
		}
		return value;
	}
	float changeRadius(float radius, int i) {
		radius = trim(radius + i, minPacSize, maxPacSize);
		krug.setSize(Vector2f(2 * radius, 2 * radius));
		return radius;
	}


	void loadPac(int index, const char * path) {
		bool result = pacmans[index].loadFromFile(path);
		pacmans[index].setSmooth(true);
	}
	void loadMine(int index, const char*path) {
		bool result = mines[index].loadFromFile(path);
		mines[index].setSmooth(true);
	}
	void loadApp(int index, const char*path) {
		bool result = appleText[index].loadFromFile(path);
		appleText[index].setSmooth(true);
	}
	Vector2f getRandPosition() {
		//return Vector2f(100, 100); // for debug

		return Vector2f(
			rand() % (500 - 5 * 2),
			rand() % (500 - 5 * 2));
	} 

	void mineCreate() {
		for (int i = 0; i < mineCount; i++) {
			mine[i].setPosition(getRandPosition());
			mine[i].setFillColor(Color::White);
			mine[i].setRadius(15.0);
			loadMine(i, "textures/Homing_Underwater_Mine.png");
		}
	}

	void appCreate() {
		for (int i = 0; i < applesCount; i++) {
			apples[i].setPosition(getRandPosition());
			apples[i].setFillColor(Color::White);
			apples[i].setRadius(15.0);
			loadApp(i, "textures/yabloko_yopta8.png");
		}
	}
	void mineCreateDebug() {
		for (int i = 0; i < mineCount; i++) {
			if (i == 0) {
				mine[i].setPosition(Vector2f(150, 50));
			}
			else {
				mine[i].setPosition(Vector2f(0, 0));
			}

			mine[i].setFillColor(Color::Red);
			mine[i].setRadius(5.0);
		}
	}
	void appDraw(RenderWindow & window) {
		for (int i = 0; i < applesCount; i++) {
			window.draw(apples[i]);
			apples[i].setTexture(&appleText[i]);
		}
	}
	void mineDraw(RenderWindow & window) {
		for (int i = 0; i < mineCount; i++) {
			window.draw(mine[i]);
			mine[i].setTexture(&mines[i]);
		}
	}
	
	void HPView(Pacman & pacman, Pacman & item) {
		//checkRadius(pacman.radius, pacman.isDamaged);
		while (pacman.isDamaged <= 5) {
			int i = 1;
			if (item.isDamaged = i) HP.setTexture(&HPtext[i]);
			i++;
			HP.setPosition(item.x, item.y);
		}

	}
	void setView(Pacman & item) {
		if (item.isHungry) krug.setTexture(&pacmans[0]);
		else krug.setTexture(&pacmans[1]);

		krug.setPosition(item.x, item.y);
		krug.setSize(Vector2f(item.radius * 2, item.radius * 2));
	}
	void appCheck(Pacman & pacman);
		

	void mineCheck(Pacman & pacman);
		
};