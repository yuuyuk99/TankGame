#pragma once

#include <memory>
#include <d3d11.h>
#include <SimpleMath.h>

class MapData
{
public:
	enum Land
	{
		FLOOR,
		WALL,

		NUM_LAND
	};
	MapData();
	MapData(DirectX::SimpleMath::Vector3& position);
	//MapData�I�u�W�F�N�g������������
	virtual void Initialize();
	//MapData�I�u�W�F�N�g���X�V����
	virtual void Update();
	//MapData�I�u�W�F�N�g�̍s��X�V
	virtual void Calc();
	//MapDate�I�u�W�F�N�g��`�悷��
	virtual void Draw();
	//MapData�̌㏈�����s��
	virtual void Finalize();
protected:
	//�ʒu
	DirectX::SimpleMath::Vector3& _Pos;
	//�q�I�u�W�F�N�g�ւ̃|�C���^
	std::shared_ptr<MapData> _Child;
	//Root�I�u�W�F�N�g�ւ̃|�C���^
	std::shared_ptr<MapData> _Root;
};