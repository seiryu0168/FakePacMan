#pragma once
#include"Engine/GameObject.h"

class stage;

class player : public GameObject
{
    int hModel_;
    float speed;
    stage* pStg_;
public:
    //�R���X�g���N�^
   player(GameObject* parent);

    //�f�X�g���N�^
    ~player();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;

    void CharactoeControl();
};
