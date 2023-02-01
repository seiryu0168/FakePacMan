#pragma once
#include"Engine/GameObject.h"
class stage : public GameObject
{
    int hModel_[2];
    int map_[15][15];
public:
    //�R���X�g���N�^
    stage(GameObject* parent);

    //�f�X�g���N�^
    ~stage();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;

    int GetMap(int x,int z) { return map_[z][x]; }
};

