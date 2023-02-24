#include "Enemy.h"
#include"Engine/Model.h"
#include"player.h"
Enemy::Enemy(GameObject* parent)
	:GameObject(parent,"Enemy"),
	time_(0),
	status_(STATE::SEARCH),
	bh_(nullptr),
	arrive_(false),
	hModel_(-1)
{
}

Enemy::~Enemy()
{
}

void Enemy::Initialize()
{	
	pPlayer = (player*)FindObject("player");
	//transform_.position_ = { 13,0,13 };
	//hModel_ = Model::Load("Enemy.fbx");
	//assert(hModel_ >= 0);
}

void Enemy::Update()
{
	if (hModel_ < 0)
	{
		hModel_ = Model::Load(bh_->GetModelName()+".fbx");
		assert(hModel_ >= 0);
	}
	bh_->Update();
	XMStoreFloat3(&transform_.position_, XMLoadFloat3(&transform_.position_) + bh_->GetVector());
}

void Enemy::Draw()
{
	if (hModel_ >= 0)
	{
		Model::SetTransform(hModel_, transform_);
		Model::Draw(hModel_);
	}
}

float Enemy::CulcDistance(XMFLOAT3 targetPos, XMFLOAT3 startPos)
{
	float a = sqrtf(powf((targetPos.x - startPos.x),2) + powf((targetPos.z - startPos.z),2));
	return a;
}

void Enemy::Release()
{
}

void Enemy::ChaseMode()
{
	AI_.Calc(pPlayer->GetPosition(), transform_.position_);
		transform_.position_ = AI_.GetPath();
		if (CulcDistance(pPlayer->GetPosition(), transform_.position_) > 5.0f && AI_.GetChaseStep() >= 0.5f)
		{
			AI_.SetChaseFlag(false);
			status_ = STATE::SEARCH;
		}
}

void Enemy::SearchMode()
{
	int x = 0;
	int z = 0;
	bool moveFlag = false;

	if (moveFlag == false)
	{
		for (int i = 0; i < 10; i++)
		{
			x = rand() % 14;
			z = rand() % 14;
			if (AI_.CanMove(XMFLOAT3(x, 0, z)))
			{
				AI_.Calc(XMFLOAT3(x,0,z), transform_.position_);
				moveFlag = true;
				break;
			}
		}
	}

	if (moveFlag)
	{
		transform_.position_ = AI_.GetPath();
		if (AI_.GetChaseStep() >= 1.0f)
		{
			float i = AI_.GetChaseStep();
			moveFlag = false;
		}
	}

	if (CulcDistance(pPlayer->GetPosition(), transform_.position_) < 5)
	{
		float dis = CulcDistance(pPlayer->GetPosition(), transform_.position_);
		status_ = STATE::CHASE;
	}
}
