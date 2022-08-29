#include "raylib.h" 
#include "raymath.h"

// ȭ�鿡 �׸� �� �ִ� ���������� https://www.raylib.com/cheatsheet/cheatsheet.html ����Ʈ�� �����ϼ���
// ���� ��� .exe ������ "CPP_Practice_Game/bin/Debug���� �ȿ� ���� �Ǿ� �ֽ��ϴ�.

void UpdatePlayer(Vector2& playerPosition)
{
	if (IsKeyDown(KEY_D)) playerPosition.x += 2;
	else if (IsKeyDown(KEY_A)) playerPosition.x -= 2;

	if (IsKeyDown(KEY_W)) playerPosition.y -= 2;
	else if (IsKeyDown(KEY_S)) playerPosition.y += 2;
}

bool CheckCollision(const Vector2& myPosition, int myRadius, const Vector2& otherPosition, int otherRadius)
{
	float distance = Vector2Distance(myPosition, otherPosition); // sqrt((x1-x2)^2+(y1-y2)^2)���� ���� ����ص� �ǰ���?
	if (distance < (myRadius + otherRadius)) // ���� ������ �Ÿ��� �� ���� �������� �պ��� ũ��, �ε��� ���Դϴ�. �׸��� �׷� ������.
	{
		return true;
	}
	return false;
}

void HandleCollision(Vector2& myPosition, int myRadius, const Vector2& otherPosition, int otherRadius) // myPosition�� const�� ������ ����!
{
	// �ε����� ������, �� ��ġ�� ������ �ε����� �ʴ� ��ġ�� �ű�ϴ�.
	Vector2 otherToMeDir = Vector2Normalize(Vector2Subtract(myPosition, otherPosition));
	Vector2 otherToMeVectorAdjusted = Vector2Scale(otherToMeDir, myRadius + otherRadius);
	myPosition = Vector2Add(otherPosition, otherToMeVectorAdjusted);
}

void UpdateEnemy(Vector2* const enemyPosition, int enemyCount, int enemyRadius, const Vector2& playerPosition)
{
	// ������ ���� ��ġ�� �ʰ� �������� ������ �ϰڽ��ϴ�. �� ��ü�� �浹(Collision)�ϴ��� �Ǻ��ϴ� ���� �Ϲ������� ������ ���� �� ���� �߿��� ��� ����Դϴ�.
	for (int i = 0; i < enemyCount; i++)
	{
		Vector2 enemyToPlayerVector = Vector2Subtract(playerPosition, enemyPosition[i]); 
		Vector2 enemyToPlayerDirection = Vector2Normalize(enemyToPlayerVector); 

		enemyPosition[i].x = enemyPosition[i].x + enemyToPlayerDirection.x;
		enemyPosition[i].y = enemyPosition[i].y + enemyToPlayerDirection.y;

		for (int j = 0; j < enemyCount; j++)
		{
			if (i != j) // �ڽ��� �ƴ� �ٸ� �� �߿�,
			{
				//if (CheckCollision(enemyPosition[i], enemyRadius, enemyPosition[j], enemyRadius)) // ��ġ�� ���� �ִٸ�
				if (CheckCollisionCircles(enemyPosition[i], enemyRadius, enemyPosition[j], enemyRadius)) // ��ġ�� ���� �ִٸ�
				{
					HandleCollision(enemyPosition[i], enemyRadius, enemyPosition[j], enemyRadius); // ��ġ�� �������ݴϴ�.
				}
			}

		}
	}
}

void DrawPlayer(const Vector2& playerPosition, int playerWidth, int playerHeight, const Color& playerColor)
{
	DrawRectangle(playerPosition.x, playerPosition.y, playerWidth, playerHeight, playerColor);
	DrawRectangleLines(playerPosition.x, playerPosition.y, playerWidth, playerHeight, BLACK); 
}

void DrawEnemy(const Vector2* const enemyPosition, int enemyCount, int enemyRadius, const Color& enemyColor)
{
	for (int i = 0; i < enemyCount; i++)
	{
		DrawCircle(enemyPosition[i].x, enemyPosition[i].y, enemyRadius, enemyColor);
		DrawCircleLines(enemyPosition[i].x, enemyPosition[i].y, enemyRadius, BLACK); 
	}
}

int main() {
	//--- ������ ���� ���� ������
	int screenWidth = 800;
	int screenHeight = 450;

	InitWindow(screenWidth, screenHeight, "6_Pointer_Reference_Collision");

	SetTargetFPS(60);

	const Color backgroundColor = Color{ 224, 251, 252, 255 };

	//--- �÷��̾� ���� ������
	Vector2 playerPosition = Vector2{ 10.0f,10.0f };

	const int playerWidth = 20;
	const int playerHeight = 20;
	const Color playerColor = Color{ 238, 108, 77, 255 };


	//--- �� ���� ������
	const int enemyCount = 10;
	const int enemyRadius = 10;

	Vector2* enemyPosition = new Vector2[enemyCount];
	for (int i = 0; i < enemyCount; i++)
	{
		float randomYPosition = (float)GetRandomValue(0, screenHeight);
		float xPosition = (float)(screenWidth - 20);
		enemyPosition[i] = Vector2{ xPosition , randomYPosition };
	}
	const Color enemyColor = Color{ 200, 150, 255, 255 };


	while (!WindowShouldClose())
	{
		UpdatePlayer(playerPosition);
		UpdateEnemy(enemyPosition, enemyCount, enemyRadius, playerPosition); // �浹 ��꿡 radius ������ �ʿ��ϴ� �߰��� �Ѱ��ݴϴ�.

		BeginDrawing();

		ClearBackground(backgroundColor);
		DrawPlayer(playerPosition, playerWidth, playerHeight, playerColor);
		DrawEnemy(enemyPosition, enemyCount, enemyRadius, enemyColor);

		DrawFPS(10, 10); // ���⼭���� ���ɿ� ������ �������� �𸣴�, ȭ�� ���ŷ�(FPS)�� �� �� �ֵ��� �� �ݽô�.

		EndDrawing();
	}

	return 0;
}

//--- Practice

// 1. enemyCount�� 100, 1000���� �÷� ������. ȭ�� ���� �ӵ��� �������� ���� ���̽ó���? �Ⱥ��δٸ� �� ���� ���ڷ� ������ ������.
// 2. https://www.raylib.com/cheatsheet/cheatsheet.html ����Ʈ�� ���� CheckCollisionCircles()�� ã�� ������. 
//    ���� ���� �츮�� ���� CheckCollision�� �������? �� �Լ��� ����ϵ��� �ڵ带 �ٲ㺸����.
