#include "CTitleScene.h"
#include "Func.h"
#include "Button.h"
#include "Player.h"
#include "Block.h"
#include "Bullet.h"
#include "CSceneManager.h"
#include "ResourceManager.h"
#include <string>

CTitleScene::CTitleScene() 
{
}

CTitleScene::~CTitleScene()
{

}

void CTitleScene::Init()
{
	CObject* Player = new CPlayer();
	Player->SetObjectLayer(OBJ_LAYER::PLAYER);
	Player->SetPosition(Vector2D(500, 550));
	Player->SetTexture(CResourceManager::GetInstance()->FindTexture("PLAYER"));
	Player->SetOBJ_Angle();
	AddObject(OBJ_LAYER::PLAYER, Player);

	for (int i = 0; i < 15; ++i)
	{
		static float Interval = 0.f;
		Vector2D InPosition{ 100 + Interval , 100 };
		CObject* CBlock = new Block(InPosition, Vector2D{50, 50});
		CBlock->SetObjectLayer(OBJ_LAYER::BLOCK);
		CBlock->SetTexture(CResourceManager::GetInstance()->FindTexture("BLOCK"));
		AddObject(OBJ_LAYER::BLOCK, CBlock);
		Interval += 50.f;
	}

	for (int i = 0; i < 15; ++i)
	{
		static float Interval = 0.f;
		Vector2D InPosition{ 100 + Interval , 125 };
		CObject* CBlock = new Block(InPosition, Vector2D{ 50, 50 });
		CBlock->SetObjectLayer(OBJ_LAYER::BLOCK);
		CBlock->SetTexture(CResourceManager::GetInstance()->FindTexture("BLOCK"));
		AddObject(OBJ_LAYER::BLOCK, CBlock);
		Interval += 50.f;
	}

	for (int i = 0; i < 15; ++i)
	{
		static float Interval = 0.f;
		Vector2D InPosition{ 100 + Interval , 150 };
		CObject* CBlock = new Block(InPosition, Vector2D{ 50, 50 });
		CBlock->SetObjectLayer(OBJ_LAYER::BLOCK);
		CBlock->SetTexture(CResourceManager::GetInstance()->FindTexture("BLOCK"));
		AddObject(OBJ_LAYER::BLOCK, CBlock);
		Interval += 50.f;
	}

	for (int i = 0; i < 15; ++i)
	{
		static float Interval = 0.f;
		Vector2D InPosition{ 100 + Interval , 175 };
		CObject* CBlock = new Block(InPosition, Vector2D{ 50, 50 });
		CBlock->SetObjectLayer(OBJ_LAYER::BLOCK);
		CBlock->SetTexture(CResourceManager::GetInstance()->FindTexture("BLOCK"));
		AddObject(OBJ_LAYER::BLOCK, CBlock);
		Interval += 50.f;
	}

	CObject* Bullet = new CBullet();
	Bullet->SetObjectLayer(OBJ_LAYER::BULLET);
	Bullet->SetTexture(CResourceManager::GetInstance()->FindTexture("BULLET"));
	AddObject(OBJ_LAYER::BULLET, Bullet);
	// UI는 충돌체크하면 로직이 꼬일수도 있음 체크해도 UI 끼리만 하도록 주의

	std::vector<OBJ_LAYER> checkLayerList;
	checkLayerList.push_back(OBJ_LAYER::PLAYER);
	CheckCollisionLayer[OBJ_LAYER::BULLET] = checkLayerList;
	checkLayerList.push_back(OBJ_LAYER::BLOCK);
	CheckCollisionLayer[OBJ_LAYER::BULLET] = checkLayerList;
}

void CTitleScene::Clear()
{	
	CScene::Clear();
}

void CTitleScene::Update(float InDeltaTime)
{
	CScene::Update(InDeltaTime);
}