#pragma once
#include "iobj.h"
#include "cObjMgr.h"
#include "cSystemMgr.h"


class cCharacter :
	public IObj
{
public:
	
	_SYNTHESIZE_REF_INHER( float,	m_fHp	,	Hp );
	_SYNTHESIZE_REF_INHER( float,	m_fShotRot,	ShotRot );
	_SYNTHESIZE_INHER( cResourceFile*, m_pResBullet, BulletResource );
	_SYNTHESIZE_REF_INHER( float,	m_fBulletSpeed, BulletSpeed );
	_SYNTHESIZE_REF_INHER( float,	m_fShotCoolTime, ShotCoolTime );
	_SYNTHESIZE_INHER( bool,	m_IsCanShot,	CanShot );
	_SYNTHESIZE_REF_INHER( float, m_fRed, Red );

public:
	virtual	void	Init()		PURE;
	virtual	void	Update()	PURE;
	virtual	void	Render()	PURE;
	virtual	void	Release()	PURE;

	
protected:
	virtual void	OnTimer( cTimer* pTimer ) override;
	virtual void Shot( SHORT nTargetType, int nNum = 1, bool IsTimer = true, 
		D3DXVECTOR3 vScale = D3DXVECTOR3( 1 , 1 , 1  ));
	virtual void OnePieceShot( SHORT nTargetType, D3DXVECTOR3 vDir, bool IsTimer = true );
public:

	virtual void RedOn( float fSpeed = 3.0f );	
public:
	cCharacter(void);
	virtual ~cCharacter(void);
};

