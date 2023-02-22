#include "Red.h"
#include"Enemy.h"

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
	time_(0)
{
	AI_.Init();
}


void Red::Init(Enemy* enemy)
{
}

void Red::Update()
{
	time_++;
	if (time_ % 10 == 0)
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

	if (moveFlag)
	{
		enemy_->SetPosition(AI_.GetPath());
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
	enemy_->SetPosition(AI_.GetPath());
	if (CulcDistance(pPlayer_->GetPosition(), enemy_->GetPosition()) > 5.0f && AI_.GetChaseStap() >= 0.5f)
	{
		AI_.SetChaseFlag(false);
		status_ = STATE::SEARCH;
	}
}
