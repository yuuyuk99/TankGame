#include "Texture.h"
#include "../Tool/Direct3D.h"

// コンストラクタ
Texture::Texture(wchar_t* fname)
{
	//assert(g_pd3dDevice.Get());
	// テクスチャ作成
	DirectX::CreateWICTextureFromFile(g_pd3dDevice.Get(), fname, nullptr, &_texture);
}

Texture::~Texture()
{
	_texture->Release();
}