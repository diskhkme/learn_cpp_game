#include "raylib.h"

// 화면에 그릴 수 있는 여러가지는 https://www.raylib.com/cheatsheet/cheatsheet.html 사이트를 참고하세요
// 빌드 결과 .exe 파일은 "CPP_Practice_Game/bin/Debug 또는 Release 폴더 안에 들어가게 되어 있습니다.


// 플레이어의 이동 관련한 연산을 모두 이곳에 모아 놓으면 보기가 좋겠죠?
void Update(int& playerPositionX, int& playerPositionY)
{
	// IsKeyDown(keyCode) 함수를 사용하면, 해당 키보드가 눌렸는지 여부를 bool로 반환해줍니다.

	if (IsKeyDown(KEY_RIGHT)) playerPositionX += 2;
	else if (IsKeyDown(KEY_LEFT)) playerPositionX -= 2;

	if (IsKeyDown(KEY_UP)) playerPositionY -= 2;
	else if (IsKeyDown(KEY_DOWN)) playerPositionY += 2;
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

			EndDrawing();
		}
	}

	return 0;
}

//--- Practice

// 1. 참조자가 아닌 포인터로 Update() 함수 내에서 main() 함수 내의 지역변수에 접근할 수 있도록 구현해 보세요.
// 2. 화살표 키가 아닌 W,A,S,D 키로 플레이어가 움직이도록 바꾸어 보세요.
// 3. 플레이어의 속도가 너무 느린 것 같습니다. 속도를 더 빠르게 바꾸어 보세요. 효율적으로 하기 위해 playerSpeed 변수를 선언해서 구현해 보세요.
// 4. 플레이어의 가로세로 속도와 대각선 속도가 같을까요? 아니라면 어떻게 해야 일정한 속도로 움직이게 될까요? 