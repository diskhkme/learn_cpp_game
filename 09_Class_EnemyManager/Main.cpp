#include "raylib.h" 
#include "raymath.h"

#include "Player.h"
#include "EnemyManager.h"

// ȭ�鿡 �׸� �� �ִ� ���������� https://www.raylib.com/cheatsheet/cheatsheet.html ����Ʈ�� �����ϼ���
// ���� ��� .exe ������ "CPP_Practice_Game/bin/Debug���� �ȿ� ���� �Ǿ� �ֽ��ϴ�.

int main() {
	//--- ������ ���� ���� ������
	int screenWidth = 800;
	int screenHeight = 450;

	InitWindow(screenWidth, screenHeight, "10_Class_Bullet");

	SetTargetFPS(60);

	const Color backgroundColor = Color{ 224, 251, 252, 255 };

	//--- �÷��̾� ���� ������
	Player player = Player{ 10,10,20,20,Color{238,108,77,255} };

	//--- �� ���� ������
	// ���� �������� ������ �����ϴ� �������� ����� EnemyManger Ŭ������ ������ �Ѱ��־����ϴ�.
	EnemyManager enemyManager;
	const int enemyCount = 10;
	const float enemyRadius = 10.0f;
	const Color enemyColor = Color{ 200, 150, 255, 255 };

	for (int i = 0; i < enemyCount; i++)
	{
		float randomYPosition = (float)GetRandomValue(0, screenHeight);
		float xPosition = (float)(screenWidth - 20);
		enemyManager.SpawnEnemy(Vector2{ xPosition,randomYPosition }, enemyRadius, enemyColor);
	}


	while (!WindowShouldClose())
	{
		player.Update(); 
		Vector2 playerPosition = player.GetPosition();
		enemyManager.Update(playerPosition); // ������ EnemyManager�� �˾Ƽ� ó���մϴ�.
		

		BeginDrawing();

		ClearBackground(backgroundColor);
		player.Draw(); // Player Ŭ������ Draw �Լ��� ȣ���ϸ�, ������ DrawPlayer�� �����ϰ� �����մϴ�.
		enemyManager.Draw();

		DrawFPS(10, 10);

		EndDrawing();
	}

	return 0;
}

//--- Practice

// 1. EnemyManger�� �����ؼ� � Enemy�� �ﰢ������, � enemy�� ������ �׸����� ������ ������.
// 2. ���� ���� ������ ��, Collision ���� ������ ��� �����ϸ� ������ ������ ������ ������.
// 3. Player�� ��ġ�� ��� ���ڷ� �Ѱ����� �ʰ�, �� �� ���ϰ� ������ ����� �������?
