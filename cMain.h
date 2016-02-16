#pragma once

#include "value.h"

class cSystemMgr;
class cObjMgr;
class cPostMgr;
class cSceneMgr;
class cMain
{
private:
	cPostMgr*	m_pPostMgr;
	cSystemMgr*	m_pSystemMgr;
	cObjMgr*	m_pObjMgr;
	cSceneMgr*	m_pSceneMgr;
public:
	void		Init();
	void		Update();
	void		Render();
	void		Release();

private:
	void		LoadResource();


public:
	cMain(void);
	~cMain(void);
};

