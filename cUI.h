#pragma once
#include "iobj.h"
class cUI :
	public IObj
{
protected:
	_SYNTHESIZE_REF_INHER( float, m_fDelayTime, DelayTime );
	_SYNTHESIZE_INHER( bool, m_IsAniDelete, AniDelete );
public:
	virtual	void	Init()		PURE;
	virtual	void	Update();
	virtual	void	Render()	PURE;
	virtual	void	Release()	PURE;

public:
	void	SetDeleteTimer( float fTime);
	virtual void	OnTimer( cTimer* pTimer );

public:
	cUI(void);
	virtual ~cUI(void);
};

