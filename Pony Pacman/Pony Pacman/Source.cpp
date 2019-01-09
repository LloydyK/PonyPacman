/*
Задание
2.3 Когда в режиме паузы выводить надпись
3. Сделать полоску со здоровьем пакмана
*/

#include <SFML/Graphics.hpp>
#include <ctime> 
#include <iostream>
#include "pacman.h"
#include "util.h"
#include "GameScene.h"
int score = 0;
using namespace std;
using namespace sf;


const int colorCount = 13;


Color items[colorCount] {
	Color(194, 24, 91),
	Color(255, 61,0),
	Color(0,176,255),
	Color(0,121,107),
	Color(198,255,0),
	Color(255,235,59),
	Color(213,0,0),
	Color(26,35,126),
	Color(118,255,3),
	Color(33,150,243),
	Color(255,205,210),
	Color(248,187,208),
	Color(178,235,242)
};





		
	/*void RisovkaMin(const int MineCount, int i) {
		for (i = 0; i < mineCount; i++) {
			mine[i].setPosition(getRandPosition());
			mine[i].setFillColor(Color::Red);
			mine[i].setRadius(5.0);
	}*/
		//Проверка: не наступил ли пакман на мины
		/*void Proverkamin(const int mineCount, float x, float y, float radius) {
			for (int i = 0; i < mineCount; i++) {
			Vector2f p = mine[i].getPosition();
			if (isHit(x, y, radius, radius, p.x, p.y)) {
				mine[i].setPosition(getRandPosition());
				changeradius(radius, -1);
			};*/
bool CanMove(Pacman & pacman, RenderWindow & window, Dir mDir ) {
	
	float x = pacman.x + pacman.radius;
	float y = pacman.y + pacman.radius;
	//cout << x <<"     "<< vx << endl;
	if (mDir == RIGHT) { 
		float tochP = x + Pacman::vx + pacman.radius;
		if ( tochP > window.getSize().x) {
			return false;
		}
	}
	if (mDir == LEFT) {
		float tochP = x - Pacman::vx - pacman.radius;
		if (0 > tochP) {
			return false;
		}
	}
	if (mDir == UP) {
		float tochP = y - Pacman::vy - pacman.radius;
		if (tochP < 0) {
			return false;
		}
	}
	if (mDir == DOWN) {
		float tochP = y + Pacman::vy + pacman.radius;
		if (window.getSize().y < tochP) {
			return false;
		}
	}
	return true;
}
bool isHit(RenderWindow & window, Pacman & pacman ) {
	float x = pacman.x + pacman.radius;
	float y = pacman.y + pacman.radius;
    //Определяем лежит ли пакман в пределах экрана
	if (0 > x - pacman.radius || x + pacman.radius > window.getSize().x ||
		0 > y - pacman.radius || y + pacman.radius > window.getSize().y) {
		return true;
	}
	return false;
}

void chdir(int& dx) {
	dx = (dx + 1) % 2;
}


Vector2f getRandPosition() {
	return Vector2f(
		rand() % (500 - 5 * 2),
		rand() % (500 - 5 * 2));
}




int main()
{
 	setlocale(LC_ALL, "Russian");
	cout << "Введите номер фона..." << endl
		<< "1 - Черные кубики\n" << "2 - Hotline miami\n" << "3 - ПОНЯШКИ!!!\n" << "4 - Черепаха\n";
	int fonNum;
	cin >> fonNum;
	RenderWindow window(VideoMode(500, 500), "Circle's Adventure!");
	Pacman pacman;
	pacman.x = 250 - 100;
	pacman.y = 100;
	pacman.radius = 25.f;
	pacman.isHungry = true;
	pacman.moveDir = Dir::NONE;
	GameScene scene = GameScene(pacman,fonNum);
	scene.appCreate();
	//Space_cookie.setSmooth(true);
	Texture fon;
	int count = 0;
	bool move = true;
	bool isEnd = false;
	
	if (fonNum == 1) {
		fon.loadFromFile("textures/FON1.jpg");
	}
	else if (fonNum == 2) {
		fon.loadFromFile("textures/FON2.jpg");
	}
	else if (fonNum == 3) {
		fon.loadFromFile("textures/FON3.jpg");
	}
	else if (fonNum == 4) {
		fon.loadFromFile("textures/FON4.jpg");
	}
	scene.fon.setTexture(&fon);
	
	while (window.isOpen()&&isEnd==false)
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed) {
				window.close();
			}
			else if (event.type == Event::MouseButtonPressed) { }

		    //смена режимов

			const int mode = 1; //0 - отладка, 1 - нормальная игра, 2 - пауза (не доделанна)
	
			
			if (scene.isPressedFirst(Keyboard::Key::P, event)) {
				scene.SwitchPause();
			}
			
			

			if (event.type == Event::KeyPressed && mode == 0) {
				float dx = 1;
				float dy = 1;
			
			
				
				
				if (event.key.code == Keyboard::Key::Left) {pacman.setPosition(-dx, 0);}
				else if (event.key.code == Keyboard::Key::Right) {pacman.setPosition(dx, 0);}
				else if (event.key.code == Keyboard::Key::Up) {pacman.setPosition(0, -dy);}
				else if (event.key.code == Keyboard::Key::Down) {pacman.setPosition(0, dy);}
				else if (event.key.code == Keyboard::Key::Escape) {isEnd = true;}
			}
			if (event.type == Event::KeyPressed && mode == 1) {
				if (event.key.code == Keyboard::Key::Num1) {
					fon.loadFromFile("textures/FON1.jpg");
					scene.setAvatar(false, pacman);
				}
				else if (event.key.code == Keyboard::Key::Num2) {
					fon.loadFromFile("textures/FON2.jpg");
					scene.setAvatar(false, pacman);
				}
				else if (event.key.code == Keyboard::Key::Num3) {
					fon.loadFromFile("textures/FON3.jpg");
					scene.setAvatar(true, pacman);
				}
				else if (event.key.code == Keyboard::Key::Num4) {
					fon.loadFromFile("textures/FON4.jpg");
					scene.setAvatar(false, pacman);
				}
				scene.fon.setTexture(&fon);
				if (event.key.code == Keyboard::Key::Left) {
					if (CanMove(pacman, window, Dir::LEFT)) {
						pacman.changeDir(Dir::LEFT);
					}
				}
				else if (event.key.code == Keyboard::Key::Right) {
					if (CanMove(pacman, window, Dir::RIGHT)) {
						pacman.changeDir(Dir::RIGHT);
					}
				}
				else if (event.key.code == Keyboard::Key::Up) {
					if (CanMove(pacman, window, Dir::UP)){
						pacman.changeDir(Dir::UP);
					}
				}
				else if (event.key.code == Keyboard::Key::Down) {
					if (CanMove(pacman, window, Dir::DOWN)) {
						pacman.changeDir(Dir::DOWN);
					}
				}
				else if (event.key.code == Keyboard::Key::Escape) {
					isEnd = true;
				}
			}
		}

		//Движение
		if (scene.Pause == false) {
			bool test = CanMove(pacman, window, pacman.moveDir);
			if (test == true) {
				pacman.move();
			};
		}
		
		//cout << test;
		if (isEnd == true) {
			break;
		}
		//Отрисовка

		scene.appCheck(pacman);
		scene.mineCheck(pacman);
		scene.setView(pacman);
		//scene.HPView(pacman, pacman);
		window.clear();
		window.draw(scene.HP);
		window.draw(scene.fon);
		scene.appDraw(window);
		scene.mineDraw(window);
		window.draw(scene.krug);
		window.display();

	}
	


	cout << "score:" <<score<<endl;
	//system("pause");
	return 0;
}