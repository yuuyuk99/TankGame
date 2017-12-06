#include "Tank.h"

using namespace DirectX::SimpleMath;
using namespace std;

/*
 *@コンストラクタ
 */
Tank::Tank() : _Child(nullptr), _Pos(0.0f, 0.0f, 0.0f), _Rot(0.0f, 0.0f, 0.0f), _isKeyDown(false)
{

}

/*
 *@コンストラクタ
 */
Tank::Tank(Vector3& position) : _Child(nullptr), _Pos(position) ,_Rot(0.0f, 0.0f, 0.0f)
{

}

/*
 *@親オブジェクトを設定する
 */
std::weak_ptr<Tank> Tank::Parent()
{
	return this->_parent;
}

/*
 *@親オブジェクトを設定する
 */
void Tank::Parent(const std::shared_ptr<Tank>& parent)
{
	this->_parent = parent;
}

