#include "DXUT.h"
#include "cMain.h"
#include "cSystemMgr.h"
#include "cResourceMgr.h"
#include "cTexBuf.h"
#include "cObjMgr.h"
#include "cPostMgr.h"
#include "cSceneMgr.h"

cMain::cMain(void)
{
}


cMain::~cMain(void)
{
	Release();
}


void	cMain::Init()
{
	srand( GetTickCount() );
	DXUTGetD3D9Device()->SetRenderState( D3DRS_LIGHTING, false );
	DXUTGetD3D9Device()->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );
	DXUTGetD3D9Device()->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA );

	
	LoadResource();
	m_pPostMgr		=	_GETSINGLE( cPostMgr );
	m_pSystemMgr	=	_GETSINGLE( cSystemMgr );
	m_pObjMgr		=	_GETSINGLE( cObjMgr );
	m_pSceneMgr		=	_GETSINGLE( cSceneMgr );

	m_pSceneMgr->Init();
	m_pPostMgr->Initialize();
	m_pSystemMgr->Init();
	m_pObjMgr->Init();


}

void	cMain::Update()
{
	m_pSceneMgr->Update();
	m_pSystemMgr->Update();
	m_pObjMgr->Update();
	m_pPostMgr->Update();

}

void	cMain::Render() 
{
	m_pObjMgr->Render(); 	
	m_pPostMgr->Render();
	m_pSceneMgr->Render();

}

void	cMain::Release()
{
}


void	cMain::LoadResource()
{
	_GETSINGLE( cResourceMgr )->AddAseFile( "player", "Data/Resource/Character/player.ase" );
	_GETSINGLE( cResourceMgr )->AddAseFile( "sub_player", "Data/Resource/Character/qhwh player.ase" );

	_GETSINGLE( cResourceMgr )->AddAseFile( "virus", "Data/Resource/Monster/virus.ase" );
	_GETSINGLE( cResourceMgr )->AddAseFile( "bacteria", "Data/Resource/Monster/bacteria.ase" );
	_GETSINGLE( cResourceMgr )->AddAseFile( "cancer", "Data/Resource/Monster/dka.ase" );
	_GETSINGLE( cResourceMgr )->AddAseFile( "two_cancer", "Data/Resource/Monster/stage2 boss.ase" );
	_GETSINGLE( cResourceMgr )->AddAseFile( "virus_stage2", "Data/Resource/Monster/stage2 virus.ase" );

	
	_GETSINGLE( cResourceMgr )->AddAseFile( "item_hp_heal", "Data/Resource/Item/Item cpfur ghlqhr.ase" );
	_GETSINGLE( cResourceMgr )->AddAseFile( "item_bullet", "Data/Resource/Item/Item dkfdir.ase" );
	_GETSINGLE( cResourceMgr )->AddAseFile( "item_pg_heal", "Data/Resource/Item/Item rhxhd ghlqhr.ase" );
	_GETSINGLE( cResourceMgr )->AddAseFile( "item_guard", "Data/Resource/Item/Item rkem.ase" );

	
	_GETSINGLE( cResourceMgr )->AddAseFile( "bullet_enemy", "Data/Resource/Bullet/wjrchd.ase" );
	_GETSINGLE( cResourceMgr )->AddAseFile( "bullet_pill", "Data/Resource/Bullet/dkfdir.ase" );
	_GETSINGLE( cResourceMgr )->AddAseFile( "redcell", "Data/Resource/Monster/wjrgufrn.ase" );
	_GETSINGLE( cResourceMgr )->AddAseFile( "whitecell", "Data/Resource/Item/qorgufrn.ase" );
	
	
	_GETSINGLE( cResourceMgr )->AddAseFile( "woman", "Data/Resource/Character/1/woman2.ase" );
	_GETSINGLE( cResourceMgr )->AddAseFile( "ground", "Data/Resource/map2.ase" );
	_GETSINGLE( cResourceMgr )->AddAseFile( "ground_stage2", "Data/Resource/Monster/stage2 map.ase" );

	_GETSINGLE( cResourceMgr )->AddAseFile( "t", "Data/Resource/asdf.ase" );
	_GETSINGLE( cResourceMgr )->AddAseFile( "t3", "Data/Resource/T.ase" );
	_GETSINGLE( cResourceMgr )->AddAseFile( "t4", "Data/Resource/dfdf.ase" );
	_GETSINGLE( cResourceMgr )->AddAseFile( "t5", "Data/Resource/Z.ase" );


	_GETSINGLE( cResourceMgr )->AddEffect( "SimpleSample.fx" , SI_TOON );
	_GETSINGLE( cResourceMgr )->AddEffect( "Alpha.fx" , SI_ALPHA );

	_GETSINGLE( cResourceMgr )->AddTexture( "Number", L"Data/Resource/Ui/Num/%d.png", 10 );
	_GETSINGLE( cResourceMgr )->AddTexture( "ui_hp_bar", L"Data/Resource/Ui/hp bar.png");
	_GETSINGLE( cResourceMgr )->AddTexture( "ui_pg_bar", L"Data/Resource/Ui/pg bar.png");
	_GETSINGLE( cResourceMgr )->AddTexture( "ui_window", L"Data/Resource/Ui/ui.PNG");
	_GETSINGLE( cResourceMgr )->AddTexture( "ui_black_background", L"Data/Resource/Ui/background_black.png");


	_GETSINGLE( cResourceMgr )->AddTexture( "ui_boss", L"Data/Resource/Ui/ui_boss.PNG");
	_GETSINGLE( cResourceMgr )->AddTexture( "ui_gameclear", L"Data/Resource/Ui/ui_gameclear.PNG");
	_GETSINGLE( cResourceMgr )->AddTexture( "ui_stage1", L"Data/Resource/Ui/ui_stage1.PNG");
	_GETSINGLE( cResourceMgr )->AddTexture( "ui_stage2", L"Data/Resource/Ui/ui_stage2.PNG");

	_GETSINGLE( cResourceMgr )->AddTexture( "ui_howto_window", L"Data/Resource/Home/UI/howto_background.PNG");
	_GETSINGLE( cResourceMgr )->AddTexture( "ui_main_window", L"Data/Resource/Home/UI/background.PNG");
	_GETSINGLE( cResourceMgr )->AddTexture( "ui_introduce_window", L"Data/Resource/Home/UI/Introduce_background.PNG");
	
	_GETSINGLE( cResourceMgr )->AddTexture( "button_about", L"Data/Resource/Home/UI/button/button_about%d.PNG" , 3);
	_GETSINGLE( cResourceMgr )->AddTexture( "button_howto", L"Data/Resource/Home/UI/button/button_howto%d.PNG" , 3);
	_GETSINGLE( cResourceMgr )->AddTexture( "button_start", L"Data/Resource/Home/UI/button/button_start%d.PNG" , 3);
	_GETSINGLE( cResourceMgr )->AddTexture( "button_main", L"Data/Resource/Home/UI/button/button_main%d.PNG" , 3);


	
	_GETSINGLE( cResourceMgr )->AddImage( "wind_effect", "Data/Resource/Effect/wind_effect/wind%d.png", 2, false );

	_GETSINGLE( cResourceMgr )->AddImage( "power_effect", "Data/Resource/Effect/power_effect/%d.tga", 8, false );
	_GETSINGLE( cResourceMgr )->AddImage( "hit_effect", "Data/Resource/Effect/bomb_effect/%d.tga", 5, true );
	_GETSINGLE( cResourceMgr )->AddImage( "bomb_effect", "Data/Resource/Effect/bomb_effect/%d.tga", 5, true );

}