#include "raylib.h" 

// ȭ�鿡 �׸� �� �ִ� ���������� https://www.raylib.com/cheatsheet/cheatsheet.html ����Ʈ�� �����ϼ���
// ���� ��� .exe ������ "CPP_Practice_Game/bin/Debug���� �ȿ� ���� �Ǿ� �ֽ��ϴ�.

// ������ �Լ����� Update�� Draw�� �ϱ� ������, �������� ����ϴ� ������ ���� ���������� ����� �ݴϴ�.
int playerPositionX = 10;
int PlayerPositionY = 10;

// �÷��̾��� ũ��� ������ ������ �ʴ´ٰ� �սô�.
const int playerWidth = 20;
const int playerHeight = 20;
const Color playerColor = Color{ 238, 108, 77, 255 };

const Color backgroundColor = Color{ 224, 251, 252, 255 };

void Update() // ���� ������ �̰��� ��Ƽ� �����ϸ� ���Ⱑ �����̴ϴ�.
{
	// IsKeyDown(keyCode) �Լ��� ����ϸ�, �ش� Ű���尡 ���ȴ��� ���θ� bool�� ��ȯ���ݴϴ�.

	if (IsKeyDown(KEY_RIGHT)) playerPositionX += 2;
	else if (IsKeyDown(KEY_LEFT)) playerPositionX -= 2;

	if (IsKeyDown(KEY_UP)) PlayerPositionY -= 2;
	else if (IsKeyDown(KEY_DOWN)) PlayerPositionY += 2;
}

void Draw() // �׸��� ������ �̰��� ��Ƽ� �����ϸ� ���Ⱑ �����̴ϴ�.
{
	ClearBackground(backgroundColor);

	DrawRectangle(playerPositionX, PlayerPositionY, playerWidth, playerHeight, playerColor);
}

int main() {
	int screenWidth = 800;
	int screenHeight = 450;

	InitWindow(screenWidth, screenHeight, "2_Function_Player_Movement");

	SetTargetFPS(60);

	while (!WindowShouldClose())
	{
		Update();

		BeginDrawing();

			Draw();

		EndDrawing();
	}

	return 0;
}

//--- Practice

// 1. ȭ��ǥ Ű�� �ƴ� W,A,S,D Ű�� �÷��̾ �����̵��� �ٲپ� ������.
// 2. �÷��̾��� �ӵ��� �ʹ� ���� �� �����ϴ�. �ӵ��� �� ������ �ٲپ� ������. ȿ�������� �ϱ� ���� playerSpeed ���� ������ �����ؼ� ������ ������.
// 3. �÷��̾��� ���μ��� �ӵ��� �밢�� �ӵ��� �������? �ƴ϶�� ��� �ؾ� ������ �ӵ��� �����̰� �ɱ��? 
// 4. ���콺 �Է��� ��� ó���ϴ°ɱ��? ������ �� �� ã�ƺ�����!