#include "Move.h"
#include <math.h>
#include "Shoot.h"


using namespace std;
using namespace DirectX::SimpleMath;

shared_ptr<AIState> Move::_AIstate = nullptr;

/*
 *@�R���X�g���N�^
 */
Move::Move()
{
	//���݂̏�Ԃ�������(�Ȃ�ł��Ȃ���Ԃɂ���)
	_currentstateNum = 0;
}

/*
 *@Move�N���X�̃C���X�^���X���擾����
 */
shared_ptr<AIState> Move::GetInstance()
{
	//�I�u�W�F�N�g�����݂��Ă��Ȃ��Ȃ�
	if (_AIstate == nullptr)
	{
		//�I�u�W�F�N�g�̐���
		_AIstate = make_shared<Move>();
	}
	//Move�̏�Ԃ�Ԃ�
	return _AIstate;
}

/*
*@�v���C���[�Ƃ̋��������߂�
*/
float Move::DistancePlayer(Enemy* enemy)
{
	//�v���C���[�ƃG�l�~�[�̋���
	float distance = 0;
	//const�Ȃ̂ŕύX�ł���悤�ɉ��̕ϐ������
	Vector3 dis = enemy->GetPlayer()->GetTrans();
	//��̏����Ɠ����悤�ȏ���������
	Vector3 disp = enemy->GetTrans();
	//�v���C���[�Ƃ̋��������߂�
	distance = sqrt((disp.x - dis.x) * (disp.x - dis.x) + (disp.z - dis.z) * (disp.z - dis.z));
	//�v���C���[�Ƃ̋�����Ԃ�
	return distance;
}

/*
 *@�^���[�Ƃ̋��������߂�
 */
float Move::DistanceTower(Enemy* enemy)
{
	//�G�l�~�[�ƃ^���[�̋���
	float distance = 0;
	//���̕ϐ�
	Vector3 dis = enemy->GetTower()->GetTrans();
	//��̏����Ɠ����悤�ȏ���������
	Vector3 disp = enemy->GetTrans();
	//�v���C���[�Ƃ̋��������߂�
	distance = sqrt((disp.x - dis.x) * (disp.x - dis.x) + (disp.z - dis.z) * (disp.z - dis.z));
	//�v���C���[�Ƃ̋�����Ԃ�
	return distance;
}


/*
 *@�I�u�W�F�N�g�̎��s
 */
inline void Move::Execute(Enemy* enemy)
{
	//�����߂̋���
	float check_distanceTower= 4.0f;
	//�v���C���[�Ɍ������đł���
	float check_distancePlayer = 2.0f;
	//�v���C���[�Ƃ̋��������߂�
	float distance_player = DistancePlayer(enemy);
	//�^���[�Ƃ̋��������߂�
	float distance_tower = DistanceTower(enemy);
	//�^���[�Ƃ̋�����check_distance���߂������ꍇ
	if (distance_tower <= check_distanceTower)
	{
		//�����łǂ����������n���\��
		//�G�̏�Ԃ���������ԂɕύX
		auto state = Shoot::GetInstance();
		assert(enemy);
		assert(state);
		enemy->ChangeState(state);
		return;
	}
	//�v���C���[�Ƃ̋�����check_distance���߂������ꍇ
	if (distance_tower <= check_distancePlayer)
	{
		//�����łǂ����������n���\��
		//�G�̏�Ԃ���������ԂɕύX
		auto state = Shoot::GetInstance();
		assert(enemy);
		assert(state);
		enemy->ChangeState(state);
		return;
	}
	//���݂̍��W��]�p���擾
	Vector3 trans = enemy->GetTrans();
	//��]��Y���󂯎��
	float rot_y = enemy->GetRot().y;
	//�G�l�~�[���������Ă���^���[�̈ʒu���󂯎��
	Vector3 pPos = enemy->GetTower()->GetTrans();
	//�G�l�~�[�̏ꏊ���󂯎��
	Vector3 ePos = enemy->GetTrans();
	//���@�ƓG�̏ꏊ�̍����v�Z����
	Vector3 dPos = pPos - ePos;
	//���𐳋K��������
	dPos.Normalize();
	//�ړ��x�N�g��
	Vector3 move(dPos / 20.0f);
	//��]
	Matrix rotm = Matrix::CreateRotationY(rot_y);
	//�ړ��x�N�g������]����
	move = Vector3::TransformNormal(move, rotm);
	//�ړ��x�N�g���𑫂�
	trans += move;
	//�ړ����s��
	enemy->SetTrans(trans);
}

void Move::Pathfinding(std::shared_ptr<Enemy> enemy)
{
	//�S�[���n�_
	Vector3 goal = enemy->GetPlayer()->GetTrans();
	//�G�̈ړ�
	Vector3 vec = goal - _Pos;
	//���K�����s��
	vec.Normalize();
	
	Vector3 nol = vec;
}


/*
 *@Move�I�u�W�F�N�g��j������
 */
void Move::Finalize()
{

}
