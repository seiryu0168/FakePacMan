#pragma once
#include"Node.h"
#include"Engine/Direct3D.h"
#include"Engine/CsvReader.h"
#include<list>
class AStarAI
{
private:
	int map[15][15]; 
	Node* nodeMap_[15][15];
	std::list<Node*> openNodeList_;
	std::list<Node*> closedNodeList_;
	CsvReader csv;
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
	void SetTargetPos(XMFLOAT3 targetPos);
	void Calc(XMFLOAT3 targetPos, XMFLOAT3 startPos);
	void Open(Node* pN);
	void ResetNode();
};

