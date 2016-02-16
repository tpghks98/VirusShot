#pragma once
class cTexBuf
{
protected:
	int		m_nWidth;
	int		m_nHeight;
	int		m_nDepth;

	LPDIRECT3DSURFACE9	m_pOriRenderTarget;
	LPDIRECT3DSURFACE9	m_pOriDepthSurface;

	LPDIRECT3DTEXTURE9	m_pTexture;
	LPDIRECT3DSURFACE9	m_pRenderTarget;
	LPDIRECT3DSURFACE9	m_pDepthSurface;
	
public:
	cTexBuf(void);
	~cTexBuf(void);

	void Create( int nWidthSize, int nHeightSize );
	void Release();

	void	BeginScene();
	void	EndScene();

	LPDIRECT3DTEXTURE9	GetTexture();

};

