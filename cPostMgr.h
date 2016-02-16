#pragma once

#include "value.h"

class cTexBuf;
class cPostMgr
{
private:
	_SYNTHESIZE_INHER( cTexBuf*, m_pBlurBuffer, BlurBuffer );
	float	m_fBlurClearTime;

public:
	void	Initialize();

	void	Update();
	void	Render();

	void	BeginBulr();
	void	EndBlur();


private:
	void		BlurRender();
public:
	_SINGLETON( cPostMgr );
};

