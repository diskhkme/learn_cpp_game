#include "raylib.h" 
#include "raymath.h"

// 화면에 그릴 수 있는 여러가지는 https://www.raylib.com/cheatsheet/cheatsheet.html 사이트를 참고하세요
// 빌드 결과 .exe 파일은 "CPP_Practice_Game/bin/Debug폴더 안에 들어가게 되어 있습니다.

void UpdatePlayer(Vector2& playerPosition)
{
	if (IsKeyDown(KEY_D)) playerPosition.x += 2;
	else if (IsKeyDown(KEY_A)) playerPosition.x -= 2;

	if (IsKeyDown(KEY_W)) playerPosition.y -= 2;
	else if (IsKeyDown(KEY_S)) playerPosition.y += 2;
}

bool CheckCollision(const Vector2& myPosition, int myRadius, const Vector2& otherPosition, int otherRadius)
{
	float distance = Vector2Distance(myPosition, otherPosition); // sqrt((x1-x2)^2+(y1-y2)^2)으로 직접 계산해도 되겠죠?
	if (distance < (myRadius + otherRadius)) // 중점 사이의 거리가 두 원의 반지름의 합보다 크면, 부딪힌 것입니다. 그림을 그려 보세요.
	{
		return true;
	}
	return false;
}

void HandleCollision(Vector2& myPosition, int myRadius, const Vector2& otherPosition, int otherRadius) // myPosition에 const가 없음에 유의!
{
	// 부딪혔기 때문에, 내 위치를 조정해 부딪히지 않는 위치로 옮깁니다.
	Vector2 otherToMeDir = Vector2Normalize(Vector2Subtract(myPosition, otherPosition));
	Vector2 otherToMeVectorAdjusted = Vector2Scale(otherToMeDir, myRadius + otherRadius);
	myPosition = Vector2Add(otherPosition, otherToMeVectorAdjusted);
}

void UpdateEnemy(Vector2* const enemyPosition, int enemyCount, int enemyRadius, const Vector2& playerPosition)
{
	// 적들이 서로 겹치지 않게 움직여줘 보도록 하겠습니다. 두 물체가 충돌(Collision)하는지 판별하는 것은 일반적으로 게임을 만들 때 아주 중요한 기능 요소입니다.
	for (int i = 0; i < enemyCount; i++)
	{
		Vector2 enemyToPlayerVector = Vector2Subtract(playerPosition, enemyPosition[i]); 
		Vector2 enemyToPlayerDirection = Vector2Normalize(enemyToPlayerVector); 

		enemyPosition[i].x = enemyPosition[i].x + enemyToPlayerDirection.x;
		enemyPosition[i].y = enemyPosition[i].y + enemyToPlayerDirection.y;

		for (int j = 0; j < enemyCount; j++)
		{
			if (i != j) // 자신이 아닌 다른 적 중에,
			{
				//if (CheckCollision(enemyPosition[i], enemyRadius, enemyPosition[j], enemyRadius)) // 겹치는 적이 있다면
				if (CheckCollisionCircles(enemyPosition[i], enemyRadius, enemyPosition[j], enemyRadius)) // 겹치는 적이 있다면
				{
					HandleCollision(enemyPosition[i], enemyRadius, enemyPosition[j], enemyRadius); // 위치를 조정해줍니다.
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
	//--- 윈도우 설정 관련 데이터
	int screenWidth = 800;
	int screenHeight = 450;

	InitWindow(screenWidth, screenHeight, "6_Pointer_Reference_Collision");

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
		UpdateEnemy(enemyPosition, enemyCount, enemyRadius, playerPosition); // 충돌 계산에 radius 정보가 필요하니 추가로 넘겨줍니다.

		BeginDrawing();

		ClearBackground(backgroundColor);
		DrawPlayer(playerPosition, playerWidth, playerHeight, playerColor);
		DrawEnemy(enemyPosition, enemyCount, enemyRadius, enemyColor);

		DrawFPS(10, 10); // 여기서부턴 성능에 영향이 있을지도 모르니, 화면 갱신률(FPS)를 볼 수 있도록 해 줍시다.

		EndDrawing();
	}

	return 0;
}

//--- Practice

// 1. enemyCount를 100, 1000으로 늘려 보세요. 화면 갱신 속도가 느려지는 것이 보이시나요? 안보인다면 더 높은 숫자로 설정해 보세요.
// 2. https://www.raylib.com/cheatsheet/cheatsheet.html 사이트로 가서 CheckCollisionCircles()를 찾아 보세요. 
//    생긴 것이 우리가 만든 CheckCollision과 비슷하죠? 그 함수를 사용하도록 코드를 바꿔보세요.
