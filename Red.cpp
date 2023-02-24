#include "Red.h"
#include"Enemy.h"

namespace
{
	static const int INTERVAL = 10;
}
Red::Red()
	:pPlayer_(nullptr),
	time_(0),
	status_(STATE::SEARCH),
	enemy_(nullptr)
{
}

Red::Red(player* pPlayer, Enemy* pEnemy)
	:pPlayer_(pPlayer),
	enemy_(pEnemy),
	status_(STATE::SEARCH),
	time_(0),
	vMove_(XMVectorSet(0,0,0,0)),
	arrive_(false)
{
	SetModelName("EnemyRed");
	AI_.Init();
}


void Red::Init(Enemy* enemy)
{
}

void Red::Update()
{
	time_++;

	if (time_ % INTERVAL == 0)
	{
		switch (status_)
		{
		case STATE::CHASE:
			ChaseMode();
			break;
		case STATE::SEARCH:
			SearchMode();
			break;
		default:
			break;
		}
	}
}

void Red::SearchMode()
{
	int x = 0;
	int z = 0;

	if (arrive_ == false)
	{
		for (int i = 0; i < 10; i++)
		{
			x = rand() % 14;
			z = rand() % 14;
			if (AI_.CanMove(XMFLOAT3(x, 0, z)))
			{
				AI_.Calc(XMFLOAT3(x, 0, z), enemy_->GetPosition());
				arrive_ = true;
				break;
			}
		}
	}

	XMFLOAT3 nextPos = AI_.GetPath();

		vMove_ = XMVectorSet(nextPos.x - enemy_->GetPosition().x, 0, nextPos.z - enemy_->GetPosition().z,0);
		vMove_ = vMove_/(float)INTERVAL;
		SetVector(vMove_);
		if (AI_.GetChaseStep() >= 1.0f)
		{
			float i = AI_.GetChaseStep();
			arrive_ = false;
		}
	
	if (CulcDistance(pPlayer_->GetPosition(), enemy_->GetPosition()) < 5)
	{
		float dis = CulcDistance(pPlayer_->GetPosition(), enemy_->GetPosition());
		status_ = STATE::CHASE;
	}
}

void Red::Move()
{
}

void Red::ChaseMode()
{
	AI_.Calc(pPlayer_->GetPosition(), enemy_->GetPosition());
	XMFLOAT3 nextPos = AI_.GetPath();

	vMove_ = XMVectorSet(nextPos.x - enemy_->GetPosition().x, 0, nextPos.z - enemy_->GetPosition().z, 0);
	vMove_ = vMove_ / (float)INTERVAL;
	SetVector(vMove_);
	if (CulcDistance(pPlayer_->GetPosition(), enemy_->GetPosition()) > 7.0f && AI_.GetChaseStep() >= 0.5f)
	{
		AI_.SetChaseFlag(false);
		arrive_ = false;
		status_ = STATE::SEARCH;
	}
}
