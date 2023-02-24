#pragma once
#include"Behavior.h"
class AStarAI;
class Enemy;

class Gray : public Behavior
{
	enum class STATE
	{
		CHASE = 0,
		SLEEP,
	};
	AStarAI AI_;
	bool arrive_;
	player* pPlayer_;
	int time_;
	int chaseStart_;
	int sleepTime_;
	STATE status_;
	Enemy* enemy_;
	int nextPosX;
	int nextPosZ;
	XMVECTOR vMove_;

public:
	Gray();
	Gray(player* pPlayer, Enemy* pEnemy);
	void Init(Enemy* enemy);
	void Update() override;
	void ChaseMode();
	void SleepMode();
	bool CalcLimit();
	int GetNextPosX() { return nextPosX; }
	int GetNextPosZ() { return nextPosZ; }
};

