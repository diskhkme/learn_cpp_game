#pragma once

#include "raylib.h"

#include "Actor.h"
#include "Bullet.h"

// Player 클래스의 정의, 이제 플레이어는 Entity의 유도 클래스입니다.
class Player : public Actor
{
public:
	Player(const Vector2& position, const Vector2& size, Texture2D* tex, int row, int col, float speed, Vector2 direction, int maxHP);
	void Update(float tick);
	void Draw() const;
	Vector2 GetPosition() const;

	// Player가 Bullet을 관리하기 때문에, Bullet 데이터 초기화를 위한 함수를 만들어 두었습니다. 어떤가요?
	void SetWeapon(const Vector2& size, Texture2D* tex, int row, int col, float speed);

private:
	void Shoot(); 

	void UpdateBullets(float tick); 
	void DrawBullets() const; 

private:
	// 공통 데이터는 Entity가 가지고있기 때문에 모두 없애줍니다.

	Bullet bullets[50]; // (우선은) 발사된 총알은 Player 멤버 변수로 두고 관리합니다.
	int bulletCount; // 발사된 총알의 개수

	// Bullet 생성과 관련하여 사용할 데이터
	Vector2 bulletSize;
	Texture* bulletTex;
	int bulletRow;
	int bulletCol;
	float bulletSpeed;
};