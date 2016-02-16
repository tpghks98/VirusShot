#include "DXUT.h"
#include "cBaseObject.h"


cBaseObject::cBaseObject(void)
	:m_IsDelete( false )
{
}


cBaseObject::~cBaseObject(void)
{
	DestroyObject();
}



void	cBaseObject::DestroyObject()
{
	m_IsDelete = true;
	if( !m_lstChild.empty() )
	{
		for each( auto iter in m_lstChild )
		{
			iter->DestroyObject();
		}
		m_lstChild.clear();
	}
}