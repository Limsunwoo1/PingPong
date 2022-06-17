#include "Block.h"
#include "ResourceManager.h"
#include "CTexture.h"

Block::Block() : CObject(Vector2D{ 100, 100 }, Vector2D{ 50,50 })
{
	HP = 3;
}

Block::Block(Vector2D InPosition, Vector2D InScale) : CObject(Vector2D{ InPosition.x, InPosition.y }, Vector2D{ InScale.x, InScale.y })
{
	HP = 3;
}

Block::~Block()
{

}

void Block::Update(float InDeltaTime)
{
	CObject::Update(InDeltaTime);

	if (HP == 2)
		CResourceManager::GetInstance()->LoadTexture("BLOCK", L"Texture/YellowBlock/YellowBlock_1.bmp");

	if(HP == 1)
		CResourceManager::GetInstance()->LoadTexture("BLOCK", L"Texture/YellowBlock/YellowBlock_2.bmp");
}

void Block::Collision(const CObject* InOtherObject)
{
	CObject::Collision(InOtherObject);

	HP -= 1;
	/*EventInfo eventInfo;
	eventInfo.Type = EVENT_TYPE::DELETE_OBJECT;
	eventInfo.Parameter = new OBJ_LAYER(ObjLayer);
	eventInfo.Parameter2 = this;
	CEventManager::GetInstance()->AddEvent(eventInfo);*/
}

void Block::Render(HDC InHdc)
{
	// 알파값 == 투명값
	// 투명하게 띄우는거, 반투명하게 띄우는거를 알파블렌딩 이라고 한다
	// 색상을 섞는다는 블렌딩의 의미

	// bmp 파일은 보통 색상이 24비트짜리
	// R : 8비트
	// G : 8비트
	// B : 8비트 0 ~ 255 값
	// 32 비트는 여기에 A : 8 비트가 추가된 값 ( 알파값 )

	if (Texture)
	{
		// 32비트 bmp 는 bf.AlphaFormat = AC_SRC_ALPHA
		// 24비트 bmp 는 bf.AlphaFormat = 0

		BLENDFUNCTION bf = {};
		bf.BlendOp = AC_SRC_OVER;
		bf.BlendFlags = 0;
		bf.AlphaFormat = 0;
		bf.SourceConstantAlpha = 255;

		AlphaBlend(InHdc,
			Position.x - (Texture->GetWidth() * 0.5f),
			Position.y - (Texture->GetHeight() * 0.5f),
			Texture->GetWidth(),
			Texture->GetHeight(),
			Texture->GetHdc(),
			0,
			0,
			Texture->GetWidth(),
			Texture->GetHeight(),
			bf);
	}
	else
	{
		Rectangle(InHdc,
			Position.x - (Scale.x * 0.5f),
			Position.y - (Scale.y * 0.5f),
			Position.x + (Scale.x * 0.5f),
			Position.y + (Scale.y * 0.5f));
	}
}