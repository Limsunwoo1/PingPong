#include "MainGame.h"
#include "TimerManager.h"
#include "KeyManager.h"
#include "CSceneManager.h"
#include "Player.h"
#include "ResourceManager.h"
#include "CollisionManager.h"
#include "EventManager.h"
#include <iostream>
#include <windows.h>

// ����꿡 ������Ʈ �߰��Ҷ� ���ǻ���
// ����Ҹ� �ϳ� ���� ����� ���� ó������ Ŀ���ϴ°� .gitIgnore ������ ���� Ŀ���Ұ�
// .gitIgnore ���Ͽ� C++, ���־� ��Ʃ��� �� ������ �־���� Ŀ���ؾ� �������� ���ϵ��� �ȿö󰣴�
// �� �̱׳�� ���� Ŀ���ϰ� ���ΰ�ħ�ϸ� cpp, h �� �ʼ����� ���ϸ� ����Ʈ�� ������

// ���� 1. 
// ���� �߰��� ���� ũ���� �簢�� ��ֹ��� �ְ� �������� ����� ������ �ؽ��ķ� �� ������Ʈ�� �ִ�
// �׸��� ȭ�� �߾ӿ� �� ������ �ؽ��ķ� �� ������Ʈ�� �ִ�
// ���콺�� Ŭ���ϴ� ���ȿ��� ��� ����� ������Ʈ�� �� ������Ʈ�� ���� �����δ�
// ���콺�� Ŭ���ϴ� ���� �� ������Ʈ�� ���콺 Ŀ�� ��ġ�� �����Ѵ�.
// �̶� ����� ������Ʈ�� ���� ũ���� �簢�� ��ֹ��� ������� ���Ѵ�.

// ���� 2.
// ��������
// ȭ�� ������ ���Ϸ� ���� ��
// ���� ���� ��ư�� ������ 1���������� �Ѿ�� ȭ�� ��ܿ��� ��ϵ��� �����ϰ�
// �ϴܿ��� �¿�� �����̴� ����Ⱑ �ְ�
// ���� ƨ�ܼ� ����� ���� �����ϴ� ����
// �ϴ� ����� hp�� �Ѵ� ������ �μ����ٰ� �����ϰ�
// ���� ������ �ȴٸ� hp�� �����ϰ� hp ���¿� ���� ����� ���°� ���ϰԲ� ( �������� ��� �����ڴٸ� �˼��ְ� )


CMainGame::CMainGame()
{

}

CMainGame::~CMainGame()
{
	// ====================================
	SelectObject(BackHdc, BitMap);
	DeleteObject(BackBitMap);
	DeleteDC(BackHdc);
	// ====================================

	//delete Player;
}

void CMainGame::Init(HWND InHwnd, HINSTANCE InHInstance)
{
	// ====================================
	HInstance = InHInstance;
	Hwnd = InHwnd;
	Hdc = GetDC(Hwnd);

	// �̱��ϵ� �ʱ�ȭ ����
	CResourceManager::GetInstance()->Init(HInstance, Hdc);
	CTimerManager::GetInstance()->Init();
	CKeyManager::GetInstance()->Init();
	CSceneManager::GetInstance()->Init();
	CCollisionManager::GetInstance()->Init();
	CEventManager::GetInstance()->Init();
	//

	// ������۸�
	BackHdc = CreateCompatibleDC(Hdc);
	BackBitMap = CreateCompatibleBitmap(Hdc, 1920, 1080);
	BitMap = (HBITMAP)SelectObject(BackHdc, BackBitMap);   
	// ====================================

	
}

void CMainGame::Logic()
{
	// ====================================
	CTimerManager::GetInstance()->Update();
	float deltaTime = CTimerManager::GetInstance()->GetDeltaTime();
	Update(deltaTime);
	Render();
	// ====================================

	// ��� ���� ������ ���� �Ŀ� �̺�Ʈ�� ó���ϰ� ���� �����ϵ���
	CEventManager::GetInstance()->Update(deltaTime);
}

void CMainGame::Update(float InDeltaTime)
{
	// ====================================
	CKeyManager::GetInstance()->Update(InDeltaTime);
	CSceneManager::GetInstance()->Update(InDeltaTime);
	CCollisionManager::GetInstance()->Update(InDeltaTime);
	// ====================================

	// Render �Ǳ� ������ ������ ������Ʈ
	// ====================================
	CSceneManager::GetInstance()->LateUpdate(InDeltaTime);
	// ====================================
}

void CMainGame::Render()
{
	// ====================================
	Rectangle(BackHdc, 0, 0, 980, 680);

	CSceneManager::GetInstance()->Render(BackHdc);

	BitBlt(Hdc, 0, 0, 980, 680, BackHdc, 0, 0, SRCCOPY);
	// ====================================
}

