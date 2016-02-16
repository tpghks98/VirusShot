#pragma once
#include "cresourcefile.h"
class cImageFile :
	public cResourceFile
{
private:
	_SYNTHESIZE_INHER( bool, m_IsBillBoard, BillBoard );
	_SYNTHESIZE_INHER( int,	m_nMax,	Max );
	std::vector<LPDIRECT3DTEXTURE9>		m_vecTexture;

public:
	void	AddTexture( LPDIRECT3DTEXTURE9	pTexture);
private:
	void	DrawTexture( D3DXMATRIXA16* pWorld,
		LPDIRECT3DTEXTURE9 pTexture );
public:
	virtual	void	Render( IObj* pObj, bool IsAni = false,
		cBaseShader* pShader = NULL ) override;	
public:
	cImageFile(void);
	~cImageFile(void);
};

