#include "DXUT.h"
#include "cSmooth.h"


cSmooth::cSmooth(void)
	:IsOn( false ),
	pTarget( NULL ),
	fStart( 0.0f ),
	fEnd( 0.0f ),
	fSpeed( 0.0f ),
	fElap( 0.0f )
{
}


cSmooth::~cSmooth(void)
{
}


void	cSmooth::Update()
{
	if( IsOn )
	{
		fElap += _GETSINGLE( cSystemMgr )->GetDeltaTime() * ( sin( 1.0f - fElap ) * 3.0f * fSpeed + 0.2f );
		if(  fElap >= 0.99f )
		{
			fElap  = 1.0f;
			IsOn = false;
		}
		(*pTarget) =  fStart + (fEnd - fStart ) * fElap;
	}
}

void	cSmooth::Init()
{
}
void	cSmooth::Render()
{
}

void	cSmooth::Release()
{
}