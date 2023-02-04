#pragma once
#include"Engine/GameObject.h"
#include"AStarAI.h"

class player;

class Enemy : public GameObject
{
private:
	AStarAI AI_;
	player* pPlayer;
	int hModel_;
	int time_;
public:
	Enemy(GameObject* parent);
	~Enemy();
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
};

