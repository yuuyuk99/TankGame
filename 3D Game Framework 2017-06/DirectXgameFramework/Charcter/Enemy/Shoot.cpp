#include "Shoot.h"
#include <math.h>
#include "Move.h"

//���݂̏�Ԃ�nullptr�ɂ���
std::shared_ptr<AIState> Shoot::_AIstate = nullptr;

/*
 *@���O���
 */
using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

/*
 *@�R���X�g���N�^
 */
Shoot::Shoot() : _delay(0)
{
	
}

/*
 *@Shoot�N���X�̃C���X�^���X���擾����
 */
shared_ptr<AIState> Shoot::GetInstance()
{
	//�I�u�W�F�N�g�����݂��Ă��Ȃ��Ȃ�
	if (_AIstate == nullptr)
	{
		//�I�u�W�F�N�g�̐���
		_AIstate = make_shared<Shoot>();
	}
	//Shoot�̏�Ԃ�Ԃ�
	return _AIstate;
}

/*
 *@�I�u�W�F�N�g�����s����
 */
inline void Shoot::Execute(Enemy* enemy)
{

	_delay++;
	//�A���Ō��ĂȂ��悤�ɂ���
	if (_delay > 60.0f)
	{
		//�f�B���C�����Z�b�g����
		_delay = 0.0f;
		//�G�̍s�����ړ��ɖ߂�
		enemy->ChangeState(Move::GetInstance());
	}
	//�v���C���[�̍��W
	//Vector3 ptrans = enemy->GetPlayer()->GetTrans();
	////�v���C���[�̊p�x�Ɍ�������
	//float angle =  atan2(ptrans.z - enemy->GetTrans().z, ptrans.x - enemy->GetTrans().x);
	//enemy->SetRot(Vector3(0.0f, -angle, 0.0f));

		//TODO:��������ǉ��\��
	enemy->SetShootBullet(true);
}

/*
 *@Shoot�I�u�W�F�N�g��j������
 */
void Shoot::Finalize()
{

}
