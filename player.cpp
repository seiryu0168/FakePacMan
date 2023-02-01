#include "player.h"
#include"Engine/Model.h"
#include"Engine/Input.h"
#include"stage.h"

//�R���X�g���N�^
player::player(GameObject* parent)
    :GameObject(parent, "player"),hModel_(-1),speed(0.1)
{
}

//�f�X�g���N�^
player::~player()
{
}

//������
void player::Initialize()
{
    pStg_ = (stage*)FindObject("stage");
    hModel_ = Model::Load("pacman.fbx");
    assert(hModel_ >= 0);
    transform_.position_.x = 1.5;
    transform_.position_.z = 1.5;
}

//�X�V
void player::Update()
{
    //�ړ��O�̈ʒu�x�N�g��
    XMVECTOR prevPosition = XMLoadFloat3(&transform_.position_);
    CharactoeControl();

    //���݂̈ʒu�x�N�g��
    XMVECTOR nowPosition = XMLoadFloat3(&transform_.position_);
    //����̃x�N�g��
    XMVECTOR vMove = nowPosition - prevPosition;

    //�p�x���߂邽�߂ɒ�����1�ɂ���E�E�E���K��
    vMove = XMVector3Normalize(vMove);
    //��ƂȂ鉜�s���̃x�N�g��
    XMVECTOR front = { 0,0,1,0 };
    //front��vMove�̓��ς����߂�
    XMVECTOR vecDot = XMVector3Dot(front, vMove);
    float dot = XMVectorGetX(vecDot);
    //�����Ă�p�x�����߂�(���W�A��)
    float angle = acos(dot);
    //�p�x����]������
    transform_.rotate_.y = (180 / 3.14f) * angle;

}

//�`��
void player::Draw()
{

    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//�J��
void player::Release()
{
}

void player::CharactoeControl()
{

    if (pStg_->GetMap((int)(transform_.position_.x), (int)(transform_.position_.z + 0.4f)) == 0)
    {
        if (Input::IsKey(DIK_W))
        {
            transform_.position_.z += speed;
        }
    }

    if (pStg_->GetMap((int)(transform_.position_.x), (int)(transform_.position_.z - 0.4f)) == 0)
    {
        if (Input::IsKey(DIK_S))
        {
            transform_.position_.z -= speed;
        }
    }
    if (pStg_->GetMap((int)(transform_.position_.x-0.4f), (int)(transform_.position_.z)) == 0)
    {
        if (Input::IsKey(DIK_A))
        {
            transform_.position_.x -= speed;
        }
    }

    if (pStg_->GetMap((int)(transform_.position_.x+0.4f), (int)(transform_.position_.z)) == 0)
    {
        if (Input::IsKey(DIK_D))
        {
            transform_.position_.x += speed;
        }
    }
        
}
