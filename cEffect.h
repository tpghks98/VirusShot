#pragma once
#include "iobj.h"
class cEffect :
	public IObj
{
private:
	_SYNTHESIZE_INHER( IObj*, m_pTargetObject, TargetObject );
	_SYNTHESIZE_INHER( int, m_nEndCount, EndCount );
	_SYNTHESIZE_REF_INHER( float, m_fAlpha, Alpha );

public:
	virtual	void	Init();
	virtual	void	Update();
	virtual	void	Render();
	virtual	void	Release();

	virtual	void	OnAnimationEnd();
public:
	cEffect(void);
	~cEffect(void);
};

