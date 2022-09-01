#include "raylib.h" 
#include "raymath.h"

#include "Player.h"
#include "EnemyManager.h"

// 화면에 그릴 수 있는 여러가지는 https://www.raylib.com/cheatsheet/cheatsheet.html 사이트를 참고하세요
// 빌드 결과 .exe 파일은 "CPP_Practice_Game/bin/Debug폴더 안에 들어가게 되어 있습니다.

//---
// 풀어야 하는 수많은 문제들이 남아있지만, 우선 최대한 게임같아 보이도록 하기 위해서 적을 쏴서 없앨 수 있는 기능과,
// 적이 플레이어에게 부딪히면 플레이어의 체력이 깎이는 로직을 추가해 봅시다.


int main() {
	//--- 윈도우 설정 관련 데이터
	int screenWidth = 800;
	int screenHeight = 450;

	InitWindow(screenWidth, screenHeight, "11_Class_Shoot_Enemy");

	SetTargetFPS(60);

	const Color backgroundColor = Color{ 224, 251, 252, 255 };

	//--- 플레이어 관련 데이터
	Player player = Player{ 10,10,20,20,Color{238,108,77,255} };

	//--- 적 관련 데이터
	EnemyManager enemyManager;
	const int enemyCount = 10;
	const float enemyRadius = 10.0f;
	const Color enemyColor = Color{ 200, 150, 255, 255 };
	const int enemyMaxHP = 100;

	for (int i = 0; i < enemyCount; i++)
	{
		float randomYPosition = (float)GetRandomValue(0, screenHeight);
		float xPosition = (float)(screenWidth - 20);
		enemyManager.SpawnEnemy(new Enemy{ Vector2{ xPosition,randomYPosition }, enemyRadius, enemyColor, enemyMaxHP });
	}


	while (!WindowShouldClose())
	{
		player.Update(); // 탄환의 발사 또한 Player 클래스에서 처리해 줍니다.
		Vector2 playerPosition = player.GetPosition();
		enemyManager.Update(player); 
		

		BeginDrawing();

		ClearBackground(backgroundColor);
		player.Draw(); 
		enemyManager.Draw();

		DrawFPS(10, 10);

		EndDrawing();
	}

	return 0;
}

//--- Practice

// 1. 자세히 보면 탄환이 플레이어 가운데서 나가는 것이 아니고 왼쪽 위쪽에서 나가는 것을 볼 수 있습니다. 가운데, 또는 다른 적절한 위치에서 발사되도록 수정해 보세요.
// 2. 탄환을 하나 발사하고, 그 위치를 콘솔창에 출력하거나, 몇초 뒤에 중단점을 걸어서 위치를 확인해보세요. 화면에서 이미 벗어난지 오래입니다. 어떻게 하는것이 좋을까요?
// 3. 당연하지만 현재는 탄환을 50발 이상 발사하게 되면 exception이 발생합니다. 어떤 해결 방법들이 있을까요?
