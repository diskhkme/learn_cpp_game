#include "raylib.h"
#include "raymath.h" // sqrt 계산을 위해 math 라이브러리도 사용합니다.

// 화면에 그릴 수 있는 여러가지는 https://www.raylib.com/cheatsheet/cheatsheet.html 사이트를 참고하세요
// 빌드 결과 .exe 파일은 "CPP_Practice_Game/bin/Debug 또는 Release 폴더 안에 들어가게 되어 있습니다.

// 플레이어 클래스
class Player
{
public:
	Player(const Vector2& position, const Vector2& size, const Color& color, float speed)
		: position{ position }, size{ size }, color{color}, speed{speed}
	{}
	void Update(float tick) // tick만 인자로 받으면 되는 아주 깔끔한 모양새가 되었습니다!
	{
		Move(tick);
	}
	void Draw() const // 플레이어 그리기
	{
		DrawRectangle(position.x, position.y, size.x, size.y, color); 
		DrawRectangleLines(position.x, position.y, size.x, size.y, BLACK); // 테두리 그리기
	}
	Vector2 GetPosition()
	{
		// 적이 플레이어쪽으로 움직이려면 플레이어 위치값이 필요합니다. 반환해 줄 수 있는 통로를 만들어 줍니다.
		return position;
	}
	
private:
	void Move(float tick) // Move 함수는 굳이 외부로 노출할 필요가 없습니다.
	{
		if (IsKeyDown(KEY_D)) position.x += speed * tick;
		else if (IsKeyDown(KEY_A)) position.x -= speed * tick;

		if (IsKeyDown(KEY_W)) position.y -= speed * tick;
		else if (IsKeyDown(KEY_S)) position.y += speed * tick;
	}

private:
	Vector2 position;
	Vector2 size;
	Color color;
	float speed;
};

void UpdateEnemy(float tick, float enemySpeed, Vector2* enemyPosition, int enemyCount, const Vector2& playerPosition)
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

		enemyPosition[i].x += vectorX * enemySpeed * tick; // speed 만큼의 속도로 player쪽으로 이동하게 됩니다
		enemyPosition[i].y += vectorY * enemySpeed * tick;
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
	// 클래스로 데이터를 묶어놓았으니 아주 깔끔해집니다.
	Player player = Player{ Vector2{10,10}, Vector2{20,20}, Color{238, 108, 77, 255}, 120.0f };

	//--- 화면에 그릴 적 관련 변수
	const float enemyCount = 10; // 적은 10 마리를 그릴 예정입니다. 배열 크기로 사용하기 위해 const 여야 한다는 것을 잊지 마세요
	// 이번 장에서는 적의 X와 Y위치를 힙 메모리에 저장해 봅시다. 사실 크게 바뀔 건 없죠? 대신, 해제 부분을 절대 잊으시면 안됩니다.
	Vector2* enemyPosition = new Vector2[enemyCount];
	const float enemySpeed = 80.0f; // tick을 고려해 속도 스케일 자체가 바뀌었으니(UpdatePlayer 참고) 같이 바꿔줍시다.
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
		{ // 데이터 조작 (Update)
			
			float tick = GetFrameTime(); // FPS가 60이라면 1/60, 144라면 1/144에 가까운 값이 반환됩니다.

			player.Update(tick);
			UpdateEnemy(tick, enemySpeed, enemyPosition, enemyCount, player.GetPosition());
		}

		{ // 그리기 (Draw)
			BeginDrawing();

			ClearBackground(backgroundColor); // 배경 그리기

			player.Draw(); // 플레이어 그리기

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

// 1. Player에게 name 멤버변수를 만들어서 플레이어 머리 위에 이름이 표시되도록 해 보세요.
// 2. 강의 자료를 참고하여 Player 클래스의 구현을 Player.h/Player.cpp에 나누어서 구현해 보세요.
// 3. Enemy 클래스를 만들고 Player 클래스를 추가한 것처럼 코드를 바꾸어 보세요.
