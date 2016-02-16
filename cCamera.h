#pragma once

#include "value.h"
#include "cBaseObject.h"

class cCamera
	:public cBaseObject
{
	friend	class	cSystemMgr;
private:
	_SYNTHESIZE_INHER( D3DXVECTOR3, m_vEye, Eye);
	_SYNTHESIZE_INHER( D3DXVECTOR3, m_vAt, At);
	_SYNTHESIZE_INHER( D3DXVECTOR3, m_vUp, Up);
	_SYNTHESIZE_INHER( D3DXVECTOR3*, m_pvTarget, Target );

	_SYNTHESIZE_REF_INHER( D3DXVECTOR3,	m_vRotatin, Rotation );

public:
	virtual	void	Init();
	virtual	void	Update();
	virtual	void	Render();
	virtual	void	Release();
public:
	cCamera(void);
	~cCamera(void);
};

