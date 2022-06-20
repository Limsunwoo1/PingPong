#pragma once
#include "Object.h"

class CBullet :
    public CObject
{
private:
    bool        mStart;
    float       mDeleta;
    Vector2D    mPrvePosition;
    Vector2D    mPrveScale;

public:
    CBullet();
    CBullet(Vector2D InPosition, Vector2D InScale);
    ~CBullet();

public:
    virtual void Update(float InDeletaTime) override;
    virtual void Collision(const CObject* InOtherObject) override;

    void CheckCollision(Vector2D InPosition1, Vector2D InScale1, Vector2D InPosition2, Vector2D InScale2);
    void ScreenOut();
};

