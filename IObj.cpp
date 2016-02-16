#include "DXUT.h"
#include "IObj.h"


IObj::IObj(void)
	:m_vPos( 0.f, 0.f, 0.f ),
	m_vScale( 1.0f, 1.0f, 1.0f ),
	m_vRotation( 0.f, 0.f, 0.f ),
	m_fAniKey( 0.0f ),
	m_pResourceFile( NULL ),
	m_fMoveSpeed( 1.0f ),
	m_vDirection( 0.0f, 0.0f, 0.0f )
{
	D3DXQuaternionIdentity( &m_quatLookAt );
	D3DXMatrixIdentity( &m_matLookAt );
	D3DXMatrixIdentity( &m_matWorld );
}



IObj::~IObj(void)
{
}

void	IObj::DirectionRotation( bool IsSmooth )
{
//	D3DXVec3Normalize( &m_vDirection, &m_vDirection );

	D3DXVECTOR3	vCoord;
	D3DXVECTOR3	vCross;
	
	D3DXMATRIXA16	matRotY;
	D3DXMatrixRotationY( &matRotY, -D3DX_PI * 0.5f );

	D3DXVec3TransformCoord( &vCoord, &m_vDirection, &matRotY );
	D3DXVec3Normalize( &vCoord, &vCoord );


	D3DXMatrixRotationX( &matRotY, D3DX_PI );

	D3DXVec3Cross( &vCross, &vCoord, &m_vDirection );
	D3DXVec3TransformCoord( &vCross, &vCross, &matRotY );
	D3DXVec3Normalize( &vCross, &vCross );

	memcpy( &m_matLookAt._11, &vCoord, sizeof( D3DXVECTOR3 ) );
	memcpy( &m_matLookAt._21, &vCross, sizeof( D3DXVECTOR3 ) );
	memcpy( &m_matLookAt._31, &m_vDirection, sizeof( D3DXVECTOR3 ) );
	memcpy( &m_matLookAt._41, &D3DXVECTOR3( 0.0f, 0.0f, 0.0f ), sizeof( D3DXVECTOR3 ) );

	D3DXQUATERNION q;
	D3DXQuaternionRotationMatrix( &q, &m_matLookAt );

	D3DXQuaternionSlerp( &m_quatLookAt, &m_quatLookAt, &q, 0.1f );
	
}