#include "raylib.h" 

// ȭ�鿡 �׸� �� �ִ� ���������� https://www.raylib.com/cheatsheet/cheatsheet.html ����Ʈ�� �����ϼ���
// ���� ��� .exe ������ "CPP_Practice_Game/bin/Debug���� �ȿ� ���� �Ǿ� �ֽ��ϴ�.

int playerPositionX = 10;
int PlayerPositionY = 10;

const int playerWidth = 20;
const int playerHeight = 20;
const Color playerColor = Color{ 238, 108, 77, 255 };

const Color backgroundColor = Color{ 224, 251, 252, 255 };

// ���� ������ Global �����ʹ� �ӽ������� �̰��� ������ ���ô�.
const Color enemyColor = Color{ 200, 150, 255, 255 };
const int enemyRadius = 10;

void Update()
{
	if (IsKeyDown(KEY_RIGHT)) playerPositionX += 2;
	else if (IsKeyDown(KEY_LEFT)) playerPositionX -= 2;

	if (IsKeyDown(KEY_UP)) PlayerPositionY -= 2;
	else if (IsKeyDown(KEY_DOWN)) PlayerPositionY += 2;
}

void Draw(int enemyPositionX, int enemyRandomPositionY [], int count) // �̹����� ������ �׸��� ���� �ʿ��� �����͸� ���ڷ� �޽��ϴ�.
{
	ClearBackground(backgroundColor);

	DrawRectangle(playerPositionX, PlayerPositionY, playerWidth, playerHeight, playerColor);

	// �� �׸���. ���� ���׶�̷� �׷��ݽô�.
	for (int i = 0; i < count; i++)
	{
		DrawCircle(enemyPositionX, enemyRandomPositionY[i], enemyRadius, enemyColor); //���ڷ� ���� �����Ϳ� Global ������ �����͸� �ĺ��� ������.
	}
}

int main() {
	int screenWidth = 800;
	int screenHeight = 450;

	InitWindow(screenWidth, screenHeight, "2_Function_Player_Movement");

	SetTargetFPS(60);

	// 10���� ���� ȭ�� �����ʿ� �����ϰ� ��ġ�ϰ� �ͽ��ϴ�.
	// ������ ���� ������ ���̺귯������ �����ϴ� GetRandomValue(min,max)�� Ȱ���մϴ�.
	const int enemyCount = 10; // 10�� ����
	int enemyRandomPositionY[enemyCount]; // ���� ������ Y��ġ�� ���� �迭�� �����մϴ�.
	const int enemyPositionX = screenWidth - 20; // ���� X��ġ�� screenWidth-20���� �����ؼ� �����մϴ�. (ȭ�� ������ ������ 20��ŭ ������ ����)
	for (int i = 0; i < enemyCount; i++)
	{
		enemyRandomPositionY[i] = GetRandomValue(0, screenHeight); // �迭�� �� ���Ҹ� 0~screenHeight ������ ������ ������ �����մϴ�.
	}

	while (!WindowShouldClose())
	{
		Update();

		BeginDrawing();

		Draw(enemyPositionX, enemyRandomPositionY, enemyCount); // ������ ȭ�鿡 �׷��� �ϴ�, enemyRandomPositionY �迭�� size�� draw �Լ��� ���ڷ� ������ �ݴϴ�.

		EndDrawing();
	}

	return 0;
}

//--- Practice

// 1. ������ ���ڸ� �÷� ������.
// 2. ������ ȭ�� ���ʿ��� �����ϰ� �����ǵ��� �ٲپ� ������.
// 3. ������ (�ڵ�����) �������� �����̵��� �Ϸ��� ��� �ؾ� �ұ��? �������� ����� ���� �� �ֽ��ϴ�!