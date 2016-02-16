#pragma once
#include "cui.h"
class cGaugeUI :
	public cUI
{
private:
	_SYNTHESIZE_REF_INHER( float, m_fTime, Time );
	_SYNTHESIZE_REF_INHER( float, m_fGauge, Gauge );
	_SYNTHESIZE_REF_INHER( float, m_fMaxGauge, MaxGauge );
public:
	virtual	void	Init();
	virtual	void	Update();
	virtual	void	Render();
	virtual	void	Release();
	
	void	TransmitGauge( float fGauge );
public:
	cGaugeUI(void);
	~cGaugeUI(void);
};

