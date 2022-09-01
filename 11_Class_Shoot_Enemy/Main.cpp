#include "raylib.h" 
#include "raymath.h"

#include "Player.h"
#include "EnemyManager.h"

// ȭ�鿡 �׸� �� �ִ� ���������� https://www.raylib.com/cheatsheet/cheatsheet.html ����Ʈ�� �����ϼ���
// ���� ��� .exe ������ "CPP_Practice_Game/bin/Debug���� �ȿ� ���� �Ǿ� �ֽ��ϴ�.

//---
// Ǯ��� �ϴ� ������ �������� ����������, �켱 �ִ��� ���Ӱ��� ���̵��� �ϱ� ���ؼ� ���� ���� ���� �� �ִ� ��ɰ�,
// ���� �÷��̾�� �ε����� �÷��̾��� ü���� ���̴� ������ �߰��� ���ô�.


int main() {
	//--- ������ ���� ���� ������
	int screenWidth = 800;
	int screenHeight = 450;

	InitWindow(screenWidth, screenHeight, "11_Class_Shoot_Enemy");

	SetTargetFPS(60);

	const Color backgroundColor = Color{ 224, 251, 252, 255 };

	//--- �÷��̾� ���� ������
	Player player = Player{ 10,10,20,20,Color{238,108,77,255} };

	//--- �� ���� ������
	EnemyManager enemyManager;
	const int enemyCount = 10;
	const float enemyRadius = 10.0f;
	const Color enemyColor = Color{ 200, 150, 255, 255 };
	const int enemyMaxHP = 100;

	for (int i = 0; i < enemyCount; i++)
	{
		float randomYPosition = (float)GetRandomValue(0, screenHeight);
		float xPosition = (float)(screenWidth - 20);
		enemyManager.SpawnEnemy(new Enemy{ Vector2{ xPosition,randomYPosition }, enemyRadius, enemyColor, enemyMaxHP });
	}


	while (!WindowShouldClose())
	{
		player.Update(); // źȯ�� �߻� ���� Player Ŭ�������� ó���� �ݴϴ�.
		Vector2 playerPosition = player.GetPosition();
		enemyManager.Update(player); 
		

		BeginDrawing();

		ClearBackground(backgroundColor);
		player.Draw(); 
		enemyManager.Draw();

		DrawFPS(10, 10);

		EndDrawing();
	}

	return 0;
}

//--- Practice

// 1. �ڼ��� ���� źȯ�� �÷��̾� ����� ������ ���� �ƴϰ� ���� ���ʿ��� ������ ���� �� �� �ֽ��ϴ�. ���, �Ǵ� �ٸ� ������ ��ġ���� �߻�ǵ��� ������ ������.
// 2. źȯ�� �ϳ� �߻��ϰ�, �� ��ġ�� �ܼ�â�� ����ϰų�, ���� �ڿ� �ߴ����� �ɾ ��ġ�� Ȯ���غ�����. ȭ�鿡�� �̹� ����� �����Դϴ�. ��� �ϴ°��� �������?
// 3. �翬������ ����� źȯ�� 50�� �̻� �߻��ϰ� �Ǹ� exception�� �߻��մϴ�. � �ذ� ������� �������?
