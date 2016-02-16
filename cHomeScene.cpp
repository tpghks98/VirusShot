#include "DXUT.h"
#include "cHomeScene.h"
#include "cObjMgr.h"
#include "cSceneMgr.h"
#include "cBackUI.h"
#include "cButton.h"

cHomeScene::cHomeScene(void)
{
}


cHomeScene::~cHomeScene(void)
{
}



void	cHomeScene::Init()
{
	_GETSINGLE( cObjMgr )->CreateObject( OI_BACKUI, D3DXVECTOR3( g_nWinSizeX * 0.5f, g_nWinSizeY * 0.5f, 0.0f ), "ui_main_window" );
		
	_GETSINGLE( cSceneMgr )->CreateVirusButton( D3DXVECTOR3( 1200, 303, 0 ), "button_start" );
	_GETSINGLE( cSceneMgr )->CreateVirusButton( D3DXVECTOR3( 1200, 473, 0 ), "button_howto" );
	_GETSINGLE( cSceneMgr )->CreateVirusButton( D3DXVECTOR3( 1200, 640, 0 ), "button_about" );

}
void	cHomeScene::Update()
{
}
void	cHomeScene::Render()
{
}
void	cHomeScene::Release()
{
}