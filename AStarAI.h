#pragma once
#include"Node.h"
#include"Engine/Direct3D.h"
#include"Engine/CsvReader.h"
#include<list>
#include<vector>
class AStarAI
{
private:
	int map[15][15];
	Node* nodeMap_[15][15];
	std::list<Node*> openNodeList_;
	std::list<Node*> closedNodeList_;
	std::vector<XMINT2> path_;
	CsvReader csv;
	XMFLOAT3 targetPos_;
	XMFLOAT3 startPos_;
	int stageWidth_;
	int stageHeight_;
	int zOffset_;
	int pathCount_;
	bool chaseFlag_;

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
	void SetPos(XMFLOAT3 targetPos,XMFLOAT3 startPos);
	void Calc(XMFLOAT3 targetPos, XMFLOAT3 startPos);
	void Open(Node* pN);
	XMFLOAT3 GetPath();
	void CreatePath();
	void SetChaseFlag(bool fChase) { chaseFlag_ = fChase; }
	float GetChaseStep() { return (float)(path_.size()-pathCount_) / (float)path_.size(); }
	bool CanMove(XMFLOAT3 pos);
	void ResetNode();
};

