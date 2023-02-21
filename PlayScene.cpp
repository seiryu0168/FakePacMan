#include "PlayScene.h"
#include"player.h"
#include"stage.h"
#include"Enemy.h"
#include"Red.h"
#include"Yellow.h"
#include"Engine/Camera.h"

PlayScene::PlayScene(GameObject* parent)
	: GameObject(parent, "PlayScene"),hModel_(-1)
{
}

//初期化
void PlayScene::Initialize()
{
	player* pP;
	Instantiate<stage>(this);
	pP = Instantiate<player>(this);
	Enemy* pE = Instantiate<Enemy>(this);
	pE->SetCharactor(new Red(pP,pE));
	pE->SetPosition(XMFLOAT3(1, 0, 13));
	pE = Instantiate<Enemy>(this);
	pE->SetCharactor(new Yellow(pP, pE));
	pE->SetPosition(XMFLOAT3(13, 0, 13));
	Camera::SetPosition(XMFLOAT3(7.5f, 15, 0));
	Camera::SetTarget(XMFLOAT3(7.5f, 0, 7.5f));
}

//更新
void PlayScene::Update()
{
}

//描画
void PlayScene::Draw()
{
}

//開放
void PlayScene::Release()
{
}
