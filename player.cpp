#include "player.h"
#include"Engine/Model.h"
#include"Engine/Input.h"
#include"stage.h"

//コンストラクタ
player::player(GameObject* parent)
    :GameObject(parent, "player"),hModel_(-1),speed(0.1)
{
}

//デストラクタ
player::~player()
{
}

//初期化
void player::Initialize()
{
    pStg_ = (stage*)FindObject("stage");
    hModel_ = Model::Load("pacman.fbx");
    assert(hModel_ >= 0);
    transform_.position_.x = 1.5;
    transform_.position_.z = 1.5;
}

//更新
void player::Update()
{
    //移動前の位置ベクトル
    XMVECTOR prevPosition = XMLoadFloat3(&transform_.position_);
    CharactoeControl();

    //現在の位置ベクトル
    XMVECTOR nowPosition = XMLoadFloat3(&transform_.position_);
    //今回のベクトル
    XMVECTOR vMove = nowPosition - prevPosition;

    //角度求めるために長さを1にする・・・正規化
    vMove = XMVector3Normalize(vMove);
    //基準となる奥行きのベクトル
    XMVECTOR front = { 0,0,1,0 };
    //frontとvMoveの内積を求める
    XMVECTOR vecDot = XMVector3Dot(front, vMove);
    float dot = XMVectorGetX(vecDot);
    //向いてる角度を求める(ラジアン)
    float angle = acos(dot);
    //角度分回転させる
    transform_.rotate_.y = (180 / 3.14f) * angle;

}

//描画
void player::Draw()
{

    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//開放
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
