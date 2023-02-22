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
	vMove_(XMVectorSet(0,0,0,0))
{
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
	if()
	{
	
	}
}

void Red::SearchMode()
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
				AI_.Calc(XMFLOAT3(x, 0, z), enemy_->GetPosition());
				moveFlag = true;
				break;
			}
		}
	}

	if (arrive_)
	{
		nextPosX = AI_.GetPath().x;
		nextPosZ = AI_.GetPath().z;

		vMove_ = XMVectorSet(nextPosX - enemy_->GetPosition().x, 0, nextPosZ - enemy_->GetPosition().z,0);
		vMove_ = XMVector3Normalize(vMove_);

		if (AI_.GetChaseStap() >= 1.0f)
		{
			float i = AI_.GetChaseStap();
			moveFlag = false;
		}
	}
	if (CulcDistance(pPlayer_->GetPosition(), enemy_->GetPosition()) < 5)
	{
		float dis = CulcDistance(pPlayer_->GetPosition(), enemy_->GetPosition());
		status_ = STATE::CHASE;
	}
}

void Red::ChaseMode()
{
	AI_.Calc(pPlayer_->GetPosition(), enemy_->GetPosition());
	nextPosX = AI_.GetPath().x;
	nextPosZ = AI_.GetPath().z;
	if (CulcDistance(pPlayer_->GetPosition(), enemy_->GetPosition()) > 5.0f && AI_.GetChaseStap() >= 0.5f)
	{
		AI_.SetChaseFlag(false);
		status_ = STATE::SEARCH;
	}
}
