#pragma once
#include "ccharacter.h"
class cMonsterSpawn :
	public cCharacter
{
private:
	_SYNTHESIZE_INHER( int, m_nGenTargetType, TargetType );
	_SYNTHESIZE_INHER( int, m_nMonsterCount, MonsterCount );


public:
	virtual	void	Init();
	virtual	void	Update();
	virtual	void	Render();
	virtual	void	Release();

	void	SetupGenTimer( float fCool, float fImmediatelyTime = 0.0f );

	virtual void	OnTimer( cTimer* pTimer ) override;
public:
	cMonsterSpawn(void);
	~cMonsterSpawn(void);
};

