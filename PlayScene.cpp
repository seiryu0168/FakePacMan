#include "PlayScene.h"
#include"player.h"
#include"stage.h"
#include"Enemy.h"
#include"Engine/Camera.h"

PlayScene::PlayScene(GameObject* parent)
	: GameObject(parent, "PlayScene"),hModel_(-1)
{
}

//‰Šú‰»
void PlayScene::Initialize()
{
	Instantiate<stage>(this);
	Instantiate<player>(this);
	Instantiate<Enemy>(this);
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
