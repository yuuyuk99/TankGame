#pragma once

#include <d3d11.h>
#include <WICTextureLoader.h>

class Texture
{
public:
	//�e�N�X�`��
	ID3D11ShaderResourceView* _texture;
	// �R���X�g���N�^
	Texture(wchar_t* fname);
	// �f�X�g���N�^
	~Texture();
private:
};
