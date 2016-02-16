#include "DXUT.h"
#include "cPlayScene.h"
#include "cObjMgr.h"

cPlayScene::cPlayScene(void)
{
}


cPlayScene::~cPlayScene(void)
{
}

void	cPlayScene::Init()
{
	_GETSINGLE( cObjMgr )->GameStart();
}
void	cPlayScene::Update()
{
}
void	cPlayScene::Render()
{
}
void	cPlayScene::Release()
{
}