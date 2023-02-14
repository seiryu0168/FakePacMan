#include "Enemy.h"
#include"Engine/Model.h"
#include"player.h"
Enemy::Enemy(GameObject* parent)
	:GameObject(parent,"Enemy"),
	time_(0),
	onScerch_(false)
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
		if (CulcDistance(pPlayer->GetPosition(),transform_.position_)>=10.0f&&AI_.GetChaseStap()>=0.5f)
			AI_.SetChaseFlag(false);
	}
}

void Enemy::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

float Enemy::CulcDistance(XMFLOAT3 targetPos, XMFLOAT3 startPos)
{
	float a = sqrt((targetPos.x - startPos.x) * (targetPos.x - startPos.x) + (targetPos.z - startPos.z) * (targetPos.z - startPos.z));
	return a;
}
void Enemy::Release()
{
}
