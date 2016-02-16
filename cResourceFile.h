#pragma once

#include "value.h"

class cBaseShader;

class IObj;
class cResourceFile
{
public:

	_SYNTHESIZE_INHER( char*, m_pKey, Key );
public:
	virtual	void	Render( IObj* pObj, bool IsAni = false,
		cBaseShader* pShader = NULL )	PURE;	
	
public:
	cResourceFile(void);
	virtual ~cResourceFile(void);
};

