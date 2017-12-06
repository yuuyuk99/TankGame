#pragma once
#include "../SceneBase.h"
#include "../../Texture/Texture.h"
#include <memory>
#include <SpriteBatch.h>
#include <d3d11.h>
#include <wrl\client.h>
#include "../../Base/ObjectBase.h"
#include "../../Camera/Camera.h"

class TitleScene : public SceneBase
{
public:
	static const int TITLE_NUM = 2;
	TitleScene(std::shared_ptr<SceneManager> scene);
	~TitleScene();
	void Initialize();
	void Update();
	void Draw();
	void Finalize();
private:
	 // �`�悵�Ă���G
	 Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> _texture;
	 //
	 std::shared_ptr<ObjectBase> _titleTexture;
	 //�J����
	 std::shared_ptr<Camera> _camera;
	 //�R�����X�e�[�^�X
	 std::unique_ptr<DirectX::CommonStates> _commonStates;
	 //�G�t�F�N�g�t�@�N�g��
	 std::unique_ptr<DirectX::EffectFactory> _factory;
};