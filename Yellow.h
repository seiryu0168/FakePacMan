#pragma once
#include"Behavior.h"

class Enemy;
class Yellow : public Behavior
{
private:
	enum class STATE
	{
		CHASE = 0,
		SEARCH,
		ESCAPE,
	};

	AStarAI AI_;
	player* pPlayer_;
	int time_;
	STATE status_;
	Enemy* enemy_;
public:
	Yellow();
	Yellow(player* pPlayer, Enemy* pEnemy);
	void Init(Enemy* enemy);
	void Update() override;
	void ChaseMode();
	void SearchMode();
	void EscapeMode();
};

