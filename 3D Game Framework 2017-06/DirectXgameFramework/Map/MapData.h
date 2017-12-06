#pragma once

#include <memory>
#include <d3d11.h>
#include <SimpleMath.h>

class MapData
{
public:
	enum Land
	{
		FLOOR,
		WALL,

		NUM_LAND
	};
	MapData();
	MapData(DirectX::SimpleMath::Vector3& position);
	//MapDataオブジェクトを初期化する
	virtual void Initialize();
	//MapDataオブジェクトを更新する
	virtual void Update();
	//MapDataオブジェクトの行列更新
	virtual void Calc();
	//MapDateオブジェクトを描画する
	virtual void Draw();
	//MapDataの後処理を行う
	virtual void Finalize();
protected:
	//位置
	DirectX::SimpleMath::Vector3& _Pos;
	//子オブジェクトへのポインタ
	std::shared_ptr<MapData> _Child;
	//Rootオブジェクトへのポインタ
	std::shared_ptr<MapData> _Root;
};