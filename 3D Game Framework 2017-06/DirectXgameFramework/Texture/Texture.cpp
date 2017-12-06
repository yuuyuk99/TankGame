#include "Texture.h"
#include "../Tool/Direct3D.h"

// �R���X�g���N�^
Texture::Texture(wchar_t* fname)
{
	//assert(g_pd3dDevice.Get());
	// �e�N�X�`���쐬
	DirectX::CreateWICTextureFromFile(g_pd3dDevice.Get(), fname, nullptr, &_texture);
}

Texture::~Texture()
{
	_texture->Release();
}