#pragma once

#include <memory>
#include "MapData.h"
#include "../Base/ObjectBase.h"

class Floor : public MapData
{
public:
	//コンストラクタ
	Floor();
	//Floorオブジェクトを初期化する
	void Initialize() override;
	//Floorオブジェクトを更新
	void Update() override;
	//Floorオブジェクトの行列更新
	void Calc() override;
	//Floorオブジェクトを描画
	void Draw() override;
	//Floorオブジェクトの後処理を行う
	void Finalize() override;
private:
	std::shared_ptr<ObjectBase> _Floor;
};