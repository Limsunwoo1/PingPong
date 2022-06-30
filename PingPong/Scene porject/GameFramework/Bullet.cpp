#include "Bullet.h"
#include "KeyManager.h"
#include "CSceneManager.h"
#include "MainGame.h"
#include "UtilMath.h"
#include <cmath>
#include <iostream>
#define SPEED 150

using namespace std;

CBullet::CBullet() : CObject(Vector2D{ 100, 100 }, Vector2D{ 50, 50 })
{
	mStart = false;
	mPrveScale = Vector2D{ 50,50 };
}

CBullet::CBullet(Vector2D InPosition, Vector2D InScale) : CObject(Vector2D{ InPosition.x, InPosition.y }, Vector2D{ InScale.x, InScale.y })
{
	mStart = false;
	mPrveScale = Vector2D{ InScale.x, InScale.y };
}

CBullet::~CBullet()
{

}

void CBullet::Update(float InDeletaTime)
{
	CObject::Update(InDeletaTime);
	mDeleta = InDeletaTime;

	if (!mStart)
	{
		int SetY_position = 16;
		CObject* InPlayer = CSceneManager::GetInstance()->Get_Object(OBJ_LAYER::PLAYER)[0];
		Position.x = InPlayer->GetPosition().x;
		Position.y = InPlayer->GetPosition().y - (InPlayer->GetScale().y * 0.5) - SetY_position;
	}

	if (KEY_STATE(KEY::SPACE) == KEY_STATE::HOLD && (!mStart))
	{
		mStart = true;
		mPrevPosition = Position;
		Direcetion.y = -2;

		if (KEY_STATE(KEY::D) == KEY_STATE::HOLD)
		{
			Direcetion.x = 2;
		}
		if (KEY_STATE(KEY::A) == KEY_STATE::HOLD)
		{
			Direcetion.x = -2;
		}
	}

	Position += UtilVector::Normalize(Direcetion) * SPEED * InDeletaTime;
	//화면밖을 나가려는 경우
	ScreenOut();
}

void CBullet::Collision(const CObject* InOtherObject)
{
	CObject::Collision(InOtherObject);

	CollisionDirection.x = InOtherObject->GetPosition().x - Position.x;
	CollisionDirection.y = InOtherObject->GetPosition().y - Position.y;

	Vector2D OtherDirection;
	UtilVector::Normalize(CollisionDirection);
	OtherDirection = UtilVector::Normalize(Vector2D(InOtherObject->GetPosition().x * (InOtherObject->GetScale().x * 0.5f), 0));

	double that = (CollisionDirection.x * OtherDirection.x) + (CollisionDirection.y * OtherDirection.y)/
			sqrt(CollisionDirection.x * CollisionDirection.x + CollisionDirection.y * CollisionDirection.y) *
			sqrt(OtherDirection.x * OtherDirection.x + OtherDirection.y * OtherDirection.y);
	cout << that;
	
	float Dgreed = acos(that);

	cout <<"  "<< UtilMath::ToDegree(Dgreed) << endl;

	//오브젝트들의 포지션을 (0,0)으로 이동후 벡터의 내적 추출
}

void CBullet::ScreenOut()
{
	if ((Position.x <= 0) || (Position.x >= 980))
	{
		Direcetion.x *= -1;
	}

	if ((Position.y <= 0) || (Position.y >= 680))
	{
		Direcetion.y *= -1;
	}
}