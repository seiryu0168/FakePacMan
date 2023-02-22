#pragma once
#include"Behavior.h"

class Enemy;
class AStarAI;

class Red : public Behavior
{
private:

	enum class STATE
	{
		CHASE = 0,
		SEARCH,
	};
	AStarAI AI_;
	bool arrive_;
	player* pPlayer_;
	int time_;
	STATE status_;
	Enemy* enemy_;
	int nextPosX;
	int nextPosZ;
	XMVECTOR vMove_;

public:
	Red();
	Red(player* pPlayer,Enemy* pEnemy);
	void Init(Enemy* enemy);
	void Update() override;
	void ChaseMode();
	void SearchMode();
	void Move();
	int GetNextPosX() { return nextPosX; }
	int GetNextPosZ() { return nextPosZ; }
};

