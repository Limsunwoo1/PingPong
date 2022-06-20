#include "Bullet.h"
#include "KeyManager.h"
#include "CSceneManager.h"
#include "MainGame.h"

#define SPEED 800
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
		mPrvePosition = Position;

		Position.y -= SPEED * InDeletaTime;
		if(KEY_STATE(KEY::D) == KEY_STATE::HOLD)
			Position.x += SPEED * InDeletaTime;
		if (KEY_STATE(KEY::A) == KEY_STATE::HOLD)
			Position.x -= SPEED * InDeletaTime;
	}

	//이전위치와 대조하여 진행방향 결정
	if (mPrvePosition.x < Position.x)
		Position.x += SPEED * InDeletaTime;
	if(mPrvePosition.x > Position.x)
		Position.x -= SPEED * InDeletaTime;
	if (mPrvePosition.y < Position.y)
		Position.y += SPEED * InDeletaTime;
	if (mPrvePosition.y > Position.y)
		Position.y -= SPEED * InDeletaTime;

	//화면밖을 나가려는 경우
	ScreenOut();

	
}

void CBullet::Collision(const CObject* InOtherObject)
{
	CObject::Collision(InOtherObject);



	if (InOtherObject->GetObjectLayer() == OBJ_LAYER::PLAYER)
	{
	if (KEY_STATE(KEY::D) == KEY_STATE::HOLD)
		Position.x += SPEED * mDeleta;
	if (KEY_STATE(KEY::A) == KEY_STATE::HOLD)
		Position.x -= SPEED * mDeleta;

	if (Position.x > InOtherObject->GetPosition().x)
	{
		mPrvePosition.x = Position.x;
		Position.x += SPEED * mDeleta;
	}
	else
	{
		mPrvePosition.x = Position.x;
		Position.x -= SPEED * mDeleta;
	}

	if (mPrvePosition.y < Position.y)
	{
		mPrvePosition.y = Position.y;
		Position.y -= SPEED * mDeleta;
	}
	else
	{
		mPrvePosition.y = Position.y;
		Position.y += SPEED * mDeleta;
	}

	return;
	}

	//Position.x += Position.x - mPrvePosition.x;
	//Position.y += Position.y - mPrvePosition.y;
	
	//CheckCollision(this->GetPosition(), this->GetScale(), InOtherObject->GetPosition(), InOtherObject->GetScale());

	if (Position.x < mPrvePosition.x)
	{
		mPrvePosition.x = Position.x;
		Position.x -= SPEED * mDeleta;
	}
	else if(Position.x > mPrvePosition.x)
	{
		mPrvePosition.x = Position.x;
		Position.x += SPEED * mDeleta;
	}

	if (mPrvePosition.y < Position.y)
	{
		mPrvePosition.y = Position.y;
		Position.y -= SPEED * mDeleta;
	}
	else if(mPrvePosition.y > Position.y)
	{
		mPrvePosition.y = Position.y;
		Position.y += SPEED * mDeleta;
	}
}

void CBullet::ScreenOut()
{
	if (Position.x <= 0)
	{
		mPrvePosition.x = Position.x;
		Position.x += SPEED * mDeleta;
	}
	if (Position.x >= 980)
	{
		mPrvePosition.x = Position.x;
		Position.x -= SPEED * mDeleta;
	}
	if (Position.y <= 0)
	{
		mPrvePosition.y = Position.y;
		Position.y += SPEED * mDeleta;
	}
	if (Position.y >= 660)
	{
		mPrvePosition.y = Position.y;
		Position.y -= SPEED * mDeleta;
	}
}

void CBullet::CheckCollision(Vector2D InPosition1, Vector2D InScale1, Vector2D InPosition2, Vector2D InScale2)
{
	/*if(InPosition1.x < mPrvePosition.x)
	{
		Position.x -= Position.x - mPrvePosition.x;
	}
	else if (InPosition1.x > mPrvePosition.x)
	{
		Position.x += Position.x - mPrvePosition.x;
	}


	if (InPosition1.y < mPrvePosition.y)
	{
		Position.y -= Position.y - mPrvePosition.y;
	}
	else if (InPosition1.y > mPrvePosition.y)
	{
		Position.y += Position.y - mPrvePosition.y;
	}*/
}