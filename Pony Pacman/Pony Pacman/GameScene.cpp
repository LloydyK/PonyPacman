#include "GameScene.h"
Vector2f getCenter(Pacman & item) {
	float radius = item.radius;
	Vector2f pacmanCenter;
	pacmanCenter.x = item.x + radius;
	pacmanCenter.y = item.y + radius;
	return pacmanCenter;
}
void GameScene::appCheck(Pacman & pacman) {
	

	for (int i = 0; i < applesCount; i++) {
		float appSize = apples[i].getRadius();
		Vector2f appCenter = apples[i].getPosition();
		appCenter.x += appSize;
		appCenter.y += appSize;

		
		Vector2f pacmanCenter = getCenter(pacman);
		
		bool eat = Distance(appCenter, pacmanCenter) <= (pacman.radius + appSize);
		if (eat) {
			pacman.radius = changeRadius(pacman.radius, +1);
			apples[i].setPosition(getRandPosition());
			/*cout << pacman.radius<<"\n";*/
		}
	}
}
void GameScene::mineCheck(Pacman & pacman) {
	for (int i = 0; i < mineCount; i++) {
		float mineSize = mine[i].getRadius();
		Vector2f mineCenter = mine[i].getPosition();
		mineCenter.x += mineSize;
		mineCenter.y += mineSize;

		
		Vector2f pacmanCenter = getCenter(pacman);

		bool eat = Distance(mineCenter, pacmanCenter) <= (pacman.radius + mineSize);
		if (eat) {
			pacman.radius = changeRadius(pacman.radius, -10);
			mine[i].setPosition(getRandPosition());

			//cout << pacman.radius << " " <<
			//	pacman.x << " " <<
			//	pacman.y << " " <<
			//	eat << " " << endl;
		}

		

	}
}