#include "Wall.h"

/*
 *@�R���X�g���N�^
 */
Wall::Wall()
{

}

/*
 *@�f�X�g���N�^
 */
Wall::~Wall()
{

}

/*
 *@Wall�I�u�W�F�N�g�̏���������
 */
void Wall::Initialize()
{
	_Wall->LoadModelFile(L"Resources/cModels/box.cmo");
}

/*
 *@Wall�I�u�W�F�N�g�̍X�V����
 */
void Wall::Update()
{
	Calc();
}

/*
 *@Wall�I�u�W�F�N�g�̍s��X�V
 */
void Wall::Calc()
{
	_Wall->Calc();
}

/*
 *@Wall�I�u�W�F�N�g�̕`�揈��
 */
void Wall::Draw()
{
	_Wall->Draw();
}

/*
 *@Wall�I�u�W�F�N�g�̌㏈��
 */
void Wall::Finalize()
{

}
