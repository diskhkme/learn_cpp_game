#include "raylib-cpp.hpp" 

// 화면에 그릴 수 있는 여러가지는 https://www.raylib.com/cheatsheet/cheatsheet.html 사이트를 참고하세요
// 빌드 결과 .exe 파일은 "CPP_Practice_Game/bin/Debug 또는 Release 폴더 안에 들어가게 되어 있습니다.

int main() {
	int screenWidth = 800;
	int screenHeight = 450;

	raylib::Window window(screenWidth, screenHeight, "0_Introduction");

	SetTargetFPS(60); 

	//--- 화면에 그릴 사각형 관련 변수
	int rectPositionX = 10;
	int rectPositionY = 10;
	int rectWidth = 20;
	int rectHeight = 20;

	//--- 배경색과 사각형의 색상을 바꾸지 않는다고 하면, 상수로 선언하는 것이 맞습니다.
	// (조금 더 보기좋은 색상을 사용하기 위해 https://coolors.co/?home 사용하였습니다.)
	const Color backgroundColor = Color{ 224, 251, 252, 255 };
	const Color rectangleColor = Color{ 238, 108, 77, 255 };
		
	while (!window.ShouldClose())
	{
		// 일반적으로 게임을 만들때 loop 안에서는 데이터 조작과 조작된 데이터를 기반으로 한 화면 그리기를 수행합니다.
		// 여기에서도 이렇게 두 부분으로 구분해서 구현할 것이며, 중괄호, 들여쓰기 등은 문법적으로 의미는 없고, 보기 좋게 하기위해 들어간 것입니다.

		{ // 데이터 조작 (Update)
			rectPositionX = rectPositionX + 1; // 매 loop마다 rectPosition 변수를 1씩 증가시킵니다.

		}

		{ // 그리기 (Draw)
			BeginDrawing(); 

				window.ClearBackground(backgroundColor); // 배경색은 whiel문 밖에 선언되어 있기 때문에, 여기서 접근할 수 있습니다.
		
				DrawRectangle(rectPositionX, rectPositionY, rectWidth, rectHeight, rectangleColor);	
				// 사각형 그리기에 상수값(10,20)을 사용하는 대신, 위에 선언해둔 변수를 사용합니다.

			EndDrawing(); 
		}
	}

	return 0;
}

//--- Practice

// 1. 사각형의 이동 속도를 더 증가시켜보세요.
// 2. 사각형의 이동 방향을 바꿔 보세요. 예를들어 오른쪽 아래로 이동하도록 해 보세요.
// 3. 사각형이 화면 끝까지 가면 사라져버립니다. 이럴 경우 화면 왼쪽에서 다시 나타나도록 코드를 수정해 보세요.