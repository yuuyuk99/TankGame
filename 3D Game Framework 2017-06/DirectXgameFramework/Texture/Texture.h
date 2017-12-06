#pragma once

#include <d3d11.h>
#include <WICTextureLoader.h>

class Texture
{
public:
	//テクスチャ
	ID3D11ShaderResourceView* _texture;
	// コンストラクタ
	Texture(wchar_t* fname);
	// デストラクタ
	~Texture();
private:
};
