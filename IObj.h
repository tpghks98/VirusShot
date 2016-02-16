#pragma once

#include "cResourceMgr.h"
#include "cAseFile.h"
#include "value.h"
#include "cPostMgr.h"
#include "cSystemMgr.h"

#include "cBaseObject.h"


class cTimer;
class IObj
	:public cBaseObject
{


public:

	_SYNTHESIZE_REF_INHER( D3DXMATRIXA16, m_matWorld, WorldMatrix );
	_SYNTHESIZE_REF_INHER( D3DXVECTOR3, m_vPos,	Pos );
	_SYNTHESIZE_REF_INHER( D3DXVECTOR3, m_vScale, Scale );
	_SYNTHESIZE_REF_INHER( D3DXVECTOR3,	m_vRotation, Rotation );
	_SYNTHESIZE_REF_INHER( D3DXMATRIXA16, m_matLookAt, LookAtMatrix );
	_SYNTHESIZE_REF_INHER( float, m_fAniKey, AniKey );
	_SYNTHESIZE_INHER( cResourceFile*, m_pResourceFile, ResourceFile );
	_SYNTHESIZE_REF_INHER( D3DXVECTOR3, m_vDirection, Direction );
	_SYNTHESIZE_REF_INHER( float, m_fMoveSpeed, MoveSpeed );
	_SYNTHESIZE_REF_INHER( D3DXVECTOR3, m_vCenterPosition, CenterPosition );
	_SYNTHESIZE_REF_INHER( D3DXQUATERNION, m_quatLookAt, QuatLookAt );


protected:
	virtual	void	Translation()
	{
		D3DXMATRIXA16	matTrans,	matRotation,	matScale;

		{
			D3DXMatrixTranslation( &matTrans, m_vPos.x, m_vPos.y, m_vPos.z );
			D3DXMatrixRotationYawPitchRoll( &matRotation, m_vRotation.y, m_vRotation.x, m_vRotation.z );
			D3DXMatrixScaling( &matScale, m_vScale.x, m_vScale.y, m_vScale.z );
			D3DXMatrixRotationQuaternion( &m_matLookAt, &m_quatLookAt );
		}
		m_matWorld	=	matScale	*	matRotation * m_matLookAt	*	matTrans;
	}
	virtual void	ModelRender( bool IsAni = false, cBaseShader* pShader = NULL, bool IsBlur = false )
 	{
		m_vCenterPosition =  m_vPos + EASY_CAST( cAseFile* ,m_pResourceFile )->m_vModelCenter;

		m_pResourceFile->Render( this,IsAni,  pShader );
		if( IsBlur )
		{
			_GETSINGLE( cPostMgr )->BeginBulr();
			m_pResourceFile->Render( this, false, pShader );
			_GETSINGLE( cPostMgr )->EndBlur();
		}
	}


public:
	virtual	void	Init()		PURE;
	virtual	void	Update()	PURE;
	virtual	void	Render()	PURE;
	virtual	void	Release()	PURE;

	virtual void	OnTimer( cTimer* pTimer ){};
	virtual void	OnCollision( int nTargetType, IObj* pObj = NULL ) {};
	virtual	void	OnAnimationEnd()	{ m_fAniKey = 0.0f; }
	virtual void	DirectionMove()
	{
		m_vPos += m_vDirection * m_fMoveSpeed * _GETSINGLE( cSystemMgr )->GetDeltaTime() ;
	}
	virtual	void	DirectionRotation( bool IsSmooth = false);

	float		GetRadius()
	{	return	EASY_CAST( cAseFile*,	m_pResourceFile ) ->m_fModelRadius; }
	D3DXMATRIXA16*	GetMatrixPointer()
	{	return	&m_matWorld; }
public:
	IObj(void);
	virtual ~IObj(void);
};