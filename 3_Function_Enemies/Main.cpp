#include "raylib.h" 

// 화면에 그릴 수 있는 여러가지는 https://www.raylib.com/cheatsheet/cheatsheet.html 사이트를 참고하세요
// 빌드 결과 .exe 파일은 "CPP_Practice_Game/bin/Debug폴더 안에 들어가게 되어 있습니다.

int playerPositionX = 10;
int PlayerPositionY = 10;

const int playerWidth = 20;
const int playerHeight = 20;
const Color playerColor = Color{ 238, 108, 77, 255 };

const Color backgroundColor = Color{ 224, 251, 252, 255 };

// 적과 관련한 Global 데이터는 임시적으로 이곳에 선언해 봅시다.
const Color enemyColor = Color{ 200, 150, 255, 255 };
const int enemyRadius = 10;

void Update()
{
	if (IsKeyDown(KEY_RIGHT)) playerPositionX += 2;
	else if (IsKeyDown(KEY_LEFT)) playerPositionX -= 2;

	if (IsKeyDown(KEY_UP)) PlayerPositionY -= 2;
	else if (IsKeyDown(KEY_DOWN)) PlayerPositionY += 2;
}

void Draw(int enemyPositionX, int enemyRandomPositionY [], int count) // 이번에는 적들을 그리기 위해 필요한 데이터를 인자로 받습니다.
{
	ClearBackground(backgroundColor);

	DrawRectangle(playerPositionX, PlayerPositionY, playerWidth, playerHeight, playerColor);

	// 적 그리기. 적은 동그라미로 그려줍시다.
	for (int i = 0; i < count; i++)
	{
		DrawCircle(enemyPositionX, enemyRandomPositionY[i], enemyRadius, enemyColor); //인자로 받은 데이터와 Global 변수인 데이터를 식별해 보세요.
	}
}

int main() {
	int screenWidth = 800;
	int screenHeight = 450;

	InitWindow(screenWidth, screenHeight, "2_Function_Player_Movement");

	SetTargetFPS(60);

	// 10명의 적을 화면 오른쪽에 랜덤하게 배치하고 싶습니다.
	// 랜덤한 수의 생성은 라이브러리에서 제공하는 GetRandomValue(min,max)를 활용합니다.
	const int enemyCount = 10; // 10명 생성
	int enemyRandomPositionY[enemyCount]; // 적의 랜덤한 Y위치를 담을 배열을 정의합니다.
	const int enemyPositionX = screenWidth - 20; // 적의 X위치는 screenWidth-20으로 고정해서 생성합니다. (화면 오른쪽 끝에서 20만큼 떨어진 지점)
	for (int i = 0; i < enemyCount; i++)
	{
		enemyRandomPositionY[i] = GetRandomValue(0, screenHeight); // 배열의 각 원소를 0~screenHeight 사이의 랜덤한 값으로 설정합니다.
	}

	while (!WindowShouldClose())
	{
		Update();

		BeginDrawing();

		Draw(enemyPositionX, enemyRandomPositionY, enemyCount); // 적들을 화면에 그려야 하니, enemyRandomPositionY 배열과 size를 draw 함수에 인자로 전달해 줍니다.

		EndDrawing();
	}

	return 0;
}

//--- Practice

// 1. 적들의 숫자를 늘려 보세요.
// 2. 적들을 화면 위쪽에서 랜덤하게 생성되도록 바꾸어 보세요.
// 3. 적들이 (자동으로) 왼쪽으로 움직이도록 하려면 어떻게 해야 할까요? 여러가지 방법이 있을 수 있습니다!