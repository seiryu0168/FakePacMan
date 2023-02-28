#include "Gray.h"
#include"Enemy.h"
#include"AStarAI.h"
namespace
{
	static const int INTERVAL = 10;
	static const int CHASE_TIME_LIMIT = 240;
	static const int SLEEP_TIME_LIMIT = 240;
}
Gray::Gray()
	:pPlayer_(nullptr),
	time_(0),
	status_(STATE::SLEEP),
	enemy_(nullptr)
{
}

Gray::Gray(player* pPlayer, Enemy* pEnemy)
	:pPlayer_(pPlayer),
	enemy_(pEnemy),
	status_(STATE::SLEEP),
	time_(0),
	vMove_(XMVectorSet(0, 0, 0, 0)),
	arrive_(false)
{
	SetModelName("EnemyGray");
	AI_.Init();
}


void Gray::Init(Enemy* enemy)
{
}

void Gray::Update()
{
	time_++;

	if (time_ % INTERVAL == 0)
	{
		switch (status_)
		{
		case STATE::CHASE:
			ChaseMode();
			break;
		case STATE::SLEEP:
			SleepMode();
			break;
		default:
			break;
		}
	}
}

void Gray::SleepMode()
{
	//Q‚Ä‚é‚Ì‚ÅƒvƒŒƒCƒ„[‚Æ‚Ì‹——£‚¾‚¯‘ª‚é
	if (CulcDistance(pPlayer_->GetPosition(), enemy_->GetPosition()) < 5&&CalcLimit())
	{
		chaseStart_ = time_;
		float dis = CulcDistance(pPlayer_->GetPosition(), enemy_->GetPosition());
		status_ = STATE::CHASE;
	}
}

bool Gray::CalcLimit()
{
	switch (status_)
	{
	case STATE::CHASE:
		if (time_ - chaseStart_ >= CHASE_TIME_LIMIT)
		{
			return true;
		}
		break;
	case STATE::SLEEP:
		if (time_ - sleepTime_ >= SLEEP_TIME_LIMIT)
		{
			return true;
		}
		break;
	default:
		return false;
		break;
	}
	return false;
}

void Gray::ChaseMode()
{
	
	AI_.Calc(pPlayer_->GetPosition(), enemy_->GetPosition());
	XMFLOAT3 nextPos = AI_.GetPath();

	vMove_ = XMVectorSet(nextPos.x - enemy_->GetPosition().x, 0, nextPos.z - enemy_->GetPosition().z, 0);
	vMove_ = vMove_ / (float)INTERVAL;
	SetVector(vMove_);
	if (CalcLimit())
	{
		sleepTime_ = time_;
		AI_.SetChaseFlag(false);
		arrive_ = false;
		status_ = STATE::SLEEP;
		vMove_ = XMVectorZero();
		SetVector(vMove_);
	}
}