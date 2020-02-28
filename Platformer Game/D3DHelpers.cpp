#include "D3Dhelpers.h"

RECT getMaxTextureRect(ID3D11ShaderResourceView* pTex)
{
	assert(pTex);
	ID3D11Resource* res = nullptr;
	pTex->GetResource(&res);
	assert(res);
	ID3D11Texture2D* texture2d = nullptr;
	HRESULT hr = res->QueryInterface(&texture2d);
	RECT rect;
	if (SUCCEEDED(hr))
	{
		D3D11_TEXTURE2D_DESC desc;
		texture2d->GetDesc(&desc);
		rect = { 0, 0, static_cast<LONG>(desc.Width), static_cast<LONG>(desc.Height) };
	}
	ReleaseCOM(texture2d);
	ReleaseCOM(res);
	return rect;
}
