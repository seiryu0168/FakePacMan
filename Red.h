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
	player* pPlayer_;
	int time_;
	STATE status_;
	Enemy* enemy_;

public:
	Red();
	Red(player* pPlayer,Enemy* pEnemy);
	void Init(Enemy* enemy);
	void Update() override;
	void ChaseMode() override;
	void SearchMode() override;
};

