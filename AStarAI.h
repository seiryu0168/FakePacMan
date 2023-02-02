#pragma once
#include"Node.h"
#include"Engine/Direct3D.h"
#include<list>
class AStarAI
{
private:
	int map[15][15]; 
	std::list<Node*> openNodeList_;
	std::list<Node*> closedNodeList_;

	XMFLOAT3 targetPos_;
	struct dir
	{
		int dirX;
		int dirZ;
	};
	dir d[4] = { {1,0},{0,1},{-1,0},{0,-1} };
public:
	AStarAI();
	~AStarAI();


	void Init();
	void Update();
	void SetPos(XMFLOAT3 targetPos,XMFLOAT3 startPos);
	void Calc(XMFLOAT3 targetPos, XMFLOAT3 startPos);
	void Open(Node* pN);
};

