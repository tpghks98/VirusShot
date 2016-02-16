#include "DXUT.h"
#include "cTimer.h"


cTimer::cTimer(void)
{
}


cTimer::~cTimer(void)
{
}

void	cTimer::Init()
{
}

void	cTimer::Render()
{
}

void	cTimer::Release()
{
}


void cTimer::Update()
{
	if( IsOn )
	{
		fElapTime += _GETSINGLE( cSystemMgr )->GetDeltaTime();
		if( fCoolTime <= fElapTime )
		{
			pOwner->OnTimer( this );
			if( IsRepeat )
			{
				fElapTime = 0.0f;
			}
			else
			{
				IsOn = false;
			}
		}
	}
}