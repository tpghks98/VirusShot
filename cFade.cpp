#include "DXUT.h"
#include "cFade.h"


cFade::cFade(void)
{
}


cFade::~cFade(void)
{
}

void	cFade::Init()
{
	m_fAlpha = 1.0f;
}
void	cFade::Render()
{
	_GETSINGLE( cResourceMgr )->SetAlpha( m_fAlpha );
	m_pResourceFile->Render( this );
}
void	cFade::Release()
{
}