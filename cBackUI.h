#pragma once
#include "cui.h"
class cBackUI :
	public cUI
{
private:
	_SYNTHESIZE_REF_INHER( float, m_fStartScale, StartScale );
	_SYNTHESIZE_REF_INHER( float, m_fEndScale, EndScale );
	_SYNTHESIZE_REF_INHER( float, m_fScalingSpeed, ScalingSpeed );
	_SYNTHESIZE_INHER( bool, m_IsOnceUpdating, OnceUpdating );
	float	m_fScale;


public:
	virtual	void	Init();
	virtual	void	Update();
	virtual	void	Render();
	virtual	void	Release();
public:
	cBackUI(void);
	~cBackUI(void);
};

