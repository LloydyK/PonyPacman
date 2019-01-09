#pragma once
#include <SFML\Graphics.hpp>
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
	int mineCount = 25;
	CircleShape mine[25];
	const int applesCount = 4;
	CircleShape apples[4];
	RectangleShape HP;
	RectangleShape krug;
	RectangleShape fon;
	Texture pacmans[2];
	Texture mines[25];
	Texture appleText[4];
	Texture HPtext[5];
	int minPacSize = 20;
	int maxPacSize = 60;

	GameScene(Pacman & item, int fonNum) {
		krug = RectangleShape(sf::Vector2f(2 * item.radius, 2 * item.radius));
		krug.setFillColor(Color::White);
		krug.setPosition(Vector2f(item.x, item.y));
		HP = RectangleShape(Vector2f(HpRadiusX, HpRadiusY));
		HP.setFillColor(Color::White);
		//HP.setPosition(Vector2f(HpPosX, HpPosY));

		fon = RectangleShape(sf::Vector2f(500.f, 500.f));
		fon.setPosition(0, 0);

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
	void setAvatar(bool isPony, Pacman &pacman) {
		if (isPony) {
			loadPac(0, "textures/avatar.png");
			loadPac(1, "textures/avatar.png");
		}
		else {
			loadPac(0, "textures/pacman0.png");
			loadPac(1, "textures/pacman1.png");
		}
		krug = RectangleShape(sf::Vector2f(2 * pacman.radius, 2 * pacman.radius));
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
	int checkRadius(float radius, int damaged) {
		damaged = 0;
		if (radius > 50) {
			loadHP("textures/HP5.png", 5);
			damaged = 5;
		}
		else if (radius > 40 && radius <= 50) {
			loadHP("textures/HP4.png", 4);
			damaged = 4;
		}
		else if (radius > 30 && radius <= 40) {
			loadHP("textures/HP3.png", 3);
			damaged = 3;
		}
		else if (radius > 20 && radius <= 30) {
			loadHP("textures/HP3.png", 2);
			damaged = 2;
		}
		else if (radius > 10 && radius <= 20) {
			loadHP("textures/HP1.png", 1);
			damaged = 1;
			return damaged;
		}
	}
	void loadHP(const char * path, int i) {
		bool result = HPtext[i].loadFromFile(path);
		HPtext[i].setSmooth(true);
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
	// ÂÀÆÍÎÅ ÌÅÑÒÎ!!! 24.12.2018
	void HPView(Pacman & pacman, Pacman & item) {
		checkRadius(pacman.radius, pacman.isDamaged);
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
	}
	void appCheck(Pacman & pacman) {
		for (int i = 0; i < applesCount; i++) {
			float appSize = apples[i].getRadius();
			Vector2f appCenter = apples[i].getPosition();
			appCenter.x += appSize;
			appCenter.y += appSize;

			Vector2f pacmanCenter;
			pacmanCenter.x = pacman.x + pacman.radius;
			pacmanCenter.y = pacman.y + pacman.radius;
			bool eat = Distance(appCenter, pacmanCenter) <= (pacman.radius + appSize);
			if (eat) {
				pacman.radius = changeRadius(pacman.radius, +2);
				apples[i].setPosition(getRandPosition());
			}
		}
	}

	void mineCheck(Pacman & pacman) {
		for (int i = 0; i < mineCount; i++) {
			float mineSize = mine[i].getRadius();
			Vector2f mineCenter = mine[i].getPosition();
			mineCenter.x += mineSize;
			mineCenter.y += mineSize;

			Vector2f pacmanCenter;
			pacmanCenter.x = pacman.x + pacman.radius;
			pacmanCenter.y = pacman.y + pacman.radius;
			bool eat = Distance(mineCenter, pacmanCenter) <= (pacman.radius + mineSize);
			if (eat) {
				pacman.radius = changeRadius(pacman.radius, -2);
				mine[i].setPosition(getRandPosition());
			}
		}
	}
};