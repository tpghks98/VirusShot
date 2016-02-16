#include "DXUT.h"
#include "cObjMgr.h"
#include "cPlayer.h"
#include "cResourceMgr.h"
#include "cSystemMgr.h"
#include "cBullet.h"
#include "cMonster.h"
#include "cMonsterSpawn.h"
#include "cEnemyBullet.h"
#include "cAseFile.h"
#include "cEffect.h"
#include "cGround.h"
#include "cTimer.h"
#include "cSmooth.h"
#include "cRedCell.h"
#include "cWhiteCell.h"
#include "cSubPlayer.h"
#include "cItem.h"
#include "cVirus.h"
#include "cCancer.h"
#include "cBacteria.h"
#include "cBackUI.h"
#include "cGaugeUI.h"
#include "cFade.h"
#include "cButton.h"
#include "cSceneMgr.h"

class cSort
{
public:
	bool	operator()( cBaseObject* pObj1, cBaseObject* pObj2 )
	{
		return EASY_CAST( IObj*, pObj1 )->GetPos().z * EASY_CAST( IObj*, pObj1 )->GetScale().z > EASY_CAST( IObj*, pObj2 )->GetPos().z * EASY_CAST( IObj*, pObj2 )->GetScale().z;
	}

};
cObjMgr::cObjMgr(void)
	:m_vLight( 0.0f, -2.0f, 1.0f, 0.0f ),
	m_fTarget( NULL ),
	m_IsRim( true ),
	m_IsLine( true ),
	m_IsEdge( false ),
	m_fLighting( 1.0f ),
	m_pPlayer( NULL ),
	m_nSellectStage( 1 ),
	m_IsGameClear( false )
{
}


cObjMgr::~cObjMgr(void)
{
	Release();
}


void	cObjMgr::Init()
{
	m_nSellectStage = 1;
}

void	cObjMgr::Update()
{
	if( m_IsGameClear )
	{
		m_IsGameClear = false;
		_GETSINGLE( cSceneMgr )->ChangeScene( SI_HOME );
		m_nSellectStage = 2;
	}

	// Object Collsiion
	this->ObjectCollision( OI_MONSTER, OI_MONSTER );
	this->ObjectCollision( OI_MONSTER, OI_BULLET );
	this->ObjectCollision( OI_ENEMYBULLET, OI_BULLET );
	this->ObjectCollision( OI_PLAYER, OI_ENEMYBULLET );
	this->ObjectCollision( OI_PLAYER, OI_MONSTER );
	this->ObjectCollision( OI_PLAYER, OI_ITEM );

	// Object Update
	for( int n = 0; n < OI_MAX; ++n )
	{
		auto	iter		=	m_listObject[n].begin();
		auto	end_iter	=	m_listObject[n].end();

		while( iter != end_iter )
 		{
			if( (*iter)->GetDelete() )
			{
				SAFE_DELETE( *iter );
				iter = m_listObject[n].erase( iter );
				continue;
			}
			(*iter)->Update();
			++iter;
		}
	}
	
	// Effect Z Sort
	m_listObject[OI_EFFECT].sort( cSort() );

}


void	cObjMgr::Render()
{
	for( int n = 0; n < OI_MAX; ++n )
	{
		for each( auto Object in m_listObject[n] )
		{
			Object->Render();
		}
	}
}

void	cObjMgr::Release()
{
	AllDestroyObject();
}

cBaseObject*	cObjMgr::CreateObject( int nType, D3DXVECTOR3 vPos , char* pResourceKey )
{
	cBaseObject*	pObj	=	NULL;
	switch( nType )
	{
	case OI_PLAYER:
		pObj	=	new	cPlayer();
		break;
	case OI_SUB_PLAYER:
		pObj	=	new cSubPlayer();
		break;
	case OI_BULLET:
		pObj	=	new cBullet();
		break;
	case OI_ENEMYBULLET:
		pObj	=	new	cEnemyBullet();
		break;
	case OI_MONSTER:
		pObj	=	new	cMonster();
		break;
	case OI_MONSTERSPAWN:
		pObj	=	new	cMonsterSpawn();
		break;
	case OI_EFFECT:
		pObj	=	new	cEffect();
		break;
	case OI_GROUND:
		pObj	=	new cGround();
		break;
	case OI_SMOOTH:
		pObj	=	new	cSmooth();
		break;
	case OI_TIMER:
		pObj	=	new	cTimer();
		break;
	case OI_REDCELL:
		pObj	=	new cRedCell();
		nType	=	OI_MONSTER;
		break;
	case OI_WHITECELL:
		pObj	=	new cWhiteCell();
		nType	=	OI_MONSTER;
		break;
	case OI_ITEM:
		pObj	=	new	cItem();
		break;
	case OI_VIRUS:
		pObj	=	new cVirus();
		nType	=	OI_MONSTER;
		break;
	case OI_CANCER:
		pObj	=	new	cCancer();
		nType	=	OI_MONSTER;
		break;
	case OI_BACTERIA:
		pObj	=	new	cBacteria();
		nType	=	OI_MONSTER;
		break;
	case OI_BACKUI:
		pObj	=	new	cBackUI();
		break;
	case OI_GAUGE_UI:
		pObj	=	new cGaugeUI();
		break;
	case OI_FADE:
		pObj	=	new	cFade();
		break;
	case OI_BUTTON:
		pObj	=	new	cButton();
		break;
	default:
		return	NULL;
	}

	if( pResourceKey != NULL )
		((cCharacter*)pObj)->SetResourceFile( _GETSINGLE( cResourceMgr )->GetResourceFile( pResourceKey ) );

	if( vPos != g_vZero )
		((cCharacter*)pObj)->SetPos( vPos );

	pObj->Init();

	m_listObject[nType].emplace_back( pObj );

	return	pObj;
}

void		cObjMgr::ObjectCollision( int nType1, int nType2)
{

	auto iter_1	=	m_listObject[nType1].begin();
	auto end_iter_1	=	m_listObject[nType1].end();

	auto iter_2	=	m_listObject[nType2].begin();
	auto end_iter_2	=	m_listObject[nType2].end();

	IObj*	pTarget1	=	NULL;
	IObj*	pTarget2	=	NULL;


	float	fLength;
	while( iter_1 != end_iter_1 )
	{
		pTarget1	=	EASY_CAST( IObj*,  *iter_1 );
		while( iter_2 != end_iter_2 )
		{
			pTarget2	=	EASY_CAST( IObj*, *iter_2 );

			D3DXVECTOR3	v	=	(pTarget1->GetCenterPosition() 
				- pTarget2->GetCenterPosition());
			v.y = 0.0f;

			fLength	=
				D3DXVec3Length( &v  );

			float f = pTarget1->GetRadius() * pTarget1->GetScale().x + pTarget2->GetRadius() * pTarget2->GetScale().x;
			if( fLength <= f )
			{
				pTarget1->OnCollision( nType2, pTarget2 );
				pTarget2->OnCollision( nType1, pTarget1 );
			}
			++iter_2;
		}
		iter_2 = m_listObject[nType2].begin();
		++iter_1;
	}
}


cBaseObject* cObjMgr::CreateMonsterSpawn( float fCoolTime, int nGenType, int nMonsterCount, float fImmediatelyTime )
{
	auto pObj =  CreateObject( OI_MONSTERSPAWN );
	EASY_CAST(cMonsterSpawn*, pObj )->SetTargetType( nGenType );
	EASY_CAST(cMonsterSpawn*, pObj )->SetMonsterCount( nMonsterCount );

	if( fCoolTime > 0.0f )
	{
		EASY_CAST(cMonsterSpawn*, pObj )->SetupGenTimer( fCoolTime, fImmediatelyTime );
	}

	return pObj;
}
void		cObjMgr::AllMonsterAttacked()
{
	for each( auto it in m_listObject[OI_MONSTER] )
	{

		EASY_CAST( IObj*, it )->OnCollision( OI_BULLET, m_pPlayer );
		CreateObject( OI_EFFECT, EASY_CAST( IObj*, it )->GetPos() + 
			D3DXVECTOR3( ( rand() % 10000 - 5000 ) * 0.0001f, ( rand() % 10000 - 5000 ) * 0.0001f, rand() % 10000 * 0.0001f ) , "hit_effect" ); 
	}
	for each( auto it in m_listObject[OI_ENEMYBULLET] )
	{
		EASY_CAST( IObj*, it )->OnCollision( OI_BULLET, m_pPlayer );
		CreateObject( OI_EFFECT, EASY_CAST( IObj*, it )->GetPos() + 
			D3DXVECTOR3( ( rand() % 10000 - 5000 ) * 0.0001f, ( rand() % 10000 - 5000 ) * 0.0001f, rand() % 10000 * 0.0001f ) , "hit_effect" ); 
	}
}
void	cObjMgr::OnPlayerPower()
{
	for each( auto it in m_listObject[OI_MONSTER] )
	{

		auto pObj = EASY_CAST( cEffect*,
			CreateObject( OI_EFFECT, EASY_CAST( IObj*, it )->GetPos(), "power_effect" ) );

		pObj->SetEndCount( 2 );
		pObj->SetTargetObject( (IObj*)it );
		pObj->SetRotation(  D3DXVECTOR3( 0.0f, 0.0f  ,0.0f ) );
	}
}


void	cObjMgr::GameStart()
{
	_GETSINGLE( cSystemMgr )->SetCamera_Eye( D3DXVECTOR3( 0.0f, 10.0f, -15.0f ));
	_GETSINGLE( cSystemMgr )->SetCamera_At( D3DXVECTOR3( 0.0f, 6.0f, 8.0f ));
	_GETSINGLE( cSystemMgr )->SetCamera_Up( D3DXVECTOR3( 0.0f, 1.0f, 0.0f ));

	m_IsGameClear = false;
	char* pGround = NULL;
	switch( m_nSellectStage )
	{
	case 1:
		pGround = "ground";
	_GETSINGLE( cObjMgr )->CreateBackUiTime( 0.0f, 1.0f, 5.0f, 
		D3DXVECTOR3( g_nWinSizeX * 0.5f, g_nWinSizeY * 0.5f, 0 ), "ui_stage1" );
		break;
	case 2:
		pGround = "ground_stage2";
		EASY_CAST( IObj* ,CreateMonsterSpawn( 4.5f, OI_BACTERIA, 1  ) ) ->SetPos( D3DXVECTOR3( 10.0f, 0.0f,  200.0f) );
		EASY_CAST( IObj* ,CreateMonsterSpawn( 4.5f, OI_BACTERIA, 1  ) ) ->SetPos( D3DXVECTOR3( -10.0f, 0.0f,  200.0f) );
	_GETSINGLE( cObjMgr )->CreateBackUiTime( 0.0f, 1.0f, 5.0f, 
		D3DXVECTOR3( g_nWinSizeX * 0.5f, g_nWinSizeY * 0.5f, 0 ), "ui_stage2" );
		break;
	}
	EASY_CAST( IObj* ,CreateMonsterSpawn( 1000.0f, OI_CANCER, 1 , 950.0f  ) ) ->SetPos( D3DXVECTOR3( 0.0f, 0.0f, 500.0f ) );

	for( int n = 0; n < 10; ++n )
	{
		CreateObject( OI_GROUND, D3DXVECTOR3( 0.0f, 0.0f, 502.0f * n ), pGround );
	}

	_GETSINGLE( cObjMgr )->CreateObject( OI_BACKUI, D3DXVECTOR3( g_nWinSizeX * 0.5f, g_nWinSizeY * 0.5f, 0.0f ), "ui_window" );


	m_pPlayer = (IObj*)CreateObject( OI_PLAYER );

	CreateMonsterSpawn( 10.0f, OI_REDCELL , 2  );
	CreateMonsterSpawn( 10.0f, OI_WHITECELL, 1  );
	CreateMonsterSpawn( 5.5f, OI_VIRUS, 1  );
	for( int n =0; n < 3; ++n )
	{
		EASY_CAST( IObj* ,CreateMonsterSpawn( 17.5f, OI_BACTERIA, 1 , n * 2.5f  ) ) ->SetPos( D3DXVECTOR3( 30.0f, 0.0f,  90.0f) );
		EASY_CAST( IObj* ,CreateMonsterSpawn( 17.5f, OI_BACTERIA, 1 , n * 2.5f ) ) ->SetPos( D3DXVECTOR3( -30.0f, 0.0f,  90.0f) );
		EASY_CAST( IObj* ,CreateMonsterSpawn( 35.0f, OI_VIRUS, 1 , n * 2.5f  ) ) ->SetPos( D3DXVECTOR3( 30.0f, 0.0f,  90.0f) );
		EASY_CAST( IObj* ,CreateMonsterSpawn( 35.0f, OI_VIRUS, 1 , n * 2.5f ) ) ->SetPos( D3DXVECTOR3( -30.0f, 0.0f,  90.0f) );
	}

}

void		cObjMgr::AllDestroyObject()
{
	for( int n = 0; n < OI_MAX; ++n )
	{
		auto	iter	=	m_listObject[n].begin();
		auto	endit	=	m_listObject[n].end();
		while( iter != endit )
		{
			SAFE_DELETE( *iter );
			iter	=	m_listObject[n].erase( iter );
		}
	}
}

void		cObjMgr::UIChange(char* pKey)
{
	auto button_iter = m_listObject[OI_BUTTON].begin();
	auto button_end_iter = m_listObject[OI_BUTTON].end();

	while( button_iter != button_end_iter )
	{
		static_cast<cButton*>(*button_iter)->SetAniDelete( true );
		++button_iter;
	}

	auto bui_iter = m_listObject[OI_BACKUI].begin();
	auto bui_end_iter = m_listObject[OI_BACKUI].end();

	bool IsbuiStart = false;
	while( bui_iter != bui_end_iter )
	{
		if( !IsbuiStart )
		{
			IsbuiStart = true;
		}
		else
		{
			static_cast<cBackUI*>(*bui_iter)->SetAniDelete( true );
		}
		++bui_iter;
	}

	if( pKey == "button_howto" )
	{
		auto pEffect = ( cBackUI*)
			CreateObject( OI_BACKUI, D3DXVECTOR3( g_nWinSizeX * 0.5f, g_nWinSizeY * 0.5f, 0.0f ), "ui_howto_window" );
		pEffect->SetStartScale( 0.0f );
		pEffect->SetScalingSpeed( 1.5f );
		_GETSINGLE( cSceneMgr )->CreateVirusButton( D3DXVECTOR3( 1200, 303, 0 ), "button_start" );
		_GETSINGLE( cSceneMgr )->CreateVirusButton( D3DXVECTOR3( 1200, 473, 0 ), "button_main" );
	}
	else if( pKey == "button_main" )
	{
		_GETSINGLE( cSceneMgr )->CreateVirusButton( D3DXVECTOR3( 1200, 303, 0 ), "button_start" );
		_GETSINGLE( cSceneMgr )->CreateVirusButton( D3DXVECTOR3( 1200, 473, 0 ), "button_howto" );
		_GETSINGLE( cSceneMgr )->CreateVirusButton( D3DXVECTOR3( 1200, 640, 0 ), "button_about" );

	}
	else if( pKey == "button_about" )
	{
		auto pEffect = ( cBackUI*)
			CreateObject( OI_BACKUI, D3DXVECTOR3( g_nWinSizeX * 0.5f, g_nWinSizeY * 0.5f, 0.0f ), "ui_introduce_window" );
		pEffect->SetStartScale( 0.0f );
		pEffect->SetScalingSpeed( 1.5f );
		_GETSINGLE( cSceneMgr )->CreateVirusButton( D3DXVECTOR3( 1200, 303, 0 ), "button_start" );
		_GETSINGLE( cSceneMgr )->CreateVirusButton( D3DXVECTOR3( 1200, 473, 0 ), "button_main" );

	}
}

void		cObjMgr::CreateBackUiTime( const float& fStartScale, const float& fScaleSpeed,
	const float& fDeleteTime, const D3DXVECTOR3& vPosition, char* pKey )
{
	auto pEffect = ( cBackUI*)
		CreateObject( OI_BACKUI, vPosition, pKey );
	pEffect->SetStartScale( fStartScale );
	pEffect->SetScalingSpeed( fScaleSpeed );
	pEffect->SetDeleteTimer( fDeleteTime );
}