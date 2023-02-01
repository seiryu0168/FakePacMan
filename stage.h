#pragma once
#include"Engine/GameObject.h"
class stage : public GameObject
{
    int hModel_[2];
    int map_[15][15];
public:
    //コンストラクタ
    stage(GameObject* parent);

    //デストラクタ
    ~stage();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;
    /// <summary>
    /// マップのタイプ
    /// </summary>
    /// <param name="x">position : x</param>
    /// <param name="z">position : z</param>
    /// <returns></returns>
    int GetMap(int x,int z) { return map_[z][x]; }
};

