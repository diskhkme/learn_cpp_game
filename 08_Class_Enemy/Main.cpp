#include "raylib.h" 
#include "raymath.h"

#include "Player.h"
#include "Enemy.h"

// ȭ�鿡 �׸� �� �ִ� ���������� https://www.raylib.com/cheatsheet/cheatsheet.html ����Ʈ�� �����ϼ���
// ���� ��� .exe ������ "CPP_Practice_Game/bin/Debug���� �ȿ� ���� �Ǿ� �ֽ��ϴ�.

// Player Ŭ������ Player.h/Player.cpp�� �������ϴ�! Enemy Ŭ���� ���� ��������.

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
				// �츮�� ������� �Լ� ���, ���̺귯������ �����ϴ� �Լ��� ����սô�.
				if (CheckCollisionCircles(enemies[i].GetPosition(), enemies[i].GetRadius(), enemies[j].GetPosition(), enemies[j].GetRadius()))
				{
					PushCollidingObject(enemies[i], enemies[j]);
				}
			}

		}
	}
}

int main() {
	//--- ������ ���� ���� ������
	int screenWidth = 800;
	int screenHeight = 450;

	InitWindow(screenWidth, screenHeight, "8_Class_Player");

	SetTargetFPS(60);

	const Color backgroundColor = Color{ 224, 251, 252, 255 };

	//--- �÷��̾� ���� ������
	// ���� 4���� �����͸� �ս��� player��ü �ϳ��� �Ҽӽ��׽��ϴ�. UpdatePlayer�� DrawPlayer �Լ�����!
	Player player = Player{ 10,10,20,20,Color{238,108,77,255} };

	//--- �� ���� ������
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
		player.Update(); // Player Ŭ������ Update �Լ��� ȣ���ϸ�, ������ UpdatePlayer�� �����ϰ� �����մϴ�.
		Vector2 playerPosition = player.GetPosition();

		// �켱 Enemy ���� �˾Ƽ� ������ �Ŀ�,
		for (int i = 0; i < enemyCount; i++)
		{
			enemies[i].Update(playerPosition);
		}
		HandleCollision(enemies, enemyCount, playerPosition); // UpdateEnemy�Լ��� �浹 ó��

		BeginDrawing();

		ClearBackground(backgroundColor);
		player.Draw(); // Player Ŭ������ Draw �Լ��� ȣ���ϸ�, ������ DrawPlayer�� �����ϰ� �����մϴ�.
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

// 1. Enemy Ŭ������ ���� Encapsulation�� ���� �� �ϳ���, ���� ��ü�� �ٸ� �Ӽ��� ������ ��쿡 ���� ó���� ���� ���ٴ� ���Դϴ�.
//	  Enemies�� ������ �� �������� ���� �Ǵ� radius�� �ο��ϵ��� ������ ������. �׸��� �����ؾ� �ϴ� �ڵ尡 �󸶳� ������ Ȯ���غ�����.
//	  ���� ���� Ŭ������ �����ٸ� �󸶳� ���� ������ �ؾ� �������� ����� ������.
// 2. HandleCollision()�� UpdateEnemy()�� Main.cpp�� �����ִ°��� �׸� ���� �ʾƺ����� �ʳ���?
//	  ��� ������ �ٲٸ� ������ ������ ���� ������ ������.
