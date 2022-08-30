#include "raylib.h" 
#include "raymath.h" // ���� ����� �����ִ� �Լ����� ���ǵ� ��� �����Դϴ�.

// ȭ�鿡 �׸� �� �ִ� ���������� https://www.raylib.com/cheatsheet/cheatsheet.html ����Ʈ�� �����ϼ���
// ���� ��� .exe ������ "CPP_Practice_Game/bin/Debug���� �ȿ� ���� �Ǿ� �ֽ��ϴ�.

void UpdatePlayer(Vector2& playerPosition)
{
	if (IsKeyDown(KEY_D)) playerPosition.x += 2;
	else if (IsKeyDown(KEY_A)) playerPosition.x -= 2;

	if (IsKeyDown(KEY_W)) playerPosition.y -= 2;
	else if (IsKeyDown(KEY_S)) playerPosition.y += 2;
}

// ���� ���鵵 �����̵��� �� ���ô�. ������ �÷��̾ ���� �����̷� ������� �մϴ�.
void UpdateEnemy(Vector2* const enemyPosition, int enemyCount, const Vector2& playerPosition) // �÷��̾� ��ġ�� �����ڸ� ���� �޽��ϴ�.
{
	// ������ ��ġ�� �� ������ ������ �־�� �մϴ�. ���ݾ� �÷��̾�� ����� ��ġ�� �ű�� �˴ϴ�.
	for (int i = 0; i < enemyCount; i++)
	{
		Vector2 enemyToPlayerVector = Vector2Subtract(playerPosition, enemyPosition[i]); // �÷��̾� ��ġ - �� ��ġ
		Vector2 enemyToPlayerDirection = Vector2Normalize(enemyToPlayerVector); // ���̰� 1�� �������ͷ� �������ݴϴ�.

		// ���� �� �Լ��� �ѹ� ȣ��ɶ����� ���� �÷��̾�� ����� ��ġ�� �̵��մϴ�.
		enemyPosition[i].x = enemyPosition[i].x + enemyToPlayerDirection.x;
		enemyPosition[i].y = enemyPosition[i].y + enemyToPlayerDirection.y;
	}
}

void DrawPlayer(const Vector2& playerPosition, int playerWidth, int playerHeight, const Color& playerColor)
{
	DrawRectangle(playerPosition.x, playerPosition.y, playerWidth, playerHeight, playerColor);
	DrawRectangleLines(playerPosition.x, playerPosition.y, playerWidth, playerHeight, BLACK); // ���� �� ���̵��� �׵θ� ���� �׷��ݴϴ�.
}

void DrawEnemy(const Vector2* const enemyPosition, int enemyCount, int enemyRadius, const Color& enemyColor)
{
	for (int i = 0; i < enemyCount; i++)
	{
		DrawCircle(enemyPosition[i].x, enemyPosition[i].y, enemyRadius, enemyColor);
		DrawCircleLines(enemyPosition[i].x, enemyPosition[i].y, enemyRadius, BLACK); // ���� �� ���̵��� �׵θ� ���� �׷��ݴϴ�.
	}
}

int main() {
	//--- ������ ���� ���� ������
	int screenWidth = 800;
	int screenHeight = 450;

	InitWindow(screenWidth, screenHeight, "5_Pointer_Reference_MovingEnemies");

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
		UpdateEnemy(enemyPosition, enemyCount, playerPosition);

		BeginDrawing();
		
		ClearBackground(backgroundColor);
		DrawPlayer(playerPosition, playerWidth, playerHeight, playerColor);
		DrawEnemy(enemyPosition, enemyCount, enemyRadius, enemyColor);

		EndDrawing();
	}

	{
		delete[] enemyPosition;

	}

	return 0;
}

//--- Practice

// 1. UpdateEnemy() �Լ��� for�� �ȿ���, x�� y�� ��ġ�� ���������� ������ �ְ� �ֽ��ϴ�. Vector2 �������� �ٲپ� ������ (Vector2Scale()�� Vector2Add() �Լ� ���)
// 2. ������ �̵��ӵ��� �� ������, Ȥ�� �� ������ �ٲ� ������
// 3. �ð��� ������ ������ ���� �����ϴ�. ��� �ذ��� �� �������?