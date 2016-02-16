#pragma once

#include "value.h"

class cSmooth;
class cTimer;
class cCamera;
class IObj;
class cSystemMgr
{
private:
	bool	m_bKeyState[256];
	bool	m_bPrevKeyState[256];

	int		m_nShakeReverse;
	float	m_fShakePower;
	D3DXVECTOR3	m_vShakeDirection;

	CUSTOM_POINT	m_ptMouse;
	CUSTOM_POINT	m_ptMouseGap;

	_SYNTHESIZE_INHER( cCamera*, m_pCamera, Cameara );

	_SYNTHESIZE_REF_INHER( float, m_fTimeScale, TimeScale );
	_SYNTHESIZE_REF_INHER( D3DXVECTOR3, m_vPrevEye, PrevEye );
	_SYNTHESIZE_REF_INHER( D3DXVECTOR3, m_vPrevAt, PrevAt  );
	_SYNTHESIZE_REF_INHER( D3DXMATRIXA16, m_matRot, MatrixRot ); 
	std::list<cCamera*>	m_lstCamera;
private:
	void	KeyInputUpdate();
	void	MouseUpdate();


public:
	void	Init();
	void	Update();
	void	Release();

	cCamera*	CreateCamera();

	// Key & Mouse
	void	SetClientMouse( const CUSTOM_POINT& pt );
	int		GetKeyState( int nKey );

	const CUSTOM_POINT&	GetClientMouse()		{	return	this->m_ptMouse;	}
	const CUSTOM_POINT&	GetMouseGap()			{	return	this->m_ptMouseGap;	}


	// Camera 
	void	MainCameraUpdate();
	void	OtherCameraUpdate();

	void	SetCamera_Eye( const D3DXVECTOR3& vEye );
	void	SetCamera_At( const D3DXVECTOR3& vAt );
	void	SetCamera_Up( const D3DXVECTOR3& vUp );

	const D3DXVECTOR3&	GetCamera_Eye();
	const D3DXVECTOR3&	GetCamera_At();
	const D3DXVECTOR3&	GetCamera_Up();

	void	CameraShake( float fPower );

	
	// Timer
	cTimer* SetTimer( IObj* pObj, float fCool, short nType, bool IsRepeat = false );
	
	// Smooth

	cSmooth*	SetSmooth( float* fTarget, float fStart, float fEnd, float fSpeed = 1.0f );

	// Time

	float	GetDeltaTime()	{	return	DXUTGetElapsedTime() * m_fTimeScale; }

public:
	_SINGLETON( cSystemMgr );
};

