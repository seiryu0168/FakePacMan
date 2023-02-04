#include "Enemy.h"
#include"Engine/Model.h"
#include"player.h"
Enemy::Enemy(GameObject* parent)
	:GameObject(parent,"Enemy"),
	time_(0)
{
}

Enemy::~Enemy()
{
}

void Enemy::Initialize()
{	
	pPlayer = (player*)FindObject("player");
	transform_.position_ = { 13,0,13 };
	hModel_ = Model::Load("pacman.fbx");
	assert(hModel_ >= 0);
	AI_.Init();
}

void Enemy::Update()
{
	time_++;
	AI_.Calc(pPlayer->GetPosition(), transform_.position_);
	if (time_ % 10 == 0)
	{
		transform_.position_ = AI_.GetPath();
		transform_.position_.x += 0.5f;
		transform_.position_.z += 0.5f;
	}
}

void Enemy::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void Enemy::Release()
{
}
