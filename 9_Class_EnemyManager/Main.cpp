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

	InitWindow(screenWidth, screenHeight, "9_Class_EnemyManager");

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

// 1. Enemy 클래스를 통한 Encapsulation의 장점 중 하나로, 개별 객체가 다른 속성을 가지는 경우에 대한 처리가 쉬워 졌다는 것입니다.
//	  Enemies를 생성할 때 무작위로 색상 또는 radius를 부여하도록 수정해 보세요. 그리고 수정해야 하는 코드가 얼마나 적은지 확인해보세요.
//	  또한 만일 클래스가 없었다면 얼마나 많은 수정을 해야 했을지를 상상해 보세요.
// 2. HandleCollision()과 UpdateEnemy()가 Main.cpp에 남아있는것이 그리 좋지 않아보이지 않나요?
//	  어떻게 구조를 바꾸면 좋을까 스스로 먼저 생각해 보세요.
