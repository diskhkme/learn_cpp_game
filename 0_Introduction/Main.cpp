#include "raylib-cpp.hpp" // 화면을 그리는 데 필요한 기능들이 구현되어 있는 헤더 파일

// 화면에 그릴 수 있는 여러가지는 https://www.raylib.com/cheatsheet/cheatsheet.html 사이트를 참고하세요
// 빌드 결과 .exe 파일은 "CPP_Practice_Game/bin/Debug 또는 Release 폴더 안에 들어가게 되어 있습니다.

int main() {
	// 화면의 가로 및 세로 크기
	int screenWidth = 800;
	int screenHeight = 450;

	// 윈도우 만들기
	raylib::Window window(screenWidth, screenHeight, "0_Introduction"); // Parameter: ((int)가로, (int)세로, (std::string)창 이름)

	SetTargetFPS(60); // 화면을 1초에 몇번 그릴 것인지 (보통은 60번을 사용함. 60 fps(frames per second)

	// 창을 닫을 때까지 while 반복문을 돌면서 화면을 그리기 위한 함수들을 호출
	while (!window.ShouldClose())
	{
		BeginDrawing(); // 무언가를 그리기 전에 BeginDrawing()이 먼저 호출되어야 합니다.

		//------ 그리기 ---------------------------------------------------//
		Color backgroundColor = Color{ 50,50,50,255 };	// Color는 색상 정보를 담기 위한 구조체입니다. R,G,B,A 값을 설정할 수 있습니다.
														// 예를들어 빨간색은 Color{255,0,0,255}로 정의됩니다.
		
		window.ClearBackground(backgroundColor); // 배경을 위에 설정한 backgroundColor값으로 칠합니다.

		Color rectangleColor = Color{ 255, 255, 255, 255 }; // 사각형의 색상인 흰색을 rectangleColor에 저장합니다.

		DrawRectangle(10, 10, 20, 20, rectangleColor);	// DrawRectangle 함수를 호출해 배경 위에 사각형을 그립니다.
														// Parameter: ((int)가로위치, (int)세로위치, (int)사각형의 넓이, (int)사각형의 높이, (Color)사각형 색상)
														// (Note) 사각형의 위치와 크기를 원하는대로 바꿔 보세요
		
		DrawText("Hello World!", 190, 200, 20, LIGHTGRAY); // DrawText를 사용해 화면에 문자를 표시할 수도 있습니다!
		//-----------------------------------------------------------------//
		
		EndDrawing(); // 그리기가 끝나면, EndDrawing()을 호출해야 합니다.
	}

	return 0;
}

//--- Practice

// 1. 화면의 크기를 더 크게, 또는 더 작게 만들어 보세요.
// 2. 사각형을 화면의 다른 위치에, 다른 크기로 만들어 보세요.
// 3. 사각형 대신 원을 화면에 그려보세요.