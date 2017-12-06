#include "Shoot.h"
#include <math.h>
#include "Move.h"

//現在の状態はnullptrにする
std::shared_ptr<AIState> Shoot::_AIstate = nullptr;

/*
 *@名前空間
 */
using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

/*
 *@コンストラクタ
 */
Shoot::Shoot() : _delay(0)
{
	
}

/*
 *@Shootクラスのインスタンスを取得する
 */
shared_ptr<AIState> Shoot::GetInstance()
{
	//オブジェクトが存在していないなら
	if (_AIstate == nullptr)
	{
		//オブジェクトの生成
		_AIstate = make_shared<Shoot>();
	}
	//Shootの状態を返す
	return _AIstate;
}

/*
 *@オブジェクトを実行する
 */
inline void Shoot::Execute(Enemy* enemy)
{

	_delay++;
	//連続で撃てないようにする
	if (_delay > 60.0f)
	{
		//ディレイをリセットする
		_delay = 0.0f;
		//敵の行動を移動に戻す
		enemy->ChangeState(Move::GetInstance());
	}
	//プレイヤーの座標
	//Vector3 ptrans = enemy->GetPlayer()->GetTrans();
	////プレイヤーの角度に向かせる
	//float angle =  atan2(ptrans.z - enemy->GetTrans().z, ptrans.x - enemy->GetTrans().x);
	//enemy->SetRot(Vector3(0.0f, -angle, 0.0f));

		//TODO:撃つ処理を追加予定
	enemy->SetShootBullet(true);
}

/*
 *@Shootオブジェクトを破棄する
 */
void Shoot::Finalize()
{

}
