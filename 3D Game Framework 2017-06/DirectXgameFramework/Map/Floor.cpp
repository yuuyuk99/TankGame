#include "Floor.h"

/*
 *@コンストラクタ
 */
Floor::Floor()
{

}

/*
 *@Floorの初期化処理
 */
void Floor::Initialize()
{
	_Floor->LoadModelFile(L"Resources/cModels/Grass.cmo");
}

/*
 *@Floorの更新処理
 */
void Floor::Update()
{
	Calc();
}

/*
 *@Floorの行列更新
 */
void Floor::Calc()
{
	_Floor->Calc();
}

/*
 *@Floorの描画処理
 */
void Floor::Draw()
{
	_Floor->Draw();
}

/*
 *@Floorの後処理
 */
void Floor::Finalize()
{

}
