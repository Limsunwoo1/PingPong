#pragma once
#include <math.h>

// ����1.
// ������ �ߴ� �����, �������⿡ �븻���� �����ϱ�

// ����2.
// �¾�� �����
// ���� �¾��ó�� ũ�⸦ �� �ʿ�� ����
// ����, ��, �¾� 3������ �ְ�
// �¾��� ������ ȭ���� ���߾ӿ� ��ġ���ְ�
// ������ �� �Ÿ���ŭ �������ְ� �޵� ���� �������� �� �Ÿ���ŭ �������ִ�
// ���� ���� ������ �����ϰ�
// ������ �¾��� �����Ѵ�.

// ����3.
// https://day-days.tistory.com/1117
// ����� ���� �࿧ �����غ���
// ��ֹ��� ����� �ص� ��

typedef struct Vector2D {
	float x;
	float y;

	Vector2D() : x(0.f), y(0.f) {}
	Vector2D(float InX, float InY) : x(InX), y(InY) {}

	Vector2D operator* (float InValue) { return Vector2D(x * InValue, y * InValue); }

	Vector2D operator- (const Vector2D& InValue) { return Vector2D(x - InValue.x, y - InValue.y); }

	void operator+= (const Vector2D& InValue) {
		x = x + InValue.x;
		y = y + InValue.y;
	}

}Vector2D;

namespace UtilVector
{
	// ũ�Ⱑ 1�� ����ȭ�� ���ʹ� �븻����, ���⺤��, �������Ͷ�� �Ѵ�.
	inline Vector2D Normalize(const Vector2D& InVector)
	{
		float length = sqrt((InVector.x * InVector.x) + (InVector.y * InVector.y));

		if (length != 0)
			return Vector2D(InVector.x / length, InVector.y / length);
		else
			return Vector2D(0.f, 0.f);
	}
}