#include "raylib.h" 
#include "raymath.h"

#include "Player.h"
#include "EnemyManager.h"

// 화면에 그릴 수 있는 여러가지는 https://www.raylib.com/cheatsheet/cheatsheet.html 사이트를 참고하세요
// 빌드 결과 .exe 파일은 "CPP_Practice_Game/bin/Debug폴더 안에 들어가게 되어 있습니다.

int main() {
	//--- 윈도우 설정 관련 데이터
	int screenWidth = 800;
	int screenHeight = 450;

	InitWindow(screenWidth, screenHeight, "10_Class_Bullet");

	SetTargetFPS(60);

	const Color backgroundColor = Color{ 224, 251, 252, 255 };

	//--- 플레이어 관련 데이터
	Player player = Player{ 10,10,20,20,Color{238,108,77,255} };

	//--- 적 관련 데이터
	// 이제 여러명의 적들을 관리하는 전반적인 기능은 EnemyManger 클래스로 역할을 넘겨주었습니다.
	EnemyManager enemyManager;
	const int enemyCount = 10;
	const float enemyRadius = 10.0f;
	const Color enemyColor = Color{ 200, 150, 255, 255 };

	for (int i = 0; i < enemyCount; i++)
	{
		float randomYPosition = (float)GetRandomValue(0, screenHeight);
		float xPosition = (float)(screenWidth - 20);
		enemyManager.SpawnEnemy(Vector2{ xPosition,randomYPosition }, enemyRadius, enemyColor);
	}


	while (!WindowShouldClose())
	{
		player.Update(); 
		Vector2 playerPosition = player.GetPosition();
		enemyManager.Update(playerPosition); // 이제는 EnemyManager가 알아서 처리합니다.
		

		BeginDrawing();

		ClearBackground(backgroundColor);
		player.Draw(); // Player 클래스의 Draw 함수를 호출하면, 기존의 DrawPlayer와 동일하게 동작합니다.
		enemyManager.Draw();

		DrawFPS(10, 10);

		EndDrawing();
	}

	return 0;
}

//--- Practice

// 1. EnemyManger를 수정해서 어떤 Enemy는 삼각형으로, 어떤 enemy는 원으로 그리도록 수정해 보세요.
// 2. 위와 같이 수정할 때, Collision 관련 내용을 어떻게 수정하면 좋을지 스스로 생각해 보세요.
// 3. Player의 위치를 계속 인자로 넘겨주지 않고, 좀 더 편리하게 구현할 방법이 있을까요?
