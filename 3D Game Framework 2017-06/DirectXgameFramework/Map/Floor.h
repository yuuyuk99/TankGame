#pragma once

#include <memory>
#include "MapData.h"
#include "../Base/ObjectBase.h"

class Floor : public MapData
{
public:
	//�R���X�g���N�^
	Floor();
	//Floor�I�u�W�F�N�g������������
	void Initialize() override;
	//Floor�I�u�W�F�N�g���X�V
	void Update() override;
	//Floor�I�u�W�F�N�g�̍s��X�V
	void Calc() override;
	//Floor�I�u�W�F�N�g��`��
	void Draw() override;
	//Floor�I�u�W�F�N�g�̌㏈�����s��
	void Finalize() override;
private:
	std::shared_ptr<ObjectBase> _Floor;
};