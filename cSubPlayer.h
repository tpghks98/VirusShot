#pragma once
#include "cplayer.h"
class cSubPlayer :
	public cPlayer
{
public:
	virtual	void	Init();
	virtual	void	Update();
	virtual	void	Render();
	virtual	void	Release();

	virtual	void	Translation()
	{
		D3DXMATRIXA16	matTrans,	matRotation,	matScale;

		{
			D3DXMatrixTranslation( &matTrans, m_vPos.x, m_vPos.y, m_vPos.z );
			D3DXMatrixRotationYawPitchRoll( &matRotation, m_vRotation.y, m_vRotation.x, m_vRotation.z );
			D3DXMatrixScaling( &matScale, m_vScale.x, m_vScale.y, m_vScale.z );
			D3DXMatrixRotationQuaternion( &m_matLookAt, &m_quatLookAt );
		}
		m_matWorld	=	matScale	*	matRotation * m_matLookAt	*	matTrans *
			(*_GETSINGLE( cObjMgr )->m_pPlayer->GetMatrixPointer());

	}
public:
	cSubPlayer(void);
	~cSubPlayer(void);
};

