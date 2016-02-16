#pragma	once

struct	CUSTOM_POINT
	:public	POINT
{

	CUSTOM_POINT()
	{
		this->x	=	0;
		this->y	=	0;
	}

	CUSTOM_POINT( UINT32 x, UINT32 y )
	{
		this->x	=	x;
		this->y	=	y;
	}

	CUSTOM_POINT( const POINT& pt )
	{
		this->x	=	pt.x;
		this->y	=	pt.y;
	}

	CUSTOM_POINT CUSTOM_POINT::operator-( const CUSTOM_POINT& pt ) const
	{
		return CUSTOM_POINT( this->x - pt.x, this->y - pt.y );
	}
};

struct	ST_PNT_VERTEX
{
	D3DXVECTOR3	p;
	D3DXVECTOR3	n;
	D3DXVECTOR2	t;

	enum	{ FVF	=	D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1 };
};

struct	ST_MTL_TEX
{
	LPDIRECT3DTEXTURE9	pTex;
	D3DMATERIAL9		Mtl;

	ST_MTL_TEX()
		:pTex( NULL )
	{
		ZeroMemory( &Mtl, sizeof( D3DMATERIAL9 ) );
	}
};

struct	ST_POS_TRACK
{
	int	nKey;
	D3DXVECTOR3	v;
};

struct	ST_ROT_TRACK
{
	int	nKey;
	D3DXQUATERNION	q;
};

