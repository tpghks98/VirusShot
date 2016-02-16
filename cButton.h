#pragma once
#include "cui.h"
class cButton :
	public cUI
{
private:
	_SYNTHESIZE_INHER( bool, m_IsVirusPatten, VirusPatten );
	_SYNTHESIZE_REF_INHER( float, m_fPattenTime, PattenTime );
	_SYNTHESIZE_REF_INHER( D3DXVECTOR3, m_vStart, StartPos );
	_SYNTHESIZE_REF_INHER( D3DXVECTOR3, m_vEnd, EndPos );
public:
	virtual	void	Init();
	virtual	void	Update();
	virtual	void	Render();
	virtual	void	Release();

private:
	void	VirusPatten();
public:
	cButton(void);
	~cButton(void);
};

