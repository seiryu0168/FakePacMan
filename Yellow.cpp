#include "Yellow.h"
#include"Enemy.h"

Yellow::Yellow()
	:pPlayer_(nullptr),
	time_(0),
	status_(STATE::SEARCH),
	enemy_(nullptr)
{
}

Yellow::Yellow(player* pPlayer, Enemy* pEnemy)
	:pPlayer_(pPlayer),
	enemy_(pEnemy)
{
	AI_.Init();
}


void Yellow::Init(Enemy* enemy)
{
}

void Yellow::Update()
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
		case STATE::ESCAPE:
			EscapeMode();
			break;
		default:
			break;
		}
	}
}

void Yellow::ChaseMode()
{
	//経路を計算
	AI_.Calc(pPlayer_->GetPosition(), enemy_->GetPosition());
	enemy_->SetPosition(AI_.GetPath());
	if (CulcDistance(pPlayer_->GetPosition(), enemy_->GetPosition()) < 4.0f && AI_.GetChaseStap() >= 0.5f)
	{
		AI_.SetChaseFlag(false);
		status_ = STATE::ESCAPE;
	}
}

void Yellow::SearchMode()
{
	int x = 0;
	int z = 0;
	bool moveFlag = false;

	//フラグが立ってたら
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

	//プレイヤーとの距離が6以下だったら追いかける
	if (CulcDistance(pPlayer_->GetPosition(), enemy_->GetPosition()) < 6)
	{
		float dis = CulcDistance(pPlayer_->GetPosition(), enemy_->GetPosition());
		status_ = STATE::CHASE;
	}
}

void Yellow::EscapeMode()
{
	int x = 0;
	int z = 0;
	bool moveFlag = false;
	
	if (moveFlag == false)
	{

		//次に移動するところを探す
		for (int i = 0; i < 10; i++)
		{
			x = rand() % 14;
			z = rand() % 14;

			//移動できて、プレイヤーとの距離が6以上
			if (AI_.CanMove(XMFLOAT3(x, 0, z)) && CulcDistance(XMFLOAT3(x, 0, z), pPlayer_->GetPosition()) >= 6)
			{
				AI_.Calc(XMFLOAT3(x, 0, z), enemy_->GetPosition());
				moveFlag = true;
				break;
			}
		}
	}

	//動けるならうごいて、目的地に着いたらフラグを降ろす
	if (moveFlag)
	{
		enemy_->SetPosition(AI_.GetPath());
		if (AI_.GetChaseStap() >= 1.0f)
		{
			float i = AI_.GetChaseStap();
			moveFlag = false;
		}
	}

	//距離が8以上だったらプレイヤーを追いかける
	if (CulcDistance(pPlayer_->GetPosition(), enemy_->GetPosition()) > 8)
	{
		float dis = CulcDistance(pPlayer_->GetPosition(), enemy_->GetPosition());
		status_ = STATE::SEARCH;
	}
}
