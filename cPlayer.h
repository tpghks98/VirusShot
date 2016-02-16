#pragma once
#include "ccharacter.h"

class cGaugeUI;
class cPlayer :
	public cCharacter
{
protected:
	char*	m_pKey;
	bool	m_IsNoMove;
	bool	m_IsPlayer;
	bool	m_IsPower;
	float	m_fPowerTime;
	float	m_fMaxX;
	float	m_fMinX;
	float	m_fKnockBack;

	_SYNTHESIZE_INHER( int, m_nHowCanShotBullet, HowCanShotBullet );
	_SYNTHESIZE_REF_INHER( float, m_fMulti, Multi );
	_SYNTHESIZE_REF_INHER( float, m_fPG, PG );
	_SYNTHESIZE_REF_INHER( float, m_fRotQuat, RotQuat );
	_SYNTHESIZE_INHER( bool, m_IsGuard, Guard );
	_SYNTHESIZE_INHER( bool, m_IsOnceDir, OnceDir );
	_SYNTHESIZE_REF_INHER( float, m_fLRDir, LRDir );
	_SYNTHESIZE_REF_INHER( D3DXVECTOR3, m_vQuatRotAxis, QuatRotAxis);

private:
	cGaugeUI*	m_pHp;
	cGaugeUI*	m_pPg;
public:
	virtual	void	Init();
	virtual	void	Update();
	virtual	void	Render();
	virtual	void	Release();

	void	PlusPG( float fPG );
	void	AttackedDamagae( int nDamage );
private:
	void	PickUpItem( char* pName );
protected:
	void	KeyInput();
	void	Rotation();
	void	Move();
	void	KnockBack();
	virtual void	OnTimer( cTimer* pTimer ) override;
	virtual void	OnCollision( int nTargetType, IObj* pObj = NULL );

public:
	cPlayer(void);
	~cPlayer(void);
};

