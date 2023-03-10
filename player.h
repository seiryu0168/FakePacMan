#pragma once
#include"Engine/GameObject.h"

class stage;

class player : public GameObject
{
    int hModel_;
    float speed;
    stage* pStg_;
public:
    //コンストラクタ
   player(GameObject* parent);

    //デストラクタ
    ~player();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;

    void CharactoeControl();
};

