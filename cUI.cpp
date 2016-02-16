#include "DXUT.h"
#include "cUI.h"
#include "cTimer.h"

cUI::cUI(void)
	:m_fDelayTime( 0.0f )
	,m_IsAniDelete( false )

{
}


cUI::~cUI(void)
{
}


void	cUI::Update()
{
	this->Translation();
}

void	cUI::SetDeleteTimer( float fTime )
{
	cTimer*	pTimer	=	_GETSINGLE( cSystemMgr )->SetTimer( this, fTime, TT_DELETE, false );

	this->AddChild( (cBaseObject*)pTimer );
}

void	cUI::OnTimer( cTimer* pTimer )
{
	switch( pTimer->nType)
	{
	case TT_DELETE:
		m_IsAniDelete = true;
		break;
	}
}
