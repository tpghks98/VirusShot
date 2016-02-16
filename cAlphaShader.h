#pragma once
#include "cbaseshader.h"
class cAlphaShader :
	public cBaseShader
{
public:
	virtual void	Setting( LPDIRECT3DTEXTURE9 pTexture,
		D3DXMATRIXA16* pWorld);
public:
	cAlphaShader(void);
	~cAlphaShader(void);
};

