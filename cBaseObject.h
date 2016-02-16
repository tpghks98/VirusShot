#pragma once

#include "value.h"

interface cBaseObject
{
protected:
	std::list<cBaseObject*>	m_lstChild;
	std::list<cBaseObject*> m_lstParent;

public:
	_SYNTHESIZE_INHER( bool, m_IsDelete, Delete );

public:
	void	AddChild( cBaseObject*	pBase ) { m_lstChild.push_back( pBase ); pBase->AddParent( this );	}
	void	AddParent( cBaseObject* pBase ) { m_lstParent.push_back( pBase ); }
public:
	void	DestroyObject();

public:
	virtual	void	Init()		PURE;
	virtual	void	Update()	PURE;
	virtual	void	Render()	PURE;
	virtual	void	Release()	PURE;
public:
	cBaseObject(void);
	virtual ~cBaseObject(void);
};

