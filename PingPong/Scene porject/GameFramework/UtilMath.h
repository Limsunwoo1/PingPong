#pragma once
#include <math.h>

#define PIE 3.141592

// �ﰢ�Լ� ���� ���ǻ���
// sinf, cosf �� �ﰢ�Լ������ؼ� ���� ��� ���ڴ� ���� �� ( Radian ) �̿����Ѵ�.
// �츮�� ���� 0~360�� ��� ������ 10�����̶�� �ǹ��� ��׸� �� ( Degree )
// Radian �� ������ 0 ~ 360�� �� 0 ~ 2���� ������ ǥ���ȴ�.

// 0 ~ 180 ���� ���� => 0 ~ PIE ������ ������ ��ȯ�Ǵ� ���� ����ٰ� �Ҷ�
// 0 ���� �����ϴ� ��ʽ��� ¥�� �����
// Ư������/Ư�������� �ִ� �� * ��ʵǴ� ������� �ִ밪
// 
// Ư�� �� ���� �����ϴ� ��ʽ�
// 0 ���� �����ϰԲ� ��ʽ��� ����� ����
// Ư������/Ư�������� �ִ� �� * ��ʵǴ� ������� �ִ밪 + ��ʵǴ� ������� �ּҰ�

// minX ~ maxX �� ���� minY ~ maxY
// (X - minX) / (maxX - minX) * maxY + minY

namespace UtilMath
{
	inline float ToRaidan(float InDegree)
	{
		return InDegree / 180.f * PIE;
	}

	inline float ToDegree(float InRadian)
	{
		return InRadian * 180.f / PIE;
	}

	inline float Sin(float InDegree)
	{
		return sinf(ToRaidan(InDegree));
	}

	inline float Cos(float InDegree)
	{
		return cosf(ToRaidan(InDegree));
	}

	inline float Tan(float InDegree)
	{
		return tanf(ToRaidan(InDegree));
	}
}