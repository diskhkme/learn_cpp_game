#pragma once

#include "raylib.h"

#include "Bullet.h"

// Player 클래스의 정의
class Player
{
public:
	// 플레이어를 그리기 위해 색상 대신, 이미지를 활용할 것입니다.
	Player(const Vector2& position, const Vector2& size, const Texture2D& tex, int row, int col, float speed);
	void Update(float tick);
	void Draw() const;
	Vector2 GetPosition() const;

private:
	void Move(float tick, Vector2 moveInput);
	void Shoot(Vector2 shootDirection); // 플레이어는 이제 마우스로 총알을 발사할 수 있습니다. 

	void UpdateBullets(float tick); // 이미 발사된 총알도 계속 업데이트 해주어야 합니다.
	void DrawBullets() const; // 이미 발사된 총알도 계속 그려주어야 합니다.

private:
	Vector2 position;
	Vector2 size;
	Texture2D tex; // Texture2D 이미지에 대한 참조
	Rectangle sourceRect; // row, col 정보를 사용해 어떤 이미지를 가져와 그릴것인지 설정합니다. 생성자를 참고하세요.
	float speed;

	Bullet bullets[50]; // (우선은) 발사된 총알은 Player 멤버 변수로 두고 관리합니다.
	int bulletCount; // 발사된 총알의 개수
};