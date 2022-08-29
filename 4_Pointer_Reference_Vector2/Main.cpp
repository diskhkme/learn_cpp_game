#include "raylib.h" 

// ȭ�鿡 �׸� �� �ִ� ���������� https://www.raylib.com/cheatsheet/cheatsheet.html ����Ʈ�� �����ϼ���
// ���� ��� .exe ������ "CPP_Practice_Game/bin/Debug���� �ȿ� ���� �Ǿ� �ֽ��ϴ�.

// ���������� ������� ���� ������, �ϴ� Main�Լ� ������ �ű�鼭 ������ �� �غ��ڽ��ϴ�.

void Update(Vector2& playerPosition) // main �Լ� scope�� �ִ� playerPosition�� �����ڷ� �޾Ƽ� �Լ� �ȿ��� ������ �ݴϴ�.
{
	// Vector2�� ����� 2���� ���� .x, .y�� ������ �� �ֽ��ϴ�. (����ü���� ���̰ų�, ���� Ŭ�������� ���� ���� ���̴ϴ�.)

	if (IsKeyDown(KEY_D)) playerPosition.x += 2;
	else if (IsKeyDown(KEY_A)) playerPosition.x -= 2;

	if (IsKeyDown(KEY_W)) playerPosition.y -= 2;
	else if (IsKeyDown(KEY_S)) playerPosition.y += 2;
}

// �׸��⸦ �� ���� playerPosition �� playerColor ���� �ٲ��� ������ const �����ڷ� ȿ������ ���Խô�.
void DrawPlayer(const Vector2& playerPosition, int playerWidth, int playerHeight, const Color& playerColor) 
{
	DrawRectangle(playerPosition.x, playerPosition.y, playerWidth, playerHeight, playerColor);
}

// �� �����͵� ����ϰ� �޽��ϴ�. ��ġ�� ���� �Ҵ�� �޸� �ּ�(������)�� �޽��ϴ�.
void DrawEnemy(const Vector2* const enemyPosition, int enemyCount, int enemyRadius, const Color& enemyColor) 
{
	for (int i = 0; i < enemyCount; i++)
	{
		DrawCircle(enemyPosition[i].x, enemyPosition[i].y, enemyRadius, enemyColor); 
	}
}

int main() {
	//--- ������ ���� ���� ������
	int screenWidth = 800;
	int screenHeight = 450;

	InitWindow(screenWidth, screenHeight, "4_Pointer_Reference_Vector2");

	SetTargetFPS(60);

	const Color backgroundColor = Color{ 224, 251, 252, 255 };

	//--- �÷��̾� ���� ������
	// Raylib���� 2���� �����͸� ���� �����ϱ� ���� Vector2 Struct�� �����մϴ�. ����غ��ô�.
	// Vector2�� float 2���� �����ϴ� �ڷ����Դϴ�.
	Vector2 playerPosition = Vector2{ 10.0f,10.0f };

	const int playerWidth = 20;
	const int playerHeight = 20;
	const Color playerColor = Color{ 238, 108, 77, 255 };

	
	//--- �� ���� ������
	const int enemyCount = 10;
	const int enemyRadius = 10;

	// ������ �ʱ� ��ġ�� Vector2�� �迭�� �ٲپ� ���ô�. �����Ͱ� (����) ������, ���� �Ҵ��� ���� �� �޸𸮿� �����ϴ°ɷ� ����.
	Vector2* enemyPosition = new Vector2[enemyCount]; // ���� ��ġ���� �� �޸𸮿� �����Ҽ� �ֵ��� �����Ҵ�
	for (int i = 0; i < enemyCount; i++)
	{
		float randomYPosition = (float)GetRandomValue(0, screenHeight); // float���� ��ȯ�ϱ� ���� (float)���� �� ��ȯ�� ���ݴϴ�.
		float xPosition = (float)(screenWidth - 20);
		enemyPosition[i] = Vector2{ xPosition , randomYPosition }; // �����Ҵ�� ���� ������ �ʱ� ��ġ�� ������ �Ӵϴ�.
	}
	const Color enemyColor = Color{ 200, 150, 255, 255 };
	

	while (!WindowShouldClose())
	{
		Update(playerPosition); // Update������ Ű���� �Է¿� ���� �÷��̾� ��ġ�� �ٲپ�� �մϴ�. �Լ� �ȿ��� ���� �ٲپ�� �ϴ�, �����ڸ� ����ϸ� �����̴ϴ�.

		BeginDrawing();

		// ���������� ���������, ���� �������� ���̱����� DrawPlayer, DrawElemy �ΰ��� �Լ��� ���� �и��ؼ� ȣ���սô�.
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

// 1. DrawText() �Լ��� ����ؼ� �÷��̾� ���ʿ� �̸��� ǥ�õǵ��� ����� ������. (��� �����մϴ�.)
// 2. DrawPlayer, DrawEnemy�� ���ڰ� �ʹ� ���Ƽ� ������ �� ���⵵ �մϴ�. �⺻ �Ķ���͸� ����� ������ �� �ֵ��� �ڵ带 ������ ������.
// 3. ������� �޸� â�� Ȱ���� enemyPosition�� ����Ű�� �� �޸𸮿�, �����Ͱ� �� ������ �Ǿ� �ִ��� Ȯ���� ������.