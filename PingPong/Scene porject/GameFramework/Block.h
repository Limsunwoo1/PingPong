#pragma once
#include "Object.h"
class Block :
    public CObject
{
private:
    int HP;
public:
    Block();
    Block(Vector2D InPosition, Vector2D InScale);
    ~Block();

    virtual void Update(float InDeltaTime) override;
    virtual void Render(HDC InHdc) override;
    virtual void Collision(const CObject* InOtherObject) override;
};

