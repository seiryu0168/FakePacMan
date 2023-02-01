#pragma once
class AStarAI
{
	AStarAI();
	~AStarAI();

	int map[15][15];

	void Init();
	void Update();
	void SetPos(int targetPos,int startPos);
	void Calc();
};

