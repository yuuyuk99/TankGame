#pragma once

#include <d3d11.h>
#include <SimpleMath.h>

#include "../SceneBase.h"


class ResultScene : public SceneBase
{
public:
	//コンストラクタ
	ResultScene(std::shared_ptr<SceneManager> scene);
	//デストラクタ
	~ResultScene();
	//初期化処理
	void Initialize();
	//更新処理
	void Update();
	//描画処理
	void Draw();
	//終了処理
	void Finalize();
private:

};
