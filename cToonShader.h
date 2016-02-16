#pragma once
#include "cbaseshader.h"
class cToonShader :
	public cBaseShader
{
public:
	virtual void	Setting( cGeomNode* pNode  );
	virtual void	Setting(  LPDIRECT3DTEXTURE9 pTexture, D3DXMATRIXA16* pWorld  );

public:
	cToonShader(void);
	~cToonShader(void);
};

