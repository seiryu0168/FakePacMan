#pragma once
#include"Engine/GameObject.h"
#include"AStarAI.h"
#include"Red.h"

class player;

class Enemy : public GameObject
{
private:
	enum class STATE
	{
		CHASE=0,
		SEARCH,
	};

	AStarAI AI_;
	player* pPlayer;
	int hModel_;
	int time_;
	STATE status_;
	Red* bh_;
public:
	Enemy(GameObject* parent);
	~Enemy();
	void Initialize() override;
	void Update() override;
	void Draw() override;
	float CulcDistance(XMFLOAT3 targetPos, XMFLOAT3 startPos);
	void Release() override;
	void SetCharactor(Red* b) { bh_ = b; }
	void ChaseMode();
	void SearchMode();
};

