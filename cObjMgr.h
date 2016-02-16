#pragma once

#include "value.h"

class	IObj;
class cBaseObject;
class cObjMgr
{
private:
	std::list<cBaseObject*>	m_listObject[OI_MAX];


	_SYNTHESIZE_INHER( int, m_nSellectStage, SellectStage );
	_SYNTHESIZE_INHER( bool ,m_IsGameClear, GameClear );
public:
	IObj*		m_pPlayer;
	D3DXVECTOR4	m_vLight;
	bool		m_IsRim;
	bool		m_IsLine;
	bool		m_IsEdge;
	float*		m_fTarget;
	float		m_fLighting;
	
public:
	void		Init();
	void		Update();
	void		Render();
	void		Release();

	void		ObjectCollision( int nType1, int nType2);
	std::list<cBaseObject*>*	GetObjectListPointer( int nType ) { return &m_listObject[nType]; }

	cBaseObject*		CreateObject( int nType, D3DXVECTOR3 vPos = g_vZero, char* pResourceKey = NULL );

	bool	GetCanAcessPlayer()	{  return m_pPlayer != NULL; }
	IObj*	GetPlayerPointer()	{	return	m_pPlayer; }
	
	void		AllMonsterAttacked();
	void		OnPlayerPower();
	void		GameStart();
	void		AllDestroyObject();
	void		UIChange( char* pKey );

	void		CreateBackUiTime( const float& fStartScale, const float& fScaleSpeed,
		const float& fDeleteTime, const D3DXVECTOR3& vPosition, char* pKey );
private:
	cBaseObject*	CreateMonsterSpawn( float fCoolTime, int nGenType, int nMonsterCount, float fImmediatelyTime = 0.0f );


public:
	_SINGLETON( cObjMgr );
};