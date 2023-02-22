#pragma once
#include"Behavior.h"
#include"Enemy.h"

class Red;
class Blue : public Behavior
{
private:

	enum class STATE
	{
		CHASE = 0,
		SEARCH,
	};

	struct patrolPoint
	{
		int x;
		int z;
	};
	AStarAI AI_;
	bool arrive_;
	player* pPlayer_;
	int time_;
	int nowPoint;
	STATE status_;
	Enemy* enemy_;
	patrolPoint point[4];

public:
	Blue();
	Blue(player* pPlayer, Enemy* pEnemy);
	void Update() override;
	void ChangePatrolRoute();
	void PatrolMode();
};

