#include "Floor.h"

/*
 *@�R���X�g���N�^
 */
Floor::Floor()
{

}

/*
 *@Floor�̏���������
 */
void Floor::Initialize()
{
	_Floor->LoadModelFile(L"Resources/cModels/Grass.cmo");
}

/*
 *@Floor�̍X�V����
 */
void Floor::Update()
{
	Calc();
}

/*
 *@Floor�̍s��X�V
 */
void Floor::Calc()
{
	_Floor->Calc();
}

/*
 *@Floor�̕`�揈��
 */
void Floor::Draw()
{
	_Floor->Draw();
}

/*
 *@Floor�̌㏈��
 */
void Floor::Finalize()
{

}
