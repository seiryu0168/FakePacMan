#include "Blue.h"

namespace
{
	static const int INTERVAL = 10;
}
Blue::Blue()
	:pPlayer_(nullptr),
	time_(0),
	status_(STATE::SEARCH),
	enemy_(nullptr)
{
}

Blue::Blue(player* pPlayer, Enemy* pEnemy)
	:pPlayer_(pPlayer),
	enemy_(pEnemy),
	status_(STATE::SEARCH),
	time_(0),
	arrive_(false)
{
	AI_.Init();
	ChangePatrolRoute();
	srand((unsigned int)time_t(NULL));
	SetModelName("EnemyBlue");
}

void Blue::Update()
{
	time_++;
	if (time_ % 10 == 0)
	{
		PatrolMode();
	}
}

void Blue::ChangePatrolRoute()
{
	for (int i = 0; i < 4; i++)
	{
		//巡回ポイントの設定
		point[i].x = rand() % 14;
		point[i].z = rand() % 14;

		if (AI_.CanMove(XMFLOAT3(point[i].x, 0, point[i].z)) == false)
		{
			i--;
		}
	}
}

void Blue::PatrolMode()
{
	int targetPoint = nowPoint % 4;
	AI_.Calc(XMFLOAT3(point[targetPoint].x,0, point[targetPoint].z), enemy_->GetPosition());
	
	XMFLOAT3 nextPos = AI_.GetPath();
	XMVECTOR vMove;
	vMove = XMVectorSet(nextPos.x - enemy_->GetPosition().x, 0, nextPos.z - enemy_->GetPosition().z, 0);
	vMove = vMove / (float)INTERVAL;
	SetVector(vMove);
	//目的地に着いたら次の目的地に向かう
	if (AI_.GetChaseStep()>=1.0f)
	{
		AI_.SetChaseFlag(false);
		nowPoint++;
		if (nowPoint == 12)
		{
			nowPoint = 0;
			ChangePatrolRoute();
		}
	}
}
