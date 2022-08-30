#include "raylib.h" 
#include "raymath.h"

#include "Player.h"
#include "Enemy.h"

// 화면에 그릴 수 있는 여러가지는 https://www.raylib.com/cheatsheet/cheatsheet.html 사이트를 참고하세요
// 빌드 결과 .exe 파일은 "CPP_Practice_Game/bin/Debug폴더 안에 들어가게 되어 있습니다.

// Player 클래스는 Player.h/Player.cpp로 떠났습니다! Enemy 클래스 또한 마찬가지.

void PushCollidingObject(Enemy& self, const Enemy& other)
{
	Vector2 selfPosition = self.GetPosition();
	Vector2 otherPosition = other.GetPosition();

	Vector2 otherToMeDir = Vector2Normalize(Vector2Subtract(selfPosition, otherPosition));
	Vector2 otherToMeVectorAdjusted = Vector2Scale(otherToMeDir, self.GetRadius() + self.GetRadius());

	self.SetPosition(Vector2Add(otherPosition, otherToMeVectorAdjusted));
}

void HandleCollision(Enemy* const enemies, int enemyCount, const Vector2& playerPosition)
{
	for (int i = 0; i < enemyCount; i++)
	{
		for (int j = 0; j < enemyCount; j++)
		{
			if (i != j)
			{
				// 우리가 만들었던 함수 대신, 라이브러리에서 제공하는 함수를 사용합시다.
				if (CheckCollisionCircles(enemies[i].GetPosition(), enemies[i].GetRadius(), enemies[j].GetPosition(), enemies[j].GetRadius()))
				{
					PushCollidingObject(enemies[i], enemies[j]);
				}
			}

		}
	}
}

int main() {
	//--- 윈도우 설정 관련 데이터
	int screenWidth = 800;
	int screenHeight = 450;

	InitWindow(screenWidth, screenHeight, "8_Class_Player");

	SetTargetFPS(60);

	const Color backgroundColor = Color{ 224, 251, 252, 255 };

	//--- 플레이어 관련 데이터
	// 기존 4줄의 데이터를 손쉽게 player객체 하나에 소속시켰습니다. UpdatePlayer와 DrawPlayer 함수도요!
	Player player = Player{ 10,10,20,20,Color{238,108,77,255} };

	//--- 적 관련 데이터
	const int enemyCount = 10;
	const float enemyRadius = 10.0f;
	Enemy* enemies = new Enemy[enemyCount];
	const Color enemyColor = Color{ 200, 150, 255, 255 };

	for (int i = 0; i < enemyCount; i++)
	{
		float randomYPosition = (float)GetRandomValue(0, screenHeight);
		float xPosition = (float)(screenWidth - 20);
		enemies[i] = Enemy{ xPosition, randomYPosition, enemyRadius, enemyColor };
	}


	while (!WindowShouldClose())
	{
		player.Update(); // Player 클래스의 Update 함수를 호출하면, 기존의 UpdatePlayer와 동일하게 동작합니다.
		Vector2 playerPosition = player.GetPosition();

		// 우선 Enemy 각자 알아서 움직인 후에,
		for (int i = 0; i < enemyCount; i++)
		{
			enemies[i].Update(playerPosition);
		}
		HandleCollision(enemies, enemyCount, playerPosition); // UpdateEnemy함수로 충돌 처리

		BeginDrawing();

		ClearBackground(backgroundColor);
		player.Draw(); // Player 클래스의 Draw 함수를 호출하면, 기존의 DrawPlayer와 동일하게 동작합니다.
		for (int i = 0; i < enemyCount; i++)
		{
			enemies[i].Draw();
		}

		DrawFPS(10, 10);

		EndDrawing();
	}

	{
		delete[] enemies;

	}

	return 0;
}

//--- Practice

// 1. Enemy 클래스를 통한 Encapsulation의 장점 중 하나로, 개별 객체가 다른 속성을 가지는 경우에 대한 처리가 쉬워 졌다는 것입니다.
//	  Enemies를 생성할 때 무작위로 색상 또는 radius를 부여하도록 수정해 보세요. 그리고 수정해야 하는 코드가 얼마나 적은지 확인해보세요.
//	  또한 만일 클래스가 없었다면 얼마나 많은 수정을 해야 했을지를 상상해 보세요.
// 2. HandleCollision()과 UpdateEnemy()가 Main.cpp에 남아있는것이 그리 좋지 않아보이지 않나요?
//	  어떻게 구조를 바꾸면 좋을까 스스로 먼저 생각해 보세요.
