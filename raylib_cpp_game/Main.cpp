#include "raylib.h"

// 화면에 그릴 수 있는 여러가지는 https://www.raylib.com/cheatsheet/cheatsheet.html 사이트를 참고하세요
// 빌드 결과 .exe 파일은 "CPP_Practice_Game/bin/Debug 또는 Release 폴더 안에 들어가게 되어 있습니다.


// 플레이어의 이동 관련한 연산을 모두 이곳에 모아 놓으면 보기가 좋겠죠?
void Update(int& playerPositionX, int& playerPositionY)
{
	// IsKeyDown(keyCode) 함수를 사용하면, 해당 키보드가 눌렸는지 여부를 bool로 반환해줍니다.

	if (IsKeyDown(KEY_D)) playerPositionX += 2;
	else if (IsKeyDown(KEY_A)) playerPositionX -= 2;

	if (IsKeyDown(KEY_W)) playerPositionY -= 2;
	else if (IsKeyDown(KEY_S)) playerPositionY += 2;
}

// 적을 그리는 연산은 이 곳에 함수로 모아 뒀습니다.
void DrawEnemy(int enemyPositionX[], int enemyPositionY[], int enemyCount, int enemyRadius, Color enemyColor)
{
	for (int i = 0; i < enemyCount; i++)
	{
		DrawCircle(enemyPositionX[i], enemyPositionY[i], enemyRadius, enemyColor); // 적 그리기. 적은 동그라미로 그려줍시다.
		DrawCircleLines(enemyPositionX[i], enemyPositionY[i], enemyRadius, BLACK); // 똑같은 위치에 속이 빈 원을 검은 테두리로 덧그리면 눈에 더 잘뜨입니다.

		// (BLACK, RED, GREEN, BLUE, WHITE와 같은 대표적인 색상은 매크로로 정의되어 있어 편하게 사용할 수 있습니다.)
	}
}

int main() {
	// 화면의 가로 및 세로 크기
	int screenWidth = 800;
	int screenHeight = 450;

	// 윈도우 만들기
	InitWindow(screenWidth, screenHeight, "MyGame"); // Parameter: ((int)가로, (int)세로, (std::string)창 이름)

	SetTargetFPS(60); // 화면을 1초에 몇번 그릴 것인지 (보통은 60번을 사용함. 60 fps(frames per second)

	//--- 화면에 그릴 플레이어 관련 변수
	int playerPositionX = 10;
	int playerPositionY = 10;
	const int playerWidth = 20; // 플레이어 사각형의 크기는 변하지 않는다고 합시다.
	const int playerHeight = 20;
	const Color playerColor = Color{ 238, 108, 77, 255 };

	//--- 화면에 그릴 적 관련 변수
	const int enemyCount = 10; // 적은 10 마리를 그릴 예정입니다. 배열 크기로 사용하기 위해 const 여야 한다는 것을 잊지 마세요
	int enemyPositionX[enemyCount]; 
	int enemyPositionY[enemyCount]; // 적의 X위치와 Y위치를 저장할 배열을 만들어 줍니다.
	const int enemyRadius = 10; // 적은 동그라미로 그릴 것이라 width/height 대신 반지름이 필요합니다.
	const Color enemyColor = Color{ 200, 150, 255, 255 };

	// 적의 X, Y 위치 배열에 값을 넣어주겠습니다.
	for (int i = 0; i < enemyCount; i++)
	{
		enemyPositionX[i] = screenWidth - 20; // 적의 X 위치는 항상 화면 오른쪽에서 20만큼 떨어진 지점에 만듭니다.
		enemyPositionY[i] = GetRandomValue(0, screenHeight); // Y 위치는 무작위로 만들어 봅시다. GetRandomValue() 함수로 0과 screenHeight 사이의 무작위 수를 생성할 수 있습니다. (라이브러리 기능)
	}

	//--- 배경색과 사각형의 색상을 바꾸지 않는다고 하면, 상수로 선언
	const Color backgroundColor = Color{ 224, 251, 252, 255 };
	

	// 창을 닫을 때까지 while 반복문을 돌면서 화면을 그리기 위한 함수들을 호출
	while (!WindowShouldClose())
	{
		// 일반적으로 게임을 만들때 loop 안에서는 데이터 조작과 조작된 데이터를 기반으로 한 화면 그리기를 수행합니다.
		// 여기에서도 이렇게 두 부분으로 구분해서 구현할 것이며, 중괄호, 들여쓰기 등은 문법적으로 의미는 없고, 보기 좋게 하기위해 들어간 것입니다.

		{ // 데이터 조작 (Update)
			
			// 이제 키보드를 사용해 플레이어를 움직일 수 있습니다. Update() 함수에서 이에 대한 처리를 담당합니다.
			// Update 함수 안에서 playerPositionX, playerPositionY 변수의 값을 바꾸어야 하니, 참조자로 넘겨줍니다.
			Update(playerPositionX, playerPositionY);
		}

		{ // 그리기 (Draw)
			BeginDrawing();

			ClearBackground(backgroundColor); // 배경 그리기

			DrawRectangle(playerPositionX, playerPositionY, playerWidth, playerHeight, playerColor); // 플레이어 그리기

			DrawEnemy(enemyPositionX, enemyPositionY, enemyCount, enemyRadius, enemyColor); // 적 그리기

			EndDrawing();
		}
	}

	return 0;
}

//--- Practice

// 1. 적들의 숫자를 늘려 보세요.
// 2. 적들을 화면 위쪽에서 랜덤하게 생성되도록 바꾸어 보세요.
// 3. 적들이 (자동으로) 왼쪽으로 움직이도록 하려면 어떻게 해야 할까요? 여러가지 방법이 있을 수 있습니다! 
// 4. 플레이어에게도 테두리를 그려 보세요.