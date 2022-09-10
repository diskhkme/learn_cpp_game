#include "raylib.h"

// 화면에 그릴 수 있는 여러가지는 https://www.raylib.com/cheatsheet/cheatsheet.html 사이트를 참고하세요
// 빌드 결과 .exe 파일은 "CPP_Practice_Game/bin/Debug 또는 Release 폴더 안에 들어가게 되어 있습니다.

int main() {
	// 화면의 가로 및 세로 크기
	int screenWidth = 800;
	int screenHeight = 450;

	// 윈도우 만들기
	InitWindow(screenWidth, screenHeight, "Array, Loop, Condition"); // Parameter: ((int)가로, (int)세로, (std::string)창 이름)

	SetTargetFPS(60); // 화면을 1초에 몇번 그릴 것인지 (보통은 60번을 사용함. 60 fps(frames per second)

	//--- 화면에 그릴 사각형 관련 변수
	const int numSquares = 30;
	int rectPositionX[numSquares];
	int rectPositionY[numSquares];
	Color rectColors[numSquares];
	const int rectWidth = 20;
	const int rectHeight = 20;

	// 위치 및 색상 랜덤 초기화
	for (int i = 0; i < numSquares; i++)
	{
		rectPositionX[i] = GetRandomValue(0, screenWidth); // 라이브러리에서 제공하는 GetRandomValue() 함수를 사용합니다.
		rectPositionY[i] = GetRandomValue(0, screenHeight);

		// 라이브러리에서 색상은 0~255 사이의 값이기 때문에 unsigned char(1바이트)로 정의되어 있습니다.
		unsigned char randomRed = GetRandomValue(0, 255);
		unsigned char randomGreen = GetRandomValue(0, 255);
		unsigned char randomBlue = GetRandomValue(0, 255);

		rectColors[i] = Color{ randomRed, randomGreen, randomBlue, 255 };
	}

	//--- 배경색과 사각형의 색상을 바꾸지 않는다고 하면, 상수로 선언
	const Color backgroundColor = Color{ 224, 251, 252, 255 };

	// 창을 닫을 때까지 while 반복문을 돌면서 화면을 그리기 위한 함수들을 호출
	while (!WindowShouldClose())
	{
		// 일반적으로 게임을 만들때 loop 안에서는 데이터 조작과 조작된 데이터를 기반으로 한 화면 그리기를 수행합니다.
		// 여기에서도 이렇게 두 부분으로 구분해서 구현할 것이며, 중괄호, 들여쓰기 등은 문법적으로 의미는 없고, 보기 좋게 하기위해 들어간 것입니다.

		{ // 데이터 조작 (Update)


		}

		{ // 그리기 (Draw)
			BeginDrawing();

			ClearBackground(backgroundColor); // 배경색은 whiel문 밖에 선언되어 있기 때문에, 여기서 접근할 수 있습니다.

			// numSqueares개의 사각형을, 배열에 저장된 정보를 사용해 그립니다.
			for (int i = 0; i < numSquares; i++)
			{
				DrawRectangle(rectPositionX[i], rectPositionY[i], rectWidth, rectHeight, rectColors[i]);
			}

			EndDrawing();
		}
	}

	return 0;
}

//--- Practice

// 1. 사각형의 크기도 배열을 사용해 각 사각형별로 값을 갖도록 하고, 랜덤으로 초기화 시킨 후 그려 보세요. 
// 2. 게임이 시작되면 사각형들이 오른쪽으로 움직이다가, 화면의 끝에 다다르면 왼쪽으로 움직이도록 구현해 보세요.
// 3. 2번 구현에 이어서 추가적으로, 각 사각형들의 이동 속도가 다르도록 만들어 보세요.
// 4. 시작 시 각 사각형이 왼쪽 또는 오른쪽으로 랜덤하게 움직이도록 구현해 보세요.