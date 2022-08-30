#include "raylib.h" 
#include "raymath.h" // 벡터 계산을 도와주는 함수들이 정의된 헤더 파일입니다.

// 화면에 그릴 수 있는 여러가지는 https://www.raylib.com/cheatsheet/cheatsheet.html 사이트를 참고하세요
// 빌드 결과 .exe 파일은 "CPP_Practice_Game/bin/Debug폴더 안에 들어가게 되어 있습니다.

void UpdatePlayer(Vector2& playerPosition)
{
	if (IsKeyDown(KEY_D)) playerPosition.x += 2;
	else if (IsKeyDown(KEY_A)) playerPosition.x -= 2;

	if (IsKeyDown(KEY_W)) playerPosition.y -= 2;
	else if (IsKeyDown(KEY_S)) playerPosition.y += 2;
}

// 이제 적들도 움직이도록 해 봅시다. 적들이 플레이어를 따라 움직이록 만들려고 합니다.
void UpdateEnemy(Vector2* const enemyPosition, int enemyCount, const Vector2& playerPosition) // 플레이어 위치를 참조자를 통해 받습니다.
{
	// 적들의 위치를 매 프레임 갱신해 주어야 합니다. 조금씩 플레이어에게 가까운 위치로 옮기면 됩니다.
	for (int i = 0; i < enemyCount; i++)
	{
		Vector2 enemyToPlayerVector = Vector2Subtract(playerPosition, enemyPosition[i]); // 플레이어 위치 - 적 위치
		Vector2 enemyToPlayerDirection = Vector2Normalize(enemyToPlayerVector); // 길이가 1인 단위벡터로 변경해줍니다.

		// 적은 이 함수가 한번 호출될때마다 점점 플레이어에게 가까운 위치로 이동합니다.
		enemyPosition[i].x = enemyPosition[i].x + enemyToPlayerDirection.x;
		enemyPosition[i].y = enemyPosition[i].y + enemyToPlayerDirection.y;
	}
}

void DrawPlayer(const Vector2& playerPosition, int playerWidth, int playerHeight, const Color& playerColor)
{
	DrawRectangle(playerPosition.x, playerPosition.y, playerWidth, playerHeight, playerColor);
	DrawRectangleLines(playerPosition.x, playerPosition.y, playerWidth, playerHeight, BLACK); // 좀더 잘 보이도록 테두리 선도 그려줍니다.
}

void DrawEnemy(const Vector2* const enemyPosition, int enemyCount, int enemyRadius, const Color& enemyColor)
{
	for (int i = 0; i < enemyCount; i++)
	{
		DrawCircle(enemyPosition[i].x, enemyPosition[i].y, enemyRadius, enemyColor);
		DrawCircleLines(enemyPosition[i].x, enemyPosition[i].y, enemyRadius, BLACK); // 좀더 잘 보이도록 테두리 선도 그려줍니다.
	}
}

int main() {
	//--- 윈도우 설정 관련 데이터
	int screenWidth = 800;
	int screenHeight = 450;

	InitWindow(screenWidth, screenHeight, "5_Pointer_Reference_MovingEnemies");

	SetTargetFPS(60);

	const Color backgroundColor = Color{ 224, 251, 252, 255 };

	//--- 플레이어 관련 데이터
	Vector2 playerPosition = Vector2{ 10.0f,10.0f };

	const int playerWidth = 20;
	const int playerHeight = 20;
	const Color playerColor = Color{ 238, 108, 77, 255 };


	//--- 적 관련 데이터
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

// 1. UpdateEnemy() 함수의 for문 안에서, x와 y의 위치를 개별적으로 설정해 주고 있습니다. Vector2 대입으로 바꾸어 보세요 (Vector2Scale()과 Vector2Add() 함수 사용)
// 2. 적들의 이동속도를 더 빠르게, 혹은 더 느리게 바꿔 보세요
// 3. 시간이 지나면 적들이 겹쳐 버립니다. 어떻게 해결할 수 있을까요?