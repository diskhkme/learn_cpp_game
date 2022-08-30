#include "raylib.h" 

// 화면에 그릴 수 있는 여러가지는 https://www.raylib.com/cheatsheet/cheatsheet.html 사이트를 참고하세요
// 빌드 결과 .exe 파일은 "CPP_Practice_Game/bin/Debug폴더 안에 들어가게 되어 있습니다.

// 전역변수는 여러모로 좋지 않으니, 일단 Main함수 안으로 옮기면서 정리를 좀 해보겠습니다.

void Update(Vector2& playerPosition) // main 함수 scope에 있는 playerPosition을 참조자로 받아서 함수 안에서 변경해 줍니다.
{
	// Vector2에 저장된 2개의 값은 .x, .y로 접근할 수 있습니다. (구조체에서 배우셨거나, 향후 클래스에서 보다 상세히 배울겁니다.)

	if (IsKeyDown(KEY_D)) playerPosition.x += 2;
	else if (IsKeyDown(KEY_A)) playerPosition.x -= 2;

	if (IsKeyDown(KEY_W)) playerPosition.y -= 2;
	else if (IsKeyDown(KEY_S)) playerPosition.y += 2;
}

// 그리기를 할 때는 playerPosition 및 playerColor 값이 바뀌지 않으니 const 참조자로 효율성을 높입시다.
void DrawPlayer(const Vector2& playerPosition, int playerWidth, int playerHeight, const Color& playerColor) 
{
	DrawRectangle(playerPosition.x, playerPosition.y, playerWidth, playerHeight, playerColor);
}

// 적 데이터도 비슷하게 받습니다. 위치는 동적 할당된 메모리 주소(포인터)로 받습니다.
void DrawEnemy(const Vector2* const enemyPosition, int enemyCount, int enemyRadius, const Color& enemyColor) 
{
	for (int i = 0; i < enemyCount; i++)
	{
		DrawCircle(enemyPosition[i].x, enemyPosition[i].y, enemyRadius, enemyColor); 
	}
}

int main() {
	//--- 윈도우 설정 관련 데이터
	int screenWidth = 800;
	int screenHeight = 450;

	InitWindow(screenWidth, screenHeight, "4_Pointer_Reference_Vector2");

	SetTargetFPS(60);

	const Color backgroundColor = Color{ 224, 251, 252, 255 };

	//--- 플레이어 관련 데이터
	// Raylib에서 2차원 데이터를 쉽게 관리하기 위해 Vector2 Struct를 제공합니다. 사용해봅시다.
	// Vector2는 float 2개를 저장하는 자료형입니다.
	Vector2 playerPosition = Vector2{ 10.0f,10.0f };

	const int playerWidth = 20;
	const int playerHeight = 20;
	const Color playerColor = Color{ 238, 108, 77, 255 };

	
	//--- 적 관련 데이터
	const int enemyCount = 10;
	const int enemyRadius = 10;

	// 적들의 초기 위치도 Vector2의 배열로 바꾸어 봅시다. 데이터가 (나름) 많으니, 동적 할당을 통해 힙 메모리에 생성하는걸로 하죠.
	Vector2* enemyPosition = new Vector2[enemyCount]; // 적의 위치들을 힙 메모리에 저장할수 있도록 동적할당
	for (int i = 0; i < enemyCount; i++)
	{
		float randomYPosition = (float)GetRandomValue(0, screenHeight); // float으로 변환하기 위해 (float)으로 형 변환을 해줍니다.
		float xPosition = (float)(screenWidth - 20);
		enemyPosition[i] = Vector2{ xPosition , randomYPosition }; // 동적할당된 곳에 적들의 초기 위치를 저장해 둡니다.
	}
	const Color enemyColor = Color{ 200, 150, 255, 255 };
	

	while (!WindowShouldClose())
	{
		Update(playerPosition); // Update에서는 키보드 입력에 따라 플레이어 위치를 바꾸어야 합니다. 함수 안에서 값을 바꾸어야 하니, 참조자를 사용하면 좋을겁니다.

		BeginDrawing();

		// 전역변수가 사라졌으니, 좀더 가독성을 높이기위해 DrawPlayer, DrawElemy 두개의 함수로 별도 분리해서 호출합시다.
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

// 1. DrawText() 함수를 사용해서 플레이어 위쪽에 이름이 표시되도록 만들어 보세요. (영어만 가능합니다.)
// 2. DrawPlayer, DrawEnemy에 인자가 너무 많아서 불편한 것 같기도 합니다. 기본 파라메터를 사용해 생략할 수 있도록 코드를 수정해 보세요.
// 3. 디버깅의 메모리 창을 활용해 enemyPosition이 가리키는 힙 메모리에, 데이터가 잘 저장이 되어 있는지 확인해 보세요.