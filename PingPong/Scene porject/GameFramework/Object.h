#pragma once
#include "framework.h"

class CTexture;

enum class OBJ_LAYER : short {
	BACKGROUND		= 0,
	BLOCK			= 12,
	PLAYER			= 24,
	BULLET			= 28,
	UI				= 30,
	MAX				= 32,
};

class CObject
{
private:
	static unsigned int Id;
	unsigned int ObjectId;
protected:
	Vector2D		Position;
	Vector2D		Scale;
	Vector2D		CollisionScale; // ������Ʈ ������� �����ϰ� �浹�� ������ �ʿ䰡 ��� ������ ����
	OBJ_LAYER		ObjLayer;

	CTexture*		Texture;

	bool			PrevCollision;
	bool			CurCollision;

	float			Obj_Angle;
public:
	CObject();
	CObject(Vector2D InPosition, Vector2D InScale);
	virtual ~CObject();

	virtual void Update(float InDeltaTime);
	virtual void LateUpdate(float InDeltaTime); // Render �Ǳ� �� ������ ������Ʈ
	virtual void Render(HDC InHdc);

	virtual void Collision(const CObject* InOtherObject);

public:
	void SetTexture(CTexture* InTexture);

	void SetPosition(Vector2D InPosition) { Position = InPosition; }
	Vector2D GetPosition() const { return Position; }

	void SetScale(Vector2D InScale) { Scale = InScale; }
	Vector2D GetScale() const { return Scale; }

	void SetCollisionScale(Vector2D InScale) { CollisionScale = InScale; }
	Vector2D GetCollisionScale() { return CollisionScale; }

	OBJ_LAYER GetObjectLayer() const ;
	void SetObjectLayer(OBJ_LAYER InOBJ_Layer);

	void SetOBJ_Angle();
	float GetOBJ_Angle() const { return Obj_Angle; };

	unsigned int GetId() const {return ObjectId;}
};

