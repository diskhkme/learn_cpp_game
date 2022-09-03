#include "raylib.h"
#include "raymath.h" // sqrt 계산을 위해 math 라이브러리도 사용합니다.

// 화면에 그릴 수 있는 여러가지는 https://www.raylib.com/cheatsheet/cheatsheet.html 사이트를 참고하세요
// 빌드 결과 .exe 파일은 "CPP_Practice_Game/bin/Debug 또는 Release 폴더 안에 들어가게 되어 있습니다.


// 플레이어의 이동 관련한 연산을 모두 이곳에 모아 놓으면 보기가 좋겠죠?
void UpdatePlayer(Vector2& playerPosition)
{
	// IsKeyDown(keyCode) 함수를 사용하면, 해당 키보드가 눌렸는지 여부를 bool로 반환해줍니다.

	if (IsKeyDown(KEY_D)) playerPosition.x += 2;
	else if (IsKeyDown(KEY_A)) playerPosition.x -= 2;

	if (IsKeyDown(KEY_W)) playerPosition.y -= 2;
	else if (IsKeyDown(KEY_S)) playerPosition.y += 2;
}

void UpdateEnemy(float enemySpeed, Vector2* enemyPosition, int enemyCount, const Vector2& playerPosition)
{
	// playerPositionX & Y는 변하지 않는 값이기 때문에 복사해서 받습니다. const 참조자로 받아도 되지만, 기본 자료형이니 굳이 그럴 필요가 없습니다.

	// 조금 더 흥미로운 내용을 위해서, 적들에게 간단한 이동 로직을 추가해 보겠습니다.
	// 적들이 Update마다 플레이어의 방향으로 움직이는 로직을 추가하려고 합니다.
	for (int i = 0; i < enemyCount; i++)
	{
		float vectorX = playerPosition.x - enemyPosition[i].x; // enemy에서 player로 향하는 벡터의 x방향 성분
		float vectorY = playerPosition.y - enemyPosition[i].y; // enemy에서 player로 향하는 벡터의 y방향 성분

		float length = sqrt(vectorX * vectorX + vectorY * vectorY); // 벡터의 길이

		vectorX = vectorX / length; // 길이가 1인 벡터의 x방향 성분
		vectorY = vectorY / length; // 길이가 1인 벡터의 y방향 성분

		enemyPosition[i].x += vectorX * enemySpeed; // speed 만큼의 속도로 player쪽으로 이동하게 됩니다
		enemyPosition[i].y += vectorY * enemySpeed;
	}
	

}

// 적을 그리는 연산은 이 곳에 함수로 모아 뒀습니다.
void DrawEnemy(const Vector2* const enemyPosition, int enemyCount, float enemyRadius, Color enemyColor)
{
	for (int i = 0; i < enemyCount; i++)
	{
		DrawCircle(enemyPosition[i].x, enemyPosition[i].y, enemyRadius, enemyColor); // 적 그리기. 적은 동그라미로 그려줍시다.
		DrawCircleLines(enemyPosition[i].x, enemyPosition[i].y, enemyRadius, BLACK); // 똑같은 위치에 속이 빈 원을 검은 테두리로 덧그리면 눈에 더 잘뜨입니다.

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
	// Vector2는 기존에 사용하던 Color처럼, 2개의 float 변수를 담을 수 있는 구조체입니다.
	// Vector2를 사용하면 코드를 조금 더 깔끔하게 정리할 수 있습니다. 
	// 2개의 값은 각각 .x, .y를 사용해 접근할 수 있습니다.
	Vector2 playerPosition = Vector2{ 10,10 };
	const Vector2 playerSize = Vector2{ 20,20 };
	const Color playerColor = Color{ 238, 108, 77, 255 };

	//--- 화면에 그릴 적 관련 변수
	const float enemyCount = 10; // 적은 10 마리를 그릴 예정입니다. 배열 크기로 사용하기 위해 const 여야 한다는 것을 잊지 마세요
	// 이번 장에서는 적의 X와 Y위치를 힙 메모리에 저장해 봅시다. 사실 크게 바뀔 건 없죠? 대신, 해제 부분을 절대 잊으시면 안됩니다.
	Vector2* enemyPosition = new Vector2[enemyCount];
	const float enemySpeed = 1.5f; // enemy는 player보다 약간 느린 속도로 움직입니다.
	const float enemyRadius = 10; // 적은 동그라미로 그릴 것이라 width/height 대신 반지름이 필요합니다.
	const Color enemyColor = Color{ 200, 150, 255, 255 };

	// 적의 X, Y 위치 배열에 값을 넣어주겠습니다.
	for (int i = 0; i < enemyCount; i++)
	{
		enemyPosition[i] = Vector2{ screenWidth - 20.0f, (float)GetRandomValue(0, screenHeight) };
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
			UpdatePlayer(playerPosition);

			// 이제 적들도 움직입니다.
			UpdateEnemy(enemySpeed, enemyPosition, enemyCount, playerPosition);
		}

		{ // 그리기 (Draw)
			BeginDrawing();

			ClearBackground(backgroundColor); // 배경 그리기

			DrawRectangle(playerPosition.x, playerPosition.y, playerSize.x, playerSize.y, playerColor); // 플레이어 그리기

			DrawEnemy(enemyPosition, enemyCount, enemyRadius, enemyColor); // 적 그리기

			EndDrawing();
		}
	}

	{
		// 메모리 해제는 절대 잊으시면 안됩니다!
		delete[] enemyPosition;
	}

	return 0;
}

//--- Practice

// 1. enemySpeed와 enemyRadius도 2개의 값인데, Vector2로 바꾸어 주지 않았습니다. 제가 왜 그랬을까요?
// 2. Vector2 말고 라이브러리에서 제공하는 다른 구조체는 또 무엇이 있는지 찾아 보세요.
// 3. SetTargetFPS(120)으로 값을 바꾸어 플레이 해보세요. 뭐가 어떻게 바뀐것인지 이해해 보세요.
