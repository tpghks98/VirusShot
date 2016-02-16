#include "DXUT.h"
#include "cGeomNode.h"
#include "cBaseShader.h"

cGeomNode::cGeomNode(void)
	:m_pTexMtl( NULL ),
	m_nNumTri( 0 ),
	m_IsRender( true )
{
}


cGeomNode::~cGeomNode(void)
{
	Release();
}


void	cGeomNode::Update( int nKey, D3DXMATRIXA16*	pmatParent )
{
	D3DXMATRIXA16	mT,	mR;
	AnimLocalPos( nKey, mT );
	AnimLocalRot( nKey, mR );

	m_matLocalTM	=	mR	*	mT;

	if( pmatParent )
	{
		m_matWorldTM	=	m_matLocalTM	*	(*pmatParent);
	}
	else
	{
		m_matWorldTM	=	m_matLocalTM;
	}

	for each( auto Child in m_vecChildren )
	{
		Child->Update( nKey, &this->m_matWorldTM );
	}
}

void	cGeomNode::Render( cBaseShader* pShader )
{
	if( m_IsRender )
	{
		if( pShader != NULL )
		{
			pShader->Setting( this );
			auto pEffect	=	pShader->GetEffect();

			UINT	nPass = 0;

			pEffect->Begin( &nPass, 0 );
			{
				for( int n = 0; n < nPass; ++n )
				{
					pEffect->BeginPass( n );
					{
						DrawGeom();
					}
					pEffect->EndPass();
				}
			}
			pEffect->End();
		}
		else
		{
			DrawGeom();
		}
	}

	for each( auto Child in m_vecChildren )
	{
		Child->Render( pShader );
	}

}
void	cGeomNode::DrawGeom()
{
	LPDIRECT3DDEVICE9	pDevice	=	DXUTGetD3D9Device();

	pDevice->SetStreamSource( 0, m_pVB, 0, sizeof( ST_PNT_VERTEX ) );
	pDevice->SetFVF( ST_PNT_VERTEX::FVF );
	if( m_pTexMtl )
	{
		pDevice->SetMaterial( &m_pTexMtl->Mtl );
		pDevice->SetTexture( 0, m_pTexMtl->pTex );
	}

	pDevice->SetTransform( D3DTS_WORLD, &m_matWorldTM );
 	pDevice->DrawPrimitive( D3DPT_TRIANGLELIST, 0, m_nNumTri );
}


void	cGeomNode::Release()
{
	SAFE_RELEASE( m_pVB );
	for each( auto Child in m_vecChildren )
	{
		SAFE_DELETE( Child );
	}
	m_vecChildren.clear();
}

void	cGeomNode::AddChild( cGeomNode* pChild )
{
	m_vecChildren.push_back( pChild );
}

void	cGeomNode::CalcLocalTM( D3DXMATRIXA16*	pmatParentTM )
{
	if( pmatParentTM == NULL )
	{
		m_matLocalTM	=	m_matWorldTM;
	}
	else
	{
		D3DXMATRIXA16	matInvParent;
		D3DXMatrixInverse( &matInvParent, 0, pmatParentTM );
		m_matLocalTM	=	m_matWorldTM	*	matInvParent;
	}

	for each( auto Child in m_vecChildren )
	{
		Child->CalcLocalTM( &this->m_matWorldTM );
	}
}

void	cGeomNode::AnimLocalPos( int nKey, D3DXMATRIXA16&	mT )
{
	D3DXMatrixIdentity( &mT );
	if( m_vecPosTrack.empty() )
	{
		mT._41	=	m_matLocalTM._41;
		mT._42	=	m_matLocalTM._42;
		mT._43	=	m_matLocalTM._43;
	}
	else
	{
		D3DXVECTOR3	v;
		AnimLerp( nKey, v );
		mT._41	=	v.x;
		mT._42	=	v.y;
		mT._43	=	v.z;
	}
}

void	cGeomNode::AnimLocalRot( int nKey, D3DXMATRIXA16&	mR )
{
	D3DXMatrixIdentity( &mR );
	if( m_vecRotTrack.empty() )
	{
		mR	=	m_matLocalTM;
		mR._41	=	0.0f;
		mR._42	=	0.0f;
		mR._43	=	0.0f;
	}
	else
	{
		D3DXQUATERNION	q;
		AnimSLerp( nKey, q );
		D3DXMatrixRotationQuaternion( &mR, &q );
	}
}

void	cGeomNode::AnimLerp( int nKey, D3DXVECTOR3&	v )
{
	if( nKey <= m_vecPosTrack[0].nKey )
	{
		v	=	m_vecPosTrack[0].v;
	}
	else if( nKey >= m_vecPosTrack.back().nKey )
	{
		v	=	m_vecPosTrack.back().v;
	}
	else
	{
		int	nNextIdx	=	0;
		for( int i =0; i < m_vecPosTrack.size(); ++i )
		{
			if( nKey < m_vecPosTrack[i].nKey )
			{
				nNextIdx	=	i;
				break;
			}
		}
		int	nPrevIdx	=	nNextIdx	-	1;

		float	t	=	( nKey - m_vecPosTrack[nPrevIdx].nKey ) / (float)( m_vecPosTrack[nNextIdx].nKey - m_vecPosTrack[nPrevIdx].nKey );
		D3DXVec3Lerp( &v, &m_vecPosTrack[ nPrevIdx ].v, &m_vecPosTrack[ nNextIdx ].v, t );
	}
}


void	cGeomNode::AnimSLerp( int nKey, D3DXQUATERNION&	q )
{
	if( nKey <= m_vecRotTrack[0].nKey )
	{
		q	=	m_vecRotTrack[0].q;
	}
	else if( nKey >= m_vecRotTrack.back().nKey )
	{
		q	=	m_vecRotTrack.back().q;
	}
	else
	{
		int	nNextIdx	=	0;
		for( int i = 0; m_vecRotTrack.size(); ++i )
		{
			if( nKey < m_vecRotTrack[i].nKey )
			{
				nNextIdx	=	i;
				break;
			}
		}
		int	nPrevIdx	=	nNextIdx	-	1;
		float	t	=	( nKey - m_vecRotTrack[ nPrevIdx ].nKey ) / (float)( m_vecRotTrack[ nNextIdx ].nKey - m_vecRotTrack[ nPrevIdx ].nKey );
		D3DXQuaternionSlerp( &q, &m_vecRotTrack[ nPrevIdx ].q,  &m_vecRotTrack[ nNextIdx ].q, t );
	}
}