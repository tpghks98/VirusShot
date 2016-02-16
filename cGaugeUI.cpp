#include "DXUT.h"
#include "cGaugeUI.h"


cGaugeUI::cGaugeUI(void)
	:m_fGauge( 0.0f )
	,m_fTime( 0.0f )
	,m_fMaxGauge( 0.0f )
{
}


cGaugeUI::~cGaugeUI(void)
{
}
void	cGaugeUI::Init()
{
	m_fMaxGauge = 100.0f;
	m_fTime = 0.0f;
}
void	cGaugeUI::Update()
{

	m_fTime += _GETSINGLE( cSystemMgr )->GetDeltaTime();
	if( m_fTime < m_fDelayTime )
	{
		m_fGauge = 0.0f;
	}
	this->Translation();
}
void	cGaugeUI::Render()
{
	_GETSINGLE( cResourceMgr )->SetScale( m_fGauge / m_fMaxGauge );
	m_pResourceFile->Render( this );
}
void	cGaugeUI::Release()
{
}
void	cGaugeUI::TransmitGauge( float fGauge )
{
	float f = fGauge - m_fGauge;
	if( abs( f ) < 1.0f )
	{
		if( f < 0.0f )
		{
			f = -1.0f;
		}
		else
		{
			f = 1.0f;
		}
	}
	m_fGauge += f * _GETSINGLE( cSystemMgr )->GetDeltaTime() * 2.0f;
}