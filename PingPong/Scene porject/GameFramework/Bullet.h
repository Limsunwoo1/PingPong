#pragma once
#include "Object.h"

using namespace std;
enum class Direction : short
{
    NONE    = 0,
    EAST    = 5,
    WEST    = 10,
    SOUTH   = 15,
    NORTH   = 20,
    MAX     = 25,
};
class CBullet :
    public CObject
{
private:
    bool        mStart;
    float       mDeleta;
    Vector2D    mPrvePosition;
    Vector2D    mPrveScale;

    Direction   mHigh;
    Direction   mWidth;
public:
    CBullet();
    CBullet(Vector2D InPosition, Vector2D InScale);
    ~CBullet();

    virtual void Update(float InDeletaTime) override;
    virtual void Collision(const CObject* InOtherObject) override;
public:
    void ScreenOut();
};

