#include "raylib.h"
#include "raymath.h" // sqrt 계산을 위해 math 라이브러리도 사용합니다.

#include "Player.h"
#include "Enemy.h"

// 화면에 그릴 수 있는 여러가지는 https://www.raylib.com/cheatsheet/cheatsheet.html 사이트를 참고하세요
// 빌드 결과 .exe 파일은 "CPP_Practice_Game/bin/Debug 또는 Release 폴더 안에 들어가게 되어 있습니다.

int main() {
	int screenWidth = 800;
	int screenHeight = 450;

	// 윈도우 만들기
	InitWindow(screenWidth, screenHeight, "MyGame"); 

	SetTargetFPS(60); 

	//--- 플레이어
	Player player = Player{ Vector2{10,10}, Vector2{20,20}, Color{238, 108, 77, 255}, 120.0f };

	//--- 적(들) 
	const float enemyCount = 10; 
	Enemy* enemies = new Enemy[enemyCount];
	
	for (int i = 0; i < enemyCount; i++)
	{
		Vector2 randomEnemyPosition = Vector2{ screenWidth - 20.0f, (float)GetRandomValue(0, screenHeight) };
		enemies[i] = Enemy{ randomEnemyPosition, Vector2{10.0f,10.0f}, Color{ 200, 150, 255, 255 }, 80.0f };
	}

	//--- 배경색과 사각형의 색상을 바꾸지 않는다고 하면, 상수로 선언
	const Color backgroundColor = Color{ 224, 251, 252, 255 };
	

	// 창을 닫을 때까지 while 반복문을 돌면서 화면을 그리기 위한 함수들을 호출
	while (!WindowShouldClose())
	{
		{ // 데이터 조작 (Update)
			
			float tick = GetFrameTime(); // FPS가 60이라면 1/60, 144라면 1/144에 가까운 값이 반환됩니다.

			player.Update(tick);

			for (int i = 0; i < enemyCount; i++)
			{
				// 각 적의 개별적인 움직임은, 각 적 객체의 Update() 함수 내부에 구현되어 있습니다.
				// 그 멤버함수는 멤버변수 데이터를 기반으로 움직임 로직을 수행합니다.
				enemies[i].Update(tick, player.GetPosition()); 
			}
		}

		{ // 그리기 (Draw)
			BeginDrawing();

			ClearBackground(backgroundColor); // 배경 그리기

			player.Draw(); // 플레이어 그리기

			// 적(들) 그리기
			for (int i = 0; i < enemyCount; i++)
			{
				// 마찬가지로 각 적의 그리는 법은 Draw() 함수 내부에 구현되어 있습니다.
				enemies[i].Draw();
			}

			EndDrawing();
		}
	}

	{
		// 메모리 해제는 절대 잊으시면 안됩니다!
		delete[] enemies;
	}

	return 0;
}

//--- Practice

// 1. Enemy 클래스를 통한 Encapsulation의 장점 중 하나로, 개별 객체가 다른 속성을 가지는 경우에 대한 처리가 쉬워 졌다는 것입니다.
//	  Enemies를 생성할 때 무작위로 색상, 크기 또는 속도를 부여하도록 수정해 보세요. 그리고 수정해야 하는 코드가 얼마나 적은지 체감해보세요.
//	  만일 클래스가 없었다면 얼마나 많은 수정을 해야 하고, 코드가 복잡해졌을지 상상이 되시나요?
// 2. Enemy 배열을 main 함수에서 배열로 관리하는 것 또한 더 추상화를 시키고 싶습니다. OOP Part2 강의자료를 참고해서 EnemyManager클래스를 만들어보세요
// 3. EnemyManager 클래스를 만들고 나서, 적들이 한꺼번이 아니고 몇 초에 한번씩 등장하도록 바꾸어 볼겁니다. 어떻게 구현하면 좋을지 한번 생각해보세요.