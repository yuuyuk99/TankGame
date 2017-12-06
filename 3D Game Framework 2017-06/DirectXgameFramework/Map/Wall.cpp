#include "Wall.h"

/*
 *@コンストラクタ
 */
Wall::Wall()
{

}

/*
 *@デストラクタ
 */
Wall::~Wall()
{

}

/*
 *@Wallオブジェクトの初期化処理
 */
void Wall::Initialize()
{
	_Wall->LoadModelFile(L"Resources/cModels/box.cmo");
}

/*
 *@Wallオブジェクトの更新処理
 */
void Wall::Update()
{
	Calc();
}

/*
 *@Wallオブジェクトの行列更新
 */
void Wall::Calc()
{
	_Wall->Calc();
}

/*
 *@Wallオブジェクトの描画処理
 */
void Wall::Draw()
{
	_Wall->Draw();
}

/*
 *@Wallオブジェクトの後処理
 */
void Wall::Finalize()
{

}
