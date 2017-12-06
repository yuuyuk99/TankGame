#include "Tank.h"

using namespace DirectX::SimpleMath;
using namespace std;

/*
 *@�R���X�g���N�^
 */
Tank::Tank() : _Child(nullptr), _Pos(0.0f, 0.0f, 0.0f), _Rot(0.0f, 0.0f, 0.0f), _isKeyDown(false)
{

}

/*
 *@�R���X�g���N�^
 */
Tank::Tank(Vector3& position) : _Child(nullptr), _Pos(position) ,_Rot(0.0f, 0.0f, 0.0f)
{

}

/*
 *@�e�I�u�W�F�N�g��ݒ肷��
 */
std::weak_ptr<Tank> Tank::Parent()
{
	return this->_parent;
}

/*
 *@�e�I�u�W�F�N�g��ݒ肷��
 */
void Tank::Parent(const std::shared_ptr<Tank>& parent)
{
	this->_parent = parent;
}

