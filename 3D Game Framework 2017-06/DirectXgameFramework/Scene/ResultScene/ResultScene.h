#pragma once

#include <d3d11.h>
#include <SimpleMath.h>

#include "../SceneBase.h"


class ResultScene : public SceneBase
{
public:
	//�R���X�g���N�^
	ResultScene(std::shared_ptr<SceneManager> scene);
	//�f�X�g���N�^
	~ResultScene();
	//����������
	void Initialize();
	//�X�V����
	void Update();
	//�`�揈��
	void Draw();
	//�I������
	void Finalize();
private:

};
