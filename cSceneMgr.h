#pragma once

#include "value.h"

class cScene;
class cFade;
class cSceneMgr
{
private:
	_SYNTHESIZE_INHER( cScene*,	m_pScene, Scene );
	_SYNTHESIZE_REF_INHER( float, m_fFade, Fade );
	_SYNTHESIZE_REF_INHER( float, m_fFadePlus, FadePlus );
	_SYNTHESIZE_INHER( bool, m_IsFade, IsFade );
	_SYNTHESIZE_INHER( int, m_nSceneID, ID );
	_SYNTHESIZE_INHER( cFade*, m_pFade, FadeObject );
	_SYNTHESIZE_INHER( char*, m_pUIName, UIName );
public:
	void	Init();
	void	Render();
	void	Update();

public:
	void	ChangeUI();
	void	ChangeScene( int nID);
	void	ClickButton( char* pName );

	void	CreateVirusButton( D3DXVECTOR3 vPos, char* pKey );
private:
	void	AssignScene();
public:
	_SINGLETON( cSceneMgr );
};

