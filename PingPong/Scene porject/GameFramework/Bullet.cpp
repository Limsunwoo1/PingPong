#include "Bullet.h"
#include "KeyManager.h"
#include "CSceneManager.h"
#include "MainGame.h"
#include "UtilMath.h"
#include "Player.h"
#include <cmath>
#include <iostream>
#define SPEED 1200

using namespace std;
class CPlayer;

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
	fps = 0;
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
		Direcetion.y = -1;

		if (KEY_STATE(KEY::D) == KEY_STATE::HOLD)
		{
			Direcetion.x = 1;
		}
		if (KEY_STATE(KEY::A) == KEY_STATE::HOLD)
		{
			Direcetion.x = -1;
		}
	}

	Position += UtilVector::Normalize(Direcetion) * SPEED * InDeletaTime;
	//화면밖을 나가려는 경우
	ScreenOut();
}

void CBullet::Collision(const CObject* InOtherObject)
{
	CObject::Collision(InOtherObject);

	if (fps >= 1)
		return;

	CollisionDirection.x = Position.x - InOtherObject->GetPosition().x;
	CollisionDirection.y = Position.y - InOtherObject->GetPosition().y;
	Vector2D OtherVector;

	Vector2D tset1;
	Vector2D test2;

	tset1 = UtilVector::Normalize(CollisionDirection);

	float that = (tset1.x * 1) + (tset1.y * 0);
	
	float Radian = acos(that);

	//cout << Radian << "  ";

	float Dgree = UtilMath::ToDegree(Radian);

	//cout << Dgree << endl;

	if (InOtherObject->GetObjectLayer() == OBJ_LAYER::PLAYER)
	{
		float PlayerAngle = InOtherObject->GetOBJ_Angle();
		if (Position.y < InOtherObject->GetPosition().y)
		{
			if (Dgree <= PlayerAngle)
			{
				Direcetion.x = abs(Direcetion.x);
			}
			else if (Dgree <= 180 - PlayerAngle && Dgree >= PlayerAngle)
			{
				Direcetion.y = abs(Direcetion.y) * -1;
			}
			else
			{
				Direcetion.x = abs(Direcetion.x) * -1;
			}
		}
		else if (Position.y > InOtherObject->GetPosition().y)
		{
			if (Dgree <= PlayerAngle)
			{
				Direcetion.x = abs(Direcetion.x);
			}
			else if (Dgree <= 180 - PlayerAngle && Dgree >= PlayerAngle)
			{
				Direcetion.y = abs(Direcetion.y);
			}
			else
			{
				Direcetion.x = abs(Direcetion.x) * -1;
			}
		}
		fps++;
		return;
	}

	if (Position.y < InOtherObject->GetPosition().y)
	{
		if (Dgree <= 30.f)
		{
			Direcetion.x = abs(Direcetion.x);
		}
		else if (Dgree < 150 && Dgree > 30)
		{
			Direcetion.y = abs(Direcetion.y) * -1;
		}
		else
		{
			Direcetion.x = abs(Direcetion.x) * -1;
		}
	}
	else if(Position.y > InOtherObject->GetPosition().y)
	{
		if (Dgree <= 30.f)
		{
			Direcetion.x = abs(Direcetion.x);
		}
		else if (Dgree < 150 && Dgree > 30)
		{
			Direcetion.y = abs(Direcetion.y);
		}
		else
		{
			Direcetion.x = abs(Direcetion.x) * -1;
		}
	}

	fps++;
	//오브젝트들의 포지션을 (0,0)으로 이동후 벡터의 내적 추출
}

void CBullet::ScreenOut()
{
	if (Position.x <= 0)
	{
		Position.x = 0; 
		Direcetion .x *= -1;
	}
	else if (Position.x >= 980)
	{
		Position.x = 980;
		Direcetion.x *= -1;
	}

	if (Position.y <= 0)
	{
		Position.y = 0;
		Direcetion.y *= -1;
	}
	else if (Position.y >= 680)
	{
		Position.y = 680;
		Direcetion.y *= -1;
	}
}