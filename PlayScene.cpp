#include "PlayScene.h"
#include"player.h"
#include"stage.h"
#include"Enemy.h"
#include"Red.h"
#include"Engine/Camera.h"

PlayScene::PlayScene(GameObject* parent)
	: GameObject(parent, "PlayScene"),hModel_(-1)
{
}

//‰Šú‰»
void PlayScene::Initialize()
{
	player* pP;
	Instantiate<stage>(this);
	pP = Instantiate<player>(this);
	Enemy* pE = Instantiate<Enemy>(this);
	pE->SetCharactor(new Red(pP,pE));
	pE->SetPosition(XMFLOAT3(1, 0, 13));
	pE = Instantiate<Enemy>(this);
	pE->SetCharactor(new Red(pP, pE));
	pE->SetPosition(XMFLOAT3(13, 0, 13));
	Camera::SetPosition(XMFLOAT3(7.5f, 15, 0));
	Camera::SetTarget(XMFLOAT3(7.5f, 0, 7.5f));
}

//XV
void PlayScene::Update()
{
}

//•`‰æ
void PlayScene::Draw()
{
}

//ŠJ•ú
void PlayScene::Release()
{
}
