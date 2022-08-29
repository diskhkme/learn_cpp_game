#include "raylib.h" 
#include "raymath.h"

// 화면에 그릴 수 있는 여러가지는 https://www.raylib.com/cheatsheet/cheatsheet.html 사이트를 참고하세요
// 빌드 결과 .exe 파일은 "CPP_Practice_Game/bin/Debug폴더 안에 들어가게 되어 있습니다.

// 이제 대망의 클래스를 사용해 봅시다!
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
	void Update() // Player의 멤버함수 Update는 Player 객체 멤버변수의 조작을 담당하게 되었습니다.
	{
		if (IsKeyDown(KEY_D)) position.x += 2;
		else if (IsKeyDown(KEY_A)) position.x -= 2;

		if (IsKeyDown(KEY_W)) position.y -= 2;
		else if (IsKeyDown(KEY_S)) position.y += 2;
	}
	void Draw() const // Player의 멤버함수 Draw는 Player 객체 멤버변수를 바탕으로 화면에 플레이어를 표시합니다.
	{
		DrawRectangle(position.x, position.y, size.x, size.y, color);
		DrawRectangleLines(position.x, position.y, size.x, size.y, BLACK);
	}
	Vector2 GetPosition() const// 충돌 계산에 플레이어 위치가 필요하니까, 반환해주는 기능을 하나 열어둡니다.
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
	//--- 윈도우 설정 관련 데이터
	int screenWidth = 800;
	int screenHeight = 450;

	InitWindow(screenWidth, screenHeight, "7_Class_Player");

	SetTargetFPS(60);

	const Color backgroundColor = Color{ 224, 251, 252, 255 };

	//--- 플레이어 관련 데이터
	// 기존 4줄의 데이터를 손쉽게 player객체 하나에 소속시켰습니다. UpdatePlayer와 DrawPlayer 함수도요!
	Player player = Player{ 10,10,20,20,Color{238,108,77,255} }; 
	
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
		player.Update(); // Player 클래스의 Update 함수를 호출하면, 기존의 UpdatePlayer와 동일하게 동작합니다.
		HandleCollision(enemyPosition, enemyCount, enemyRadius, player.GetPosition()); // 충돌 계산에 필요한 playerPosition도 멤버함수로 만들어 두었습니다.

		BeginDrawing();

		ClearBackground(backgroundColor);
		player.Draw(); // Player 클래스의 Draw 함수를 호출하면, 기존의 DrawPlayer와 동일하게 동작합니다.
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

// 1. Player에게 name 멤버변수를 만들어서 이전에 한것처럼 플레이어 머리 위에 이름이 표시되도록 해 보세요.
// 2. 강의 자료를 참고하여 Player 클래스의 구현을 Player.h/Player.cpp에 나누어서 구현해 보세요.
// 3. Enemy 클래스를 만들고 Player 클래스를 추가한 것처럼 코드를 바꾸어 보세요.
