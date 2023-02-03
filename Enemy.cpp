#include "Enemy.h"
#include"Engine/Model.h"
#include"player.h"
Enemy::Enemy(GameObject* parent)
	:GameObject(parent,"Enemy")
{
}

Enemy::~Enemy()
{
}

void Enemy::Initialize()
{	
	pPlayer = (player*)FindObject("player");
	transform_.position_ = { 13,0,13 };
	AI_.Init();
}

void Enemy::Update()
{
	AI_.Calc(pPlayer->GetPosition(), transform_.position_);
}

void Enemy::Draw()
{
}

void Enemy::Release()
{
}
