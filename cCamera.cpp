#include "DXUT.h"
#include "cCamera.h"
#include "cSystemMgr.h"

cCamera::cCamera(void)
	:m_vEye( g_vZero ),
	m_vAt( g_vZero ),
	m_vUp( g_vZero )
	,m_pvTarget( NULL )
	,m_vRotatin( g_vZero )
{
}


cCamera::~cCamera(void)
{
}


void	cCamera::Init()
{
	m_vEye	=	D3DXVECTOR3( 0.0f, 10.0f, -15.0f );
	m_vAt	=	D3DXVECTOR3( 0.0f, 6.0f, 8.0f );
	m_vUp	=	D3DXVECTOR3( 0.0f, 1.0f, 0.0f );
	const	float	fNear	=	0.1f;
	const	float	fFar	=	10000.0f;
	const	float	fFovy	=	D3DX_PI	*	0.3f;

	D3DVIEWPORT9	vp;
	DXUTGetD3D9Device()->GetViewport( &vp );

	D3DXMATRIXA16	matProj,	matView;

	D3DXMatrixPerspectiveFovLH( &matProj, fFovy, vp.Width / vp.Height, fNear, fFar);

	D3DXMatrixLookAtLH( &matView, &m_vEye, &m_vAt, &m_vUp );
	
	DXUTGetD3D9Device()->SetTransform( D3DTS_PROJECTION, &matProj );
	DXUTGetD3D9Device()->SetTransform( D3DTS_VIEW, &matView );

}

void	cCamera::Update()
{
	D3DXMATRIXA16	matView;

	if( m_pvTarget != NULL )
	{
		m_vAt = (*m_pvTarget);
	}

	D3DXVECTOR3	vEye = m_vEye;
	D3DXVECTOR3	vAt = m_vAt;

	D3DXMATRIXA16	matRotX;
	D3DXMATRIXA16	matRotY;

	D3DXMatrixRotationX(&matRotX, m_vRotatin.x);
	D3DXMatrixRotationY(&matRotY, m_vRotatin.y);

	D3DXMATRIXA16	matRot;	
	D3DXMatrixIdentity( &matRot );	
	matRot = matRotX * matRotY;

	D3DXVec3TransformCoord( &vEye, &m_vEye, &matRot);


	vEye = _GETSINGLE( cSystemMgr )->GetPrevEye()  +
		( vEye - _GETSINGLE( cSystemMgr )->GetPrevEye() ) 
		* _GETSINGLE( cSystemMgr )->GetDeltaTime() * 5.0f;

	vAt = _GETSINGLE( cSystemMgr )->GetPrevAt()  +
		( m_vAt - _GETSINGLE( cSystemMgr )->GetPrevAt() ) 
		* _GETSINGLE( cSystemMgr )->GetDeltaTime() * 5.0f;

	D3DXVec3TransformCoord( &vAt, &vAt, &_GETSINGLE( cSystemMgr )->GetMatrixRot() );

	D3DXMatrixLookAtLH( &matView, &vEye, &vAt, &m_vUp );

	DXUTGetD3D9Device()->SetTransform( D3DTS_VIEW, &matView );

	_GETSINGLE( cSystemMgr )->SetPrevEye( vEye );
	_GETSINGLE( cSystemMgr )->SetPrevAt( vAt );



}

void	cCamera::Render()
{
}

void	cCamera::Release()
{
}