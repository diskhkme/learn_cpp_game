#include "raylib.h" 

// 화면에 그릴 수 있는 여러가지는 https://www.raylib.com/cheatsheet/cheatsheet.html 사이트를 참고하세요
// 빌드 결과 .exe 파일은 "CPP_Practice_Game/bin/Debug폴더 안에 들어가게 되어 있습니다.

// 별도의 함수에서 Update와 Draw를 하기 때문에, 공통으로 사용하는 변수는 이제 전역변수로 만들어 줍니다.
int playerPositionX = 10;
int PlayerPositionY = 10;

// 플레이어의 크기와 색상은 변하지 않는다고 합시다.
const int playerWidth = 20;
const int playerHeight = 20;
const Color playerColor = Color{ 238, 108, 77, 255 };

const Color backgroundColor = Color{ 224, 251, 252, 255 };

void Update() // 연산 동작은 이곳에 모아서 구현하면 보기가 좋을겁니다.
{
	// IsKeyDown(keyCode) 함수를 사용하면, 해당 키보드가 눌렸는지 여부를 bool로 반환해줍니다.

	if (IsKeyDown(KEY_RIGHT)) playerPositionX += 2;
	else if (IsKeyDown(KEY_LEFT)) playerPositionX -= 2;

	if (IsKeyDown(KEY_UP)) PlayerPositionY -= 2;
	else if (IsKeyDown(KEY_DOWN)) PlayerPositionY += 2;
}

void Draw() // 그리기 동작은 이곳에 모아서 구현하면 보기가 좋을겁니다.
{
	ClearBackground(backgroundColor);

	DrawRectangle(playerPositionX, PlayerPositionY, playerWidth, playerHeight, playerColor);
}

int main() {
	int screenWidth = 800;
	int screenHeight = 450;

	InitWindow(screenWidth, screenHeight, "2_Function_Player_Movement");

	SetTargetFPS(60);

	while (!WindowShouldClose())
	{
		Update();

		BeginDrawing();

			Draw();

		EndDrawing();
	}

	return 0;
}

//--- Practice

// 1. 화살표 키가 아닌 W,A,S,D 키로 플레이어가 움직이도록 바꾸어 보세요.
// 2. 플레이어의 속도가 너무 느린 것 같습니다. 속도를 더 빠르게 바꾸어 보세요. 효율적으로 하기 위해 playerSpeed 전역 변수를 선언해서 구현해 보세요.
// 3. 플레이어의 가로세로 속도와 대각선 속도가 같을까요? 아니라면 어떻게 해야 일정한 속도로 움직이게 될까요? 
// 4. 마우스 입력은 어떻게 처리하는걸까요? 스스로 한 번 찾아보세요!