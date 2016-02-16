#include "DXUT.h"
#include "cSystemMgr.h"
#include "cCamera.h"
#include "IObj.h"
#include "cTimer.h"
#include "cSmooth.h"
#include "cObjMgr.h"

static const UINT	nKeyValMax	=	255;

cSystemMgr::cSystemMgr(void)
	:m_ptMouse( 0, 0 ),
	m_vShakeDirection( 0, 0, 0 ),
	m_fShakePower( 0.0f ),
	m_nShakeReverse( 0 ),
	m_fTimeScale( 1.0f ),
	m_vPrevEye( g_vZero ),
	m_vPrevAt( g_vZero )
{
	D3DXMatrixIdentity( &m_matRot );
}


cSystemMgr::~cSystemMgr(void)
{
	Release();
}


void	cSystemMgr::Init()
{
	m_fTimeScale	=	1.0f;
	memset( this->m_bKeyState, false, sizeof( this->m_bKeyState ) );
	memset( this->m_bPrevKeyState, false, sizeof( this->m_bPrevKeyState ) );
 
	m_pCamera	=	new	cCamera;
	m_pCamera->Init();
	SetClientMouse( CUSTOM_POINT( g_nWinSizeX * 0.5f, g_nWinSizeX * 0.5f  ) );
}

void	cSystemMgr::Update()
{
	this->KeyInputUpdate();
	this->MouseUpdate();
	
	if( m_lstCamera.empty() )
	{
		this->MainCameraUpdate();
	}
	else
	{
		this->OtherCameraUpdate();
	}
	
	if( _GETSINGLE( cSystemMgr )->GetKeyState( '1' ) == KS_ONCE )
	{
		m_fTimeScale = !m_fTimeScale;
	}
}

void	cSystemMgr::Release()
{
	SAFE_DELETE( m_pCamera );
	for each( auto iter in m_lstCamera )
	{
		SAFE_DELETE( iter );
	}
	m_lstCamera.clear();
}

inline void cSystemMgr::SetClientMouse( const CUSTOM_POINT& pt )
{
	CUSTOM_POINT ptClient( pt );
	ClientToScreen( DXUTGetHWND(), &ptClient );

	SetCursorPos( ptClient.x, ptClient.y );
	
	m_ptMouse = pt;
}

int	cSystemMgr::GetKeyState( int nKey )
{
	if( !m_bKeyState[ nKey ] && !m_bPrevKeyState[ nKey ] )
		return	KS_NONE;

	if( m_bKeyState[ nKey ] && m_bPrevKeyState[ nKey ] )
		return	KS_DOWN;
	
	if( m_bKeyState[ nKey ] && !m_bPrevKeyState[ nKey ] )
		return	KS_ONCE;

	return	KS_UP;
}


inline void	cSystemMgr::KeyInputUpdate()
{
	memcpy( this->m_bPrevKeyState, this->m_bKeyState, sizeof( this->m_bPrevKeyState ) );

	for( UINT32 i = 0; i <= nKeyValMax; ++i )
	{
		m_bKeyState[i]	=	GetAsyncKeyState( i ) & 0x8000;
	}
}

inline void	cSystemMgr::MouseUpdate()
{
	CUSTOM_POINT	ptMouse;
	GetCursorPos( &ptMouse );
	ScreenToClient( DXUTGetHWND(), &ptMouse );

	m_ptMouseGap	=	ptMouse	-	this->m_ptMouse;

	m_ptMouse	=	ptMouse;

}

cTimer* cSystemMgr::SetTimer( IObj* pObj, float fCool,short nType, bool IsRepeat )
{
	cTimer*	pTimer	=	NULL;

	pTimer =  EASY_CAST( cTimer*,  _GETSINGLE( cObjMgr )->CreateObject( OI_TIMER ) );

	pTimer->nType = nType;
	pTimer->IsOn = true;
	pTimer->IsRepeat = IsRepeat;
	pTimer->fElapTime = 0.0f;
	pTimer->fCoolTime = fCool;
	pTimer->pOwner = pObj;


	return pTimer;
}

cSmooth*	cSystemMgr::SetSmooth( float* fTarget, float fStart, float fEnd, float fSpeed )
{

	cSmooth*	pSmooth = NULL;

	pSmooth = EASY_CAST( cSmooth*,  _GETSINGLE( cObjMgr )->CreateObject( OI_SMOOTH ) );

	pSmooth->fElap  = 0.0f;
	pSmooth->IsOn = true;
	pSmooth->pTarget = fTarget;
	pSmooth->fStart = fStart;
	pSmooth->fEnd	=	fEnd;
	pSmooth->fSpeed	=	fSpeed;

	return pSmooth;
}





void	cSystemMgr::MainCameraUpdate()
{
	m_pCamera->Update();
	if( m_fShakePower > 0.0f )
	{
		float	f	=	1.0f;
		if( m_nShakeReverse <= 0 )
		{
			m_vShakeDirection = D3DXVECTOR3( rand() % 1000 - 500, rand() % 1000 - 500, 0.0f );
			D3DXVec3Normalize( &m_vShakeDirection, &m_vShakeDirection );
			m_nShakeReverse = 6;
			m_fShakePower *= 0.7f;
			if( m_fShakePower < 0.02f )
			{
				m_fShakePower = 0.0f;
			}
		}
		if( m_nShakeReverse <= 3 )
		{
			f	*=	-1.0f;	
			
		}
		m_nShakeReverse -= 1;
		D3DXVECTOR3	vPlus;
		D3DXVECTOR3	vCameraEye = m_pCamera->m_vEye;
		D3DXVECTOR3	vCameraAt	=	m_pCamera->m_vAt;

		vPlus = f * m_vShakeDirection * m_fShakePower;

		D3DXMATRIXA16	matRot , matT;
		D3DXMatrixRotationY( &matRot, ( vPlus.x + vPlus.y + vPlus.z ) * 0.18f );
		D3DXVec3TransformCoord( &vCameraAt, &vCameraAt, &matRot );
		vCameraEye += vPlus;
		m_pCamera->m_vEye = vCameraEye;
		m_matRot = matRot;
	}
}

void	cSystemMgr::OtherCameraUpdate()
{
	auto	iter		=	m_lstCamera.begin();
	auto	end_iter	=	m_lstCamera.end();
	while( iter != end_iter )
	{
		(*iter)->Update();
		if( (*iter)->GetDelete()  )
		{
			SAFE_DELETE( *iter );
			iter = m_lstCamera.erase( iter );
			continue;
		}
		++iter;
	}
}

void	cSystemMgr::CameraShake( float fPower )
{
	if( m_fShakePower == 0.0f )
	{
		m_nShakeReverse = 0;
		m_vShakeDirection = g_vZero;
		m_fShakePower = fPower * 0.6f;
	}
}


cCamera*	cSystemMgr::CreateCamera()
{
	cCamera*	pCamera	=	new	cCamera();
	pCamera->Init();

	m_lstCamera.emplace_back( pCamera );

	return pCamera;
}



void	cSystemMgr::SetCamera_Eye( const D3DXVECTOR3& vEye )	{	this->m_pCamera->m_vEye = vEye;	}	
void	cSystemMgr::SetCamera_At( const D3DXVECTOR3& vAt )		{	this->m_pCamera->m_vAt	= vAt;	}
 void	cSystemMgr::SetCamera_Up( const D3DXVECTOR3& vUp )		{	this->m_pCamera->m_vUp	= vUp;	}

 const D3DXVECTOR3&	cSystemMgr::GetCamera_Eye()				{	return	this->m_pCamera->m_vEye;	}
 const D3DXVECTOR3&	cSystemMgr::GetCamera_At()				{	return	this->m_pCamera->m_vAt;		}
 const D3DXVECTOR3&	cSystemMgr::GetCamera_Up()				{	return	this->m_pCamera->m_vUp;		}