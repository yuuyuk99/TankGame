#pragma once

#include <memory>

#include "../Base/ObjectBase.h"

class Camera;

class BackScreen
{
public:
	//�R���X�g���N�^
	BackScreen();
	//�f�X�g���N�^
	~BackScreen();
	//����������
	void Initialize();
	//�X�V����
	void Update();
	//�`�揈��
	void Draw(std::shared_ptr<Camera> camera);
	//�I������
	void Finalize();
private:
	//�w�i
	std::shared_ptr<ObjectBase> _back;
	//�G�t�F�N�g�t�@�N�g��
	std::unique_ptr<DirectX::EffectFactory> _factory;
	//�R�����X�e�[�g
	std::unique_ptr<DirectX::CommonStates> _commonState;
};
