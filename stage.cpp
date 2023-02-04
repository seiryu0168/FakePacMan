#include "stage.h"
#include"Engine/Model.h"
#include"Engine/CsvReader.h"

//�R���X�g���N�^
stage::stage(GameObject* parent)
    :GameObject(parent, "stage")
{
}

//�f�X�g���N�^
stage::~stage()
{
}

//������
void stage::Initialize()
{
    
    CsvReader csv;
    csv.Load("map.csv");
    for (int z = 0; z < 15; z++)
    {
        for (int x = 0; x < 15; x++)
        {
            map_[z][x] = csv.GetValue(x, z);
        }
    }
    hModel_[0] = Model::Load("floor.fbx");
    assert(hModel_[0] >= 0);
    hModel_[1] = Model::Load("wall.fbx");
    assert(hModel_[1] >= 0);
    
}

//�X�V
void stage::Update()
{
}

//�`��
void stage::Draw()
{
    for (int z = 0; z < 15; z++)
    {
        for (int x = 0; x < 15; x++)
        {
            int type = map_[z][x];
            transform_.position_.z = z;
            transform_.position_.x = x;
            Model::SetTransform(hModel_[type], transform_);
            Model::Draw(hModel_[type]);
        }
    }
}

//�J��
void stage::Release()
{
}