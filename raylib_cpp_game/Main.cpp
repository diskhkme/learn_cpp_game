#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include "raylib.h"
#include "raymath.h" // sqrt 계산을 위해 math 라이브러리도 사용합니다.

#include "Player.h"
#include "EnemyManager.h"

// 화면에 그릴 수 있는 여러가지는 https://www.raylib.com/cheatsheet/cheatsheet.html 사이트를 참고하세요

int main() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); // 점점 메모리 관리가 복잡해지고 있으니, 메모리 누수를 탐지하는 코드를 추가하겠습니다.
	//_CrtSetBreakAlloc(1453); // 누수가 있는 경우 그 블럭으로 이동해 체크해 볼 수 있습니다.

	int screenWidth = 800;
	int screenHeight = 450;

	// 윈도우 만들기
	InitWindow(screenWidth, screenHeight, "MyGame"); 

	SetTargetFPS(60); 

	// 텍스처 리소스 Load
	Texture2D shipsTexture = LoadTexture("../Resources/SpaceShooterAssetPack_Ships.png");
	Texture2D projectileTexture = LoadTexture("../Resources/SpaceShooterAssetPack_Projectiles.png");

	//--- 플레이어
	// 이제 플레이어를 삼각형, 사각형이 아닌 이미지를 불러와서 표시할 것입니다.
	Player player = Player{ Vector2{10,10}, Vector2{30,30}, shipsTexture, 0, 1, 120.0f };

	//--- 적 매니저
	EnemyManager enemyManger;
	
	for (int i = 0; i < 10; i++)
	{
		Vector2 randomEnemyPosition = Vector2{ screenWidth - 20.0f, (float)GetRandomValue(0, screenHeight) };
		// SpawnEnemy를 호출해서 생성한 적을 enemyManger가 가지고있는 포인터 멤버 변수에 저장해둡니다.
		enemyManger.SpawnEnemy(new Enemy{ randomEnemyPosition, Vector2{10.0f,10.0f}, Color{ 200, 150, 255, 255 }, 80.0f });
	}

	//--- 배경색과 사각형의 색상을 바꾸지 않는다고 하면, 상수로 선언
	const Color backgroundColor = Color{ 0, 0, 0, 255 };
	

	// 창을 닫을 때까지 while 반복문을 돌면서 화면을 그리기 위한 함수들을 호출
	while (!WindowShouldClose())
	{
		{ // 데이터 조작 (Update)
			
			float tick = GetFrameTime(); // FPS가 60이라면 1/60, 144라면 1/144에 가까운 값이 반환됩니다.

			player.Update(tick); // 플레이어 & 총알 Update()

			enemyManger.Update(tick, player.GetPosition()); // 적 Update()
		}

		{ // 그리기 (Draw)
			BeginDrawing();

			ClearBackground(backgroundColor); // 배경 그리기

			player.Draw(); // 플레이어 & 총알 그리기

			enemyManger.Draw(); // 적 그리기

			EndDrawing();
		}
	}

	{
		// 텍스처 자원도 사용이 끝나면 해제해 주어야 합니다.
		UnloadTexture(shipsTexture);
		UnloadTexture(projectileTexture);

		CloseWindow();
	}

	return 0;
}

//--- Practice

// 1. 적이 한꺼번에 생성되지 않고, 몇 초에 한번씩 생성되도록 코드를 바꿔 보세요.
// 2. Enemy의 update 로직에 player 정보가 필요하기 때문에 EnemyManager의 Update()에만 플레이어 위치를 인자로 넘겨주고 있습니다. 
//    이걸 없앨 수 있는 방법이 뭐가 있을까요? (주의! 없애는 것이 항상 더 좋다는 뜻은 아닙니다.)