#include "CTitleScene.h"
#include "Func.h"
#include "Button.h"
#include "Player.h"
#include "Block.h"
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
	AddObject(OBJ_LAYER::PLAYER, Player);

	CObject* Block = new Block();
	Block->SetObjectLayer(OBJ_LAYER::BLOCK);
	Player->SetTexture(CResourceManager::GetInstance()->FindTexture("BLOCK"));
	AddObject(OBJ_LAYER::BLOCK, Block);
	// UI�� �浹üũ�ϸ� ������ ���ϼ��� ���� üũ�ص� UI ������ �ϵ��� ����
	std::vector<OBJ_LAYER> checkLayerList;
	checkLayerList.push_back(OBJ_LAYER::BLOCK);
	CheckCollisionLayer[OBJ_LAYER::PLAYER] = checkLayerList;
}

void CTitleScene::Clear()
{	
	CScene::Clear();
}

void CTitleScene::Update(float InDeltaTime)
{
	CScene::Update(InDeltaTime);
}