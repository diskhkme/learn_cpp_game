#pragma once

#include "raylib.h"

// źȯ(Bullet)�� ����ڿ��Լ� ����Ͽ�, ���콺 �������� ���ư��� ��ü�� ���� �����Դϴ�.
// ������ ������ ������鼭 ������ �������� �ֵ��� ���ٵ�, �̹� �忡���� �켱 Ŭ���� ���콺 �������� ���ư��� ������ �ۼ��� ���ô�.
class Bullet
{
private:
	// ��� ������ ����ִ� ���� (��� ��ȭ�ϴ�) ���� ��ġ��� ���� ��Ȯ�ϵ��� �̸��� �ٲپ��ݴϴ�.
	Vector2 currentPosition;
	const Vector2 shootDirection; // źȯ�� ������ ������ �ʱ� ������ const�� ������ �ݴϴ�.
								  // ��� ���絵 (Player, Enemy Ŭ���� � ��������) radius, color ���� ������ ������ ���ݱ��� const�� ������ ���� �ʾҽ��ϴ�.
								  // �̴� ���Ŀ� �̷� ������ ������ ���� ���� �̸� ����Ͽ��� �����Դϴ�. �������� ��������^^; �̻��ϰ� �����ϼ̾�� �½��ϴ�.
	float radius;
	Color color;

	float speed;
public:
	// �ʱ⿡ �����Ҷ��� ���� ��ġ�� ������ �־��ݴϴ�.
	Bullet(Vector2 startPosition, Vector2 direction, float speed, float radius,  Color color);

	void Update();
	void Draw() const;
	Vector2 GetPosition() const;
};