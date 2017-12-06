#include "Move.h"
#include <math.h>
#include "Shoot.h"


using namespace std;
using namespace DirectX::SimpleMath;

shared_ptr<AIState> Move::_AIstate = nullptr;

/*
 *@コンストラクタ
 */
Move::Move()
{
	//現在の状態を初期化(なんでもない状態にする)
	_currentstateNum = 0;
}

/*
 *@Moveクラスのインスタンスを取得する
 */
shared_ptr<AIState> Move::GetInstance()
{
	//オブジェクトが存在していないなら
	if (_AIstate == nullptr)
	{
		//オブジェクトの生成
		_AIstate = make_shared<Move>();
	}
	//Moveの状態を返す
	return _AIstate;
}

/*
*@プレイヤーとの距離を求める
*/
float Move::DistancePlayer(Enemy* enemy)
{
	//プレイヤーとエネミーの距離
	float distance = 0;
	//constなので変更できるように仮の変数を作る
	Vector3 dis = enemy->GetPlayer()->GetTrans();
	//上の処理と同じような処理をする
	Vector3 disp = enemy->GetTrans();
	//プレイヤーとの距離を求める
	distance = sqrt((disp.x - dis.x) * (disp.x - dis.x) + (disp.z - dis.z) * (disp.z - dis.z));
	//プレイヤーとの距離を返す
	return distance;
}

/*
 *@タワーとの距離を求める
 */
float Move::DistanceTower(Enemy* enemy)
{
	//エネミーとタワーの距離
	float distance = 0;
	//仮の変数
	Vector3 dis = enemy->GetTower()->GetTrans();
	//上の処理と同じような処理をする
	Vector3 disp = enemy->GetTrans();
	//プレイヤーとの距離を求める
	distance = sqrt((disp.x - dis.x) * (disp.x - dis.x) + (disp.z - dis.z) * (disp.z - dis.z));
	//プレイヤーとの距離を返す
	return distance;
}


/*
 *@オブジェクトの実行
 */
inline void Move::Execute(Enemy* enemy)
{
	//撃つための距離
	float check_distanceTower= 4.0f;
	//プレイヤーに向かって打つ距離
	float check_distancePlayer = 2.0f;
	//プレイヤーとの距離を求める
	float distance_player = DistancePlayer(enemy);
	//タワーとの距離を求める
	float distance_tower = DistanceTower(enemy);
	//タワーとの距離がcheck_distanceより近かった場合
	if (distance_tower <= check_distanceTower)
	{
		//ここでどちらを撃つかを渡す予定
		//敵の状態を球を撃つ状態に変更
		auto state = Shoot::GetInstance();
		assert(enemy);
		assert(state);
		enemy->ChangeState(state);
		return;
	}
	//プレイヤーとの距離がcheck_distanceより近かった場合
	if (distance_tower <= check_distancePlayer)
	{
		//ここでどちらを撃つかを渡す予定
		//敵の状態を球を撃つ状態に変更
		auto state = Shoot::GetInstance();
		assert(enemy);
		assert(state);
		enemy->ChangeState(state);
		return;
	}
	//現在の座標回転角を取得
	Vector3 trans = enemy->GetTrans();
	//回転軸Yを受け取る
	float rot_y = enemy->GetRot().y;
	//エネミーが所持しているタワーの位置を受け取る
	Vector3 pPos = enemy->GetTower()->GetTrans();
	//エネミーの場所を受け取る
	Vector3 ePos = enemy->GetTrans();
	//自機と敵の場所の差を計算する
	Vector3 dPos = pPos - ePos;
	//差を正規化をする
	dPos.Normalize();
	//移動ベクトル
	Vector3 move(dPos / 20.0f);
	//回転
	Matrix rotm = Matrix::CreateRotationY(rot_y);
	//移動ベクトルを回転する
	move = Vector3::TransformNormal(move, rotm);
	//移動ベクトルを足す
	trans += move;
	//移動を行う
	enemy->SetTrans(trans);
}

void Move::Pathfinding(std::shared_ptr<Enemy> enemy)
{
	//ゴール地点
	Vector3 goal = enemy->GetPlayer()->GetTrans();
	//敵の移動
	Vector3 vec = goal - _Pos;
	//正規化を行う
	vec.Normalize();
	
	Vector3 nol = vec;
}


/*
 *@Moveオブジェクトを破棄する
 */
void Move::Finalize()
{

}
