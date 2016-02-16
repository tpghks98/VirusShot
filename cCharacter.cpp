#include "DXUT.h"
#include "cCharacter.h"
#include "cBullet.h"
#include "cTimer.h"

cCharacter::cCharacter(void)
	:m_pResBullet( NULL ),
	m_IsCanShot( true ),
	m_fShotCoolTime( 0.0f ),
	m_fRed( 0.0f ),
	m_fBulletSpeed( 10.0f ),
	m_fShotRot( 0.05f )
{
}


cCharacter::~cCharacter(void)
{
}


void	cCharacter::OnTimer( cTimer* pTimer )
{
	switch( pTimer->nType )
	{
	case TT_SHOT:
		m_IsCanShot = true;
		break;
	}
}
void	cCharacter::Shot( SHORT nTargetType, int nNum, bool IsTimer, D3DXVECTOR3 vScale)
{
	m_IsCanShot = false;
	SHORT	nType	=	OI_BULLET;
	if( nTargetType == OI_PLAYER )
	{
		nType	=	OI_ENEMYBULLET;
	}
	
	float	fPlus	=	( D3DX_PI * m_fShotRot ) / (float)nNum;
	float	fValue = - ( nNum / 2) * fPlus;


	D3DXVECTOR3	vDir	=	m_vDirection;
	D3DXMATRIXA16	matRot, matRotZ;
	D3DXMatrixRotationY( &matRotZ, -m_vRotation.z * 0.3f );
	for( int n =0 ; n < nNum; ++n )
	{	
		D3DXVECTOR3	vPos	=	D3DXVECTOR3(
			m_matWorld._41, m_matWorld._42, m_matWorld._43 );

		D3DXMatrixRotationY( &matRot, fValue );

		if( nNum < 3 )
		{
			vPos = D3DXVECTOR3(
			m_matWorld._41, m_matWorld._42, m_matWorld._43 );
			D3DXVec3TransformCoord( &vDir, &m_vDirection, &matRotZ );
		}
		else
		{
			D3DXVec3TransformCoord( &vDir, &m_vDirection, &matRot );	
		}
		fValue	+=	fPlus;
		
   		IObj* pBullet = EASY_CAST( IObj* ,
			_GETSINGLE( cObjMgr )->CreateObject( nType, vPos + vDir, m_pResBullet->GetKey() ) );
		
		pBullet->SetDirection( vDir ); 
		pBullet->SetMoveSpeed( m_fBulletSpeed );
		D3DXVECTOR3 v = pBullet->GetScale();
		v *= vScale.x;
		pBullet->SetScale( v);
	}
	if( IsTimer )
	{
		m_lstChild.push_back(
			_GETSINGLE( cSystemMgr )->SetTimer( this, m_fShotCoolTime, TT_SHOT ) );
	}
}
void cCharacter::OnePieceShot( SHORT nTargetType, D3DXVECTOR3 vDir, bool IsTimer  )
{
	m_IsCanShot = false;
	SHORT	nType	=	OI_BULLET;
	if( nTargetType == OI_PLAYER )
	{
		nType	=	OI_ENEMYBULLET;
	}

	IObj* pBullet = EASY_CAST( IObj* ,
		_GETSINGLE( cObjMgr )->CreateObject( nType, m_vPos, m_pResBullet->GetKey() ) );
		
		pBullet->SetDirection( vDir ); 
		pBullet->SetMoveSpeed( m_fBulletSpeed );

	if( IsTimer )
	{
		m_lstChild.push_back(
			_GETSINGLE( cSystemMgr )->SetTimer( this, m_fShotCoolTime, TT_SHOT ) );
	}
}

void	cCharacter::RedOn( float fSpeed )
{
	
	m_fRed	=	1.0f;
	cSmooth* p	=	_GETSINGLE( cSystemMgr )->SetSmooth( &m_fRed, 1.0f, 0.0f, fSpeed );

	m_lstChild.push_back( (cBaseObject*)p );
	
	
}