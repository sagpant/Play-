#pragma once

#include "../DirectXControl.h"
#include "bitmap/Bitmap.h"
#include "PixelBufferViewOverlay.h"
#include <memory>
#include <vector>

class CPixelBufferView : public CDirectXControl
{
public:
	typedef std::pair<std::string, Framework::CBitmap> PixelBuffer;
	typedef std::vector<PixelBuffer> PixelBufferArray;

							CPixelBufferView(HWND, const RECT&);
	virtual					~CPixelBufferView() = default;

	void					SetPixelBuffers(PixelBufferArray);

	void					FitBitmap();

protected:
	void					Refresh() override;

	long					OnCommand(unsigned short, unsigned short, HWND) override;
	long					OnSize(unsigned int, unsigned int, unsigned int) override;

	long					OnLeftButtonDown(int, int) override;
	long					OnLeftButtonUp(int, int) override;

	long					OnMouseMove(WPARAM, int, int) override;

	long					OnMouseWheel(int, int, short) override;

	void					OnDeviceReset() override;
	void					OnDeviceResetting() override;

private:
	typedef Framework::Win32::CComPtr<IDirect3DTexture9> TexturePtr;
	typedef Framework::Win32::CComPtr<IDirect3DVertexBuffer9> VertexBufferPtr;
	typedef Framework::Win32::CComPtr<IDirect3DVertexDeclaration9> VertexDeclarationPtr;
	typedef Framework::Win32::CComPtr<ID3DXEffect> EffectPtr;

	struct VERTEX
	{
		float	position[3];
		float	texCoord[2];
	};

	const PixelBuffer*		GetSelectedPixelBuffer();
	void					CreateSelectedPixelBufferTexture();

	void						OnSaveBitmap();
	static Framework::CBitmap	ConvertBGRToRGB(Framework::CBitmap);

	void					CreateResources();
	void					DrawCheckerboard();
	void					DrawPixelBuffer();

	EffectPtr				CreateEffectFromResource(const TCHAR*);
	TexturePtr				CreateTextureFromBitmap(const Framework::CBitmap&);
	void					SetEffectVector(EffectPtr&, const char*, float, float, float, float);

	TexturePtr				m_pixelBufferTexture;
	PixelBufferArray		m_pixelBuffers;
	VertexDeclarationPtr	m_quadVertexDecl;
	VertexBufferPtr			m_quadVertexBuffer;
	EffectPtr				m_checkerboardEffect;
	EffectPtr				m_pixelBufferViewEffect;

	std::unique_ptr<CPixelBufferViewOverlay>	m_overlay;

	float					m_panX;
	float					m_panY;
	float					m_zoomFactor;

	bool					m_dragging;
	int						m_dragBaseX;
	int						m_dragBaseY;

	float					m_panXDragBase;
	float					m_panYDragBase;
};
