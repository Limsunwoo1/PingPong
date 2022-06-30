#pragma once
#include "Object.h"

using namespace std;

class CBullet :
    public CObject
{
private:
    bool        mStart;
    float       mDeleta;
    Vector2D    mPrevPosition;
    Vector2D    mPrveScale;
    
    Vector2D    Direcetion;
    Vector2D    CollisionDirection;
public:
    CBullet();
    CBullet(Vector2D InPosition, Vector2D InScale);
    ~CBullet();

    virtual void Update(float InDeletaTime) override;
    virtual void Collision(const CObject* InOtherObject) override;
public:
    void ScreenOut();
};

