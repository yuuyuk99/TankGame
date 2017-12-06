#include "GameScene.h"
#include "../SceneManager.h"
#include "../../Charcter/Player/Player.h"
#include "../../Charcter/Enemy/Enemy.h"
#include <Effects.h>
#include "../../Camera/Camera.h"
#include "../../Collision/CollisionNode.h"
#include "../../Tower/Tower.h"
#include "../../Stage/Stage.h"
#include "../../BackScreen/BackScreen.h"


using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace std;

/*
 *@コンストラクタ
 */
GameScene::GameScene(shared_ptr<SceneManager> scene) : SceneBase(scene)
{
	//プレイヤーオブジェクトを生成する
	this->_Player = make_shared<Player>();
	//敵オブジェクトを生成する
	this->_Enemy = make_shared<Enemy>();
	//カメラを持つ
	this->_Camera = make_shared<Camera>();
	//ステージ
	this->_stage = make_shared<Stage>();
	//背景
	this->_backScreen = make_shared<BackScreen>();
}
	
/*
 *@デストラクタ
 */
GameScene::~GameScene()
{

}

/*
 *@GameSceneの初期化処理を行う
 */
void GameScene::Initialize()
{
	//プレイヤーの初期化
	this->_Player->Initialize();

	//敵の初期化
	this->_Enemy->Initialize();
	//敵にプレイヤーの情報を持たせる
	this->_Enemy->SetPlayer(this->_Player);
	//タワーの初期設定
	//0 = PlayerTower, 1 = EnemyTower
	for (int i = 0; i < TOWER_NUM; i++)
	{
		//タワーオブジェクトを生成する
		this->_Tower[i] = make_shared<Tower>();
		//タワーの初期化
		this->_Tower[i]->Initialize();
	}
	//タワーの初期位置の設定
	_Tower[0]->SetTrans(Vector3(7.5f, 0.0f, 5.0f));
	_Tower[1]->SetTrans(Vector3(7.5f, 0.0f, 25.0f));
	//プレイヤーの塔に向かわせるためにプレイヤー側のタワーの情報を受け渡す
	this->_Enemy->SetTower(this->_Tower[0]);

	//ステージの初期化
	this->_stage->Initialize();
	//天球の初期化
	this->_backScreen->Initialize();
}

/*
 *@GameSceneの更新処理を行う
 */
void GameScene::Update()
{
	Vector3 old_trans = this->_Player->GetTrans();

	//プレイヤーの更新
	this->_Player->Update();
	//エネミーの更新
	this->_Enemy->Update();
	/*
	 *カメラの設定
	 */
	{
		//カメラ距離
		const float CAMERA_DISTANCE = -5.0f;
		//視点、参照点
		Vector3 eyepos, refpos;
		//ターゲットの座標は自機の座標に追従
		refpos = this->_Player->GetTrans() + Vector3(0.0f, 2.0f, 0.0f);
		//ターゲットの座標からカメラ座標への差分
		Vector3 cameraV(0.0f, 0.0f, CAMERA_DISTANCE);
		//カメラの視線方向の逆方向回転
		Matrix rotmat = Matrix::CreateRotationY(_Player->GetRot().y);
		cameraV = Vector3::TransformNormal(cameraV, rotmat);
		//カメラ座標を計算
		eyepos = refpos + cameraV;
		//カメラに情報をセット
		_Camera->SetEyepos(eyepos);
		_Camera->SetRefpos(refpos);

	}

	//カメラの更新
	this->_Camera->Update();

	//タワーの更新
	for (int i = 0; i < TOWER_NUM; i++)
	{
		//タワーの更新
		this->_Tower[i]->Update();
	}

	//ステージの更新
	this->_stage->Update();

	//当たり判定
	if (CollisionSphere2Sphere(this->_Player->GetCollisionNodeBody(), this->_Enemy->GetCollisionnodeBody()))
	{
		//テスト用
		int i = 0;
	}

	for (int i = 0; i < TOWER_NUM; i++)
	{
		//デバッグ用
		//タワーとの当たり判定
		//if (CollisionSphere2Capusle(this->_Player->GetCollisionNodeBody(), this->_Tower[i]->GetCollsionNode()))
		//{
		//	//タワーの耐久度を減らす
		//	_Tower[i]->SetHealth(_Tower[i]->GetHealth() - 1);
		//}

		//タワーとの当たり判定
		if (CollisionSphere2Capusle(this->_Player->GetCollisionNodeBullet(), this->_Tower[i]->GetCollsionNode()))
		{
			//タワーの耐久度を減らす
			this->_Tower[i]->SetHealth(_Tower[i]->GetHealth() - 1);
		}
	}

	for (int i = 0; i < MAP_SIZE_Y; i++)
	{
		for (int j = 0; j < MAP_SIZE_X; j++)
		{
			//プレイヤーのBodyとステージの壁との衝突判定
			if (CollisionSphere2Sphere(this->_Player->GetCollisionNodeBody(), this->_stage->GetCollisionNodeWall(i, j)))
			{
				//プレイヤーがこれ以上進めないようにする
				this->_Player->SetTrans(old_trans);
			}
		}
	}
	
	
	//どちらかのタワーの耐久度がなくなったら
	for (int i = 0; i < TOWER_NUM; i++)
	{
		//どちらかのタワーの耐久度が０になったとき
		if (this->_Tower[i]->GetHealth() <= 0)
		{
			//リザルトシーンへ移行する
			m_SceneChanger._Get()->ChangeScene(SCENE_RESULT);
		}
	}

	//背景の更新
	this->_backScreen->Update();
}

/*
 *@GameSceneの描画処理を行う
 */
void GameScene::Draw()
{
	//ステージの描画
	this->_stage->Draw(_Camera);
	//プレイヤーの描画を行う
	this->_Player->Draw(_Camera);
	//エネミーの描画を行う
	this->_Enemy->Draw(_Camera);
	//タワーの描画
	for (int i = 0; i < TOWER_NUM; i++)
	{
		//タワーの描画を行う
		this->_Tower[i]->Draw(_Camera);
	}
	//背景の描画
	this->_backScreen->Draw(_Camera);
}

/*
 *@GameSceneの後処理を行う
 */
void GameScene::Finalize()
{
	//プレイヤーの終了処理
	this->_Player->Finalize();
	//敵の終了処理
	this->_Enemy->Finalize();
	//タワーの終了処理
	for (int i = 0; i < TOWER_NUM; i++)
	{
		//タワーの終了処理
		this->_Tower[i]->Finalize();
	}
	
}

/*
 *@球と球の当たり判定を行う
 *@戻り値 true　衝突している
 *             false   衝突していない
 */
bool GameScene::CollisionSphere2Sphere(const Sphere& obj1, const Sphere& obj2)
{
	//衝突点の座標を入れる変数
	Vector3 inter;
	//球と球の衝突判定
	if (CheckSphere2Sphere(obj1, obj2, &inter))
	{
		return true;
	}
	return false;
}

/*
 *@カプセルと球の当たり判定を行う
 *@戻り値 true　衝突している
 *              false  衝突していない
 */
bool GameScene::CollisionSphere2Capusle(const Sphere& obj1, const Capsule& obj2)
{
	//衝突点の座標を入れる変数
	Vector3 inter;
	//カプセルと球の衝突判定
	if (CheckSphere2Capsule(obj1, obj2, &inter))
	{
		return true;
	}
	return false;
}
