#include "PlayScene.h"
#include"player.h"
#include"stage.h"
#include"Engine/Camera.h"

PlayScene::PlayScene(GameObject* parent)
	: GameObject(parent, "PlayScene"),hModel_(-1)
{
}

//初期化
void PlayScene::Initialize()
{
	Instantiate<stage>(this);
	Instantiate<player>(this);
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
