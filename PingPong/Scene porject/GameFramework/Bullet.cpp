#include "Bullet.h"
#include "KeyManager.h"
#include "CSceneManager.h"
#include "MainGame.h"

#define SPEED 800
CBullet::CBullet() : CObject(Vector2D{ 100, 100 }, Vector2D{ 50, 50 })
{
	mStart = false;
	mPrveScale = Vector2D{ 50,50 };

	mHigh	= Direction::NONE;
	mWidth	= Direction::NONE;
}

CBullet::CBullet(Vector2D InPosition, Vector2D InScale) : CObject(Vector2D{ InPosition.x, InPosition.y }, Vector2D{ InScale.x, InScale.y })
{
	mStart = false;
	mPrveScale = Vector2D{ InScale.x, InScale.y };

	mHigh = Direction::NONE;
	mWidth = Direction::NONE;
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
		mHigh = Direction::NORTH;
		if (KEY_STATE(KEY::D) == KEY_STATE::HOLD)
		{
			Position.x += SPEED * InDeletaTime;
			mWidth = Direction::EAST;
		}
		if (KEY_STATE(KEY::A) == KEY_STATE::HOLD)
		{
			Position.x -= SPEED * InDeletaTime;
			mWidth = Direction::WEST;
		}
	}

	//이전위치와 대조하여 진행방향 결정
	/*if (mPrvePosition.x < Position.x)
		Position.x += SPEED * InDeletaTime;
	if(mPrvePosition.x > Position.x)
		Position.x -= SPEED * InDeletaTime;
	if (mPrvePosition.y < Position.y)
		Position.y += SPEED * InDeletaTime;
	if (mPrvePosition.y > Position.y)
		Position.y -= SPEED * InDeletaTime;*/

	if (mHigh == Direction::NORTH)
	{
		Position.y -= SPEED * InDeletaTime;
	}
	else if (mHigh == Direction::SOUTH)
	{
		Position.y += SPEED * InDeletaTime;
	}
	else;

	if (mWidth == Direction::EAST)
	{
		Position.x += SPEED * InDeletaTime;
	}
	else if (mWidth == Direction::WEST)
	{
		Position.x -= SPEED * InDeletaTime;
	}
	else;

	//화면밖을 나가려는 경우
	ScreenOut();
}

void CBullet::Collision(const CObject* InOtherObject)
{
	CObject::Collision(InOtherObject);
	
	if (Position.x - (Scale.x * 0.5f) < InOtherObject->GetPosition().x + (InOtherObject->GetScale().x * 0.5f))
	{
		if (Position.y - (Scale.y * 0.5f) < InOtherObject->GetPosition().y + (InOtherObject->GetScale().y * 0.5f))
		{
			float width = Position.x - (Scale.x * 0.5f) - InOtherObject->GetPosition().x + (InOtherObject->GetScale().x * 0.5f);
			float High = Position.y - (Scale.y * 0.5f) - InOtherObject->GetPosition().y + (InOtherObject->GetScale().y * 0.5f);

			if (High > width)
			{
				mWidth = Direction::EAST;
				mHigh =	Direction::NORTH;
			}
			else
			{
				mWidth = Direction::WEST;
				mHigh = Direction::SOUTH;
			}
		}
		else if (Position.y + (Scale.y * 0.5f) > InOtherObject->GetPosition().y - (InOtherObject->GetScale().y * 0.5f))
		{
			float width = Position.x - (Scale.x * 0.5f) - InOtherObject->GetPosition().x + (InOtherObject->GetScale().x * 0.5f);
			float High = Position.y + (Scale.y * 0.5f) - InOtherObject->GetPosition().y - (InOtherObject->GetScale().y * 0.5f);

			if (High < width)
			{
				mWidth = Direction::EAST;
				mHigh = Direction::SOUTH;
			}
			else
			{
				mWidth = Direction::WEST;
				mHigh = Direction::NORTH;
			}
		}
	}
	else if(Position.x + (Scale.x * 0.5f) > InOtherObject->GetPosition().x - (InOtherObject->GetScale().x * 0.5f))
	{
		if (Position.y - (Scale.y * 0.5f) < InOtherObject->GetPosition().y + (InOtherObject->GetScale().y * 0.5f))
		{
			float width = Position.x + (Scale.x * 0.5f) - InOtherObject->GetPosition().x - (InOtherObject->GetScale().x * 0.5f);
			float High = Position.y - (Scale.y * 0.5f) - InOtherObject->GetPosition().y + (InOtherObject->GetScale().y * 0.5f);

			if (High < width)
			{
				mWidth = Direction::WEST;
				mHigh = Direction::NORTH;
			}
			else
			{
				mWidth = Direction::EAST;
				mHigh = Direction::SOUTH;
			}
		}
		else if (Position.y + (Scale.y * 0.5f) > InOtherObject->GetPosition().y - (InOtherObject->GetScale().y * 0.5f))
		{
			float width = Position.x - (Scale.x * 0.5f) - InOtherObject->GetPosition().x + (InOtherObject->GetScale().x * 0.5f);
			float High = Position.y + (Scale.y * 0.5f) - InOtherObject->GetPosition().y - (InOtherObject->GetScale().y * 0.5f);

			if (High > width)
			{
				mWidth = Direction::EAST;
				mHigh = Direction::SOUTH;
			}
			else
			{
				mWidth = Direction::WEST;
				mHigh = Direction::NORTH;
			}
		}
	}

	//return;
	//}

	////Position.x += Position.x - mPrvePosition.x;
	////Position.y += Position.y - mPrvePosition.y;
	//
	////CheckCollision(this->GetPosition(), this->GetScale(), InOtherObject->GetPosition(), InOtherObject->GetScale());

	//if (Position.x < mPrvePosition.x)
	//{
	//	mPrvePosition.x = Position.x;
	//	Position.x -= SPEED * mDeleta;
	//}
	//else if(Position.x > mPrvePosition.x)
	//{
	//	mPrvePosition.x = Position.x;
	//	Position.x += SPEED * mDeleta;
	//}

	//if (mPrvePosition.y < Position.y)
	//{
	//	mPrvePosition.y = Position.y;
	//	Position.y -= SPEED * mDeleta;
	//}
	//else if(mPrvePosition.y > Position.y)
	//{
	//	mPrvePosition.y = Position.y;
	//	Position.y += SPEED * mDeleta;
	//}
}

void CBullet::ScreenOut()
{
	if (Position.x <= 0)
	{
		mWidth = Direction::EAST;
	}
	else if (Position.x >= 980)
	{
		mWidth = Direction::WEST;
	}

	if (Position.y <= 0)
	{
		mHigh = Direction::SOUTH;
	}
	else if (Position.y >= 680)
	{
		mHigh = Direction::NORTH;
	}
}