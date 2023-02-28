#include "Yellow.h"
#include"Enemy.h"
namespace
{
	static const int INTERVAL = 10;
}
Yellow::Yellow()
	:pPlayer_(nullptr),
	time_(0),
	status_(STATE::SEARCH),
	enemy_(nullptr)
{
}

Yellow::Yellow(player* pPlayer, Enemy* pEnemy)
	:pPlayer_(pPlayer),
	enemy_(pEnemy),
	arrive_(false)
{
	SetModelName("EnemyYellow");
	AI_.Init();
}


void Yellow::Init(Enemy* enemy)
{
}

void Yellow::Update()
{
	time_++;
	if (time_ % 10 == 0)
	{
		switch (status_)
		{
		case STATE::CHASE:
			ChaseMode();
			break;
		case STATE::SEARCH:
			SearchMode();
			break;
		case STATE::ESCAPE:
			EscapeMode();
			break;
		default:
			break;
		}
	}
}

void Yellow::ChaseMode()
{
	//�o�H���v�Z
	AI_.Calc(pPlayer_->GetPosition(), enemy_->GetPosition());
	XMFLOAT3 nextPos = AI_.GetPath();

	XMVECTOR vMove;
	vMove = XMVectorSet(nextPos.x - enemy_->GetPosition().x, 0, nextPos.z - enemy_->GetPosition().z, 0);
	vMove = vMove / (float)INTERVAL;
	SetVector(vMove);
	if (CulcDistance(pPlayer_->GetPosition(), enemy_->GetPosition()) < 4.0f && AI_.GetChaseStep() >= 0.5f)
	{
		AI_.SetChaseFlag(false);
		arrive_ = true;
		status_ = STATE::ESCAPE;
	}
}

void Yellow::SearchMode()
{
	int x = 0;
	int z = 0;
	bool moveFlag = false;

	//�t���O�������Ă���
	if (arrive_)
	{
		for (int i = 0; i < 10; i++)
		{
			x = rand() % 14;
			z = rand() % 14;
			if (AI_.CanMove(XMFLOAT3(x, 0, z)))
			{
				AI_.Calc(XMFLOAT3(x, 0, z), enemy_->GetPosition());
				arrive_ = false;
				break;
			}
		}
	}

	if (arrive_==false)
	{
		XMFLOAT3 nextPos = AI_.GetPath();

		XMVECTOR vMove;
		vMove = XMVectorSet(nextPos.x - enemy_->GetPosition().x, 0, nextPos.z - enemy_->GetPosition().z, 0);
		vMove = vMove / (float)INTERVAL;
		SetVector(vMove);
		if (AI_.GetChaseStep() >= 1.0f)
		{
			float i = AI_.GetChaseStep();
			arrive_ = true;
		}
	}

	//�v���C���[�Ƃ̋�����6�ȉ���������ǂ�������
	if (CulcDistance(pPlayer_->GetPosition(), enemy_->GetPosition()) < 6)
	{
		float dis = CulcDistance(pPlayer_->GetPosition(), enemy_->GetPosition());
		arrive_ = true;
		status_ = STATE::CHASE;
	}
}

void Yellow::EscapeMode()
{
	int x = 0;
	int z = 0;
	
	if (arrive_)
	{

		//���Ɉړ�����Ƃ����T��
		for (int i = 0; i < 10; i++)
		{
			x = rand() % 14;
			z = rand() % 14;

			//�ړ��ł��āA�v���C���[�Ƃ̋�����6�ȏ�
			if (AI_.CanMove(XMFLOAT3(x, 0, z)) && CulcDistance(XMFLOAT3(x, 0, z), pPlayer_->GetPosition()) >= 6)
			{
				AI_.Calc(XMFLOAT3(x, 0, z), enemy_->GetPosition());
				arrive_ = false;
				break;
			}
		}
	}

	//������Ȃ瓮���āA�ړI�n�ɒ�������t���O���~�낷
	if (arrive_==false)
	{
		XMFLOAT3 nextPos = AI_.GetPath();

		XMVECTOR vMove;
		vMove = XMVectorSet(nextPos.x - enemy_->GetPosition().x, 0, nextPos.z - enemy_->GetPosition().z, 0);
		vMove = vMove / (float)INTERVAL;
		SetVector(vMove);

		if (AI_.GetChaseStep() >= 1.0f)
		{
			float i = AI_.GetChaseStep();
			arrive_ = true;
		}
	}

	//������8�ȏゾ������v���C���[��ǂ�������
	if (CulcDistance(pPlayer_->GetPosition(), enemy_->GetPosition()) > 8)
	{
		float dis = CulcDistance(pPlayer_->GetPosition(), enemy_->GetPosition());
		arrive_=true;
		status_ = STATE::SEARCH;
	}
}
