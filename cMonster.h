#pragma once
#include "cCharacter.h"
class cMonster :
	public cCharacter
{
public:
	float		m_fMinZ;
	float		m_f;
	float		m_fOriMoveSpeed;
protected:
	float		m_fGrowTime;
	bool		m_IsCanPull;
	bool		m_IsGrow;
	bool		m_IsOnGrow;
	D3DXVECTOR3	m_vOriScale;
public:
	virtual	void	Init();
	virtual	void	Update();
	virtual	void	Render();
	virtual	void	Release();
	virtual void	OnCollision( int nTargetType, IObj* pObj = NULL );


protected:
	virtual void	SettingGrow( float fTime );
	virtual void	OnTimer( cTimer* pTimer ) override;
	virtual	void	SideMove();
	virtual	void	CheckSurvive();
	virtual	void	Grow();
public:
	cMonster(void);
	~cMonster(void);
};

