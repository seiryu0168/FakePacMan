#include "Blue.h"

Blue::Blue()
	:pPlayer_(nullptr),
	time_(0),
	status_(STATE::SEARCH),
	enemy_(nullptr)
{
}

Blue::Blue(player* pPlayer, Enemy* pEnemy)
	:pPlayer_(pPlayer),
	enemy_(pEnemy),
	status_(STATE::SEARCH),
	time_(0)
{
	AI_.Init();
	ChangePatrolRoute();
	srand((unsigned int)time_t(NULL));
}

void Blue::Update()
{
	time_++;
	if (time_ % 10 == 0)
	{
		PatrolMode();
	}
}

void Blue::ChangePatrolRoute()
{
	for (int i = 0; i < 4; i++)
	{
		//����|�C���g�̐ݒ�
		point[i].x = rand() % 14;
		point[i].z = rand() % 14;

		if (AI_.CanMove(XMFLOAT3(point[i].x, 0, point[i].z)) == false)
		{
			i--;
		}
	}
}

void Blue::PatrolMode()
{
	int targetPoint = nowPoint % 4;
	AI_.Calc(XMFLOAT3(point[targetPoint].x,0, point[targetPoint].z), enemy_->GetPosition());
	
	enemy_->SetPosition(AI_.GetPath());
	
	//�ړI�n�ɒ������玟�̖ړI�n�Ɍ�����
	if (enemy_->GetPosition().x == point[targetPoint].x && enemy_->GetPosition().z == point[targetPoint].z)
	{
		AI_.SetChaseFlag(false);
		nowPoint++;
		if (nowPoint == 12)
		{
			nowPoint = 0;
			ChangePatrolRoute();
		}
	}
}
