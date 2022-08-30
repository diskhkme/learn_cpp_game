#include "raylib.h" 
#include "raymath.h"

// ȭ�鿡 �׸� �� �ִ� ���������� https://www.raylib.com/cheatsheet/cheatsheet.html ����Ʈ�� �����ϼ���
// ���� ��� .exe ������ "CPP_Practice_Game/bin/Debug���� �ȿ� ���� �Ǿ� �ֽ��ϴ�.

// ���� ����� Ŭ������ ����� ���ô�!
class Player
{
private:
	Vector2 position;
	Vector2 size;
	Color color;

public:
	Player(float x, float y, float width, float height, Color color)
		: position{ Vector2{x,y} }, size{ Vector2{width,height} }, color{ color }
	{}
	void Update() // Player�� ����Լ� Update�� Player ��ü ��������� ������ ����ϰ� �Ǿ����ϴ�.
	{
		if (IsKeyDown(KEY_D)) position.x += 2;
		else if (IsKeyDown(KEY_A)) position.x -= 2;

		if (IsKeyDown(KEY_W)) position.y -= 2;
		else if (IsKeyDown(KEY_S)) position.y += 2;
	}
	void Draw() const // Player�� ����Լ� Draw�� Player ��ü ��������� �������� ȭ�鿡 �÷��̾ ǥ���մϴ�.
	{
		DrawRectangle(position.x, position.y, size.x, size.y, color);
		DrawRectangleLines(position.x, position.y, size.x, size.y, BLACK);
	}
	Vector2 GetPosition() const// �浹 ��꿡 �÷��̾� ��ġ�� �ʿ��ϴϱ�, ��ȯ���ִ� ����� �ϳ� ����Ӵϴ�.
	{
		return position;
	}
};


bool CheckCollision(const Vector2& myPosition, int myRadius, const Vector2& otherPosition, int otherRadius)
{
	float distance = Vector2Distance(myPosition, otherPosition); 
	if (distance < (myRadius + otherRadius)) 
	{
		return true;
	}
	return false;
}

void PushCollidingObject(Vector2& myPosition, int myRadius, const Vector2& otherPosition, int otherRadius)
{
	Vector2 otherToMeDir = Vector2Normalize(Vector2Subtract(myPosition, otherPosition));
	Vector2 otherToMeVectorAdjusted = Vector2Scale(otherToMeDir, myRadius + otherRadius);
	myPosition = Vector2Add(otherPosition, otherToMeVectorAdjusted);
}

void HandleCollision(Vector2* const enemyPosition, int enemyCount, int enemyRadius, const Vector2& playerPosition)
{
	for (int i = 0; i < enemyCount; i++)
	{
		Vector2 enemyToPlayerVector = Vector2Subtract(playerPosition, enemyPosition[i]);
		Vector2 enemyToPlayerDirection = Vector2Normalize(enemyToPlayerVector);

		enemyPosition[i].x = enemyPosition[i].x + enemyToPlayerDirection.x;
		enemyPosition[i].y = enemyPosition[i].y + enemyToPlayerDirection.y;

		for (int j = 0; j < enemyCount; j++)
		{
			if (i != j) 
			{
				if (CheckCollisionCircles(enemyPosition[i], enemyRadius, enemyPosition[j], enemyRadius))
				{
					PushCollidingObject(enemyPosition[i], enemyRadius, enemyPosition[j], enemyRadius);
				}
			}

		}
	}
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

	InitWindow(screenWidth, screenHeight, "7_Class_Player");

	SetTargetFPS(60);

	const Color backgroundColor = Color{ 224, 251, 252, 255 };

	//--- �÷��̾� ���� ������
	// ���� 4���� �����͸� �ս��� player��ü �ϳ��� �Ҽӽ��׽��ϴ�. UpdatePlayer�� DrawPlayer �Լ�����!
	Player player = Player{ 10,10,20,20,Color{238,108,77,255} }; 
	
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
		player.Update(); // Player Ŭ������ Update �Լ��� ȣ���ϸ�, ������ UpdatePlayer�� �����ϰ� �����մϴ�.
		HandleCollision(enemyPosition, enemyCount, enemyRadius, player.GetPosition()); // �浹 ��꿡 �ʿ��� playerPosition�� ����Լ��� ����� �ξ����ϴ�.

		BeginDrawing();

		ClearBackground(backgroundColor);
		player.Draw(); // Player Ŭ������ Draw �Լ��� ȣ���ϸ�, ������ DrawPlayer�� �����ϰ� �����մϴ�.
		DrawEnemy(enemyPosition, enemyCount, enemyRadius, enemyColor);

		DrawFPS(10, 10);

		EndDrawing();
	}

	{
		delete[] enemyPosition;

	}

	return 0;
}

//--- Practice

// 1. Player���� name ��������� ���� ������ �Ѱ�ó�� �÷��̾� �Ӹ� ���� �̸��� ǥ�õǵ��� �� ������.
// 2. ���� �ڷḦ �����Ͽ� Player Ŭ������ ������ Player.h/Player.cpp�� ����� ������ ������.
// 3. Enemy Ŭ������ ����� Player Ŭ������ �߰��� ��ó�� �ڵ带 �ٲپ� ������.
