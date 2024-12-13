#pragma once

#include "D2DEffectFactory.h"

class D2DTexture;
class D2DCamera;

/// <summary>
/// D2D�������� ����Ѵ�
/// 
/// </summary>
class D2DRenderer
{
public:
	D2DRenderer();
	~D2DRenderer();

	void Initalize(HWND _hwnd);
	void Finalize();

	void BeginRender();
	void EndRender();

public:
	// ȭ�鿡 ������Ʈ�� ī�޶� ������ �޴��� Ȯ���ϴ� �Լ�
	void SetCameraAffected(bool _isAffected);

	// ����Ÿ�� ���������� �ʱ�ȭ�ϴ� �Լ�
	void ClearRenderTarget();
	  
	Vector2 GetBitmapSize(const wstring& _name);

public:
	/// �׸��� ���� �Լ���

	// ������ �׸��� �Լ�
	void DrawLine(Vector2 _point1, Vector2 _point2
		, ColorF = D2D1::ColorF::White);

	void DrawEllipse(Vector2 _point, Vector2 _radius
		, ColorF = D2D1::ColorF::White);

	void DrawEllipse(Vector2 _point, float _radius,
		ColorF color = D2D1::ColorF::White);

	void DrawFillElipse(Vector2 _point, Vector2 _scale
		, ColorF _color = D2D1::ColorF::White);

	// �簢�� �׸��� �Լ�
	void DrawRectangle(Vector2 _leftTop, Vector2 _rightBottom
		, ColorF color = D2D1::ColorF::White, float _rotation = 0.f);

	// ���θ� ä��� �簢�� �׸���
	void DrawFillRectangle(Vector2 _position, Vector2 _scale
		, ColorF color = D2D1::ColorF(ColorF::White,1.f), float _rotation = 0.f);

	void DrawFillRectangle2(Vector2 _leftTop, Vector2 _rightBottom
		, ColorF color = ColorF(ColorF::WhiteSmoke),float _rotation = 0.f);

	// �ؽ�Ʈ ����Լ� 
	void DrawTextW(const std::wstring& _str, Vector2 _leftTop
		, Vector2 _rightBottom, ColorF _color = D2D1::ColorF::White
	    , FONT_TYPE _type = FONT_TYPE::DEFALUT );


public:
	D2DTexture* LoadBitmap(const wstring& _key, const wchar_t* _filePath);

	void DrawBitmap(const wstring& _key, Vector2 _position
		, float _rotation = 0.f, float _alpha = 1.f, FLIP_TYPE _type = FLIP_TYPE::NONE
		, Vector2 _scale = Vector2::One);

	// �ؽ�ó�� �߶� ������
	void DrawBitmap(const wstring& _key, Vector2 _position
		, Vector2 _textureLeftTop, Vector2 _sliceSize
		, float _rotation = 0.f, float _alpha = 1.f, FLIP_TYPE _type = FLIP_TYPE::NONE);

	void DrawFreezeBitmap(const wstring& _key, Vector2 _position
		, Vector2 _textureLeftTop, Vector2 _sliceSize , float _ratio
		, float _rotation = 0.f, float _alpha = 1.f, FLIP_TYPE _type = FLIP_TYPE::NONE);
	
	/// ����Ʈ ���� �Լ�
	void DrawPointLight(Vector2 _position, float _intensity, D2D1_VECTOR_3F _rgb, Vector2 _scale, float _angle);

	// ������ ��Ʈ���� ����Ѵ�.
	void DrawBlendBitmap(const wstring& _sourceKey
		, const wstring& _destination
		, D2D1_BLEND_MODE _mode
		, Vector2 _position
		, float _rotation
		, float _alpha = 1.f);

	// Bloom Effect�� �Բ� ��Ʈ���� �׸���.
	void DrawBitmapBloom(const wstring& _key, Vector2 _position
		, float _rotation = 0.f, float _alpha = 1.f);

	void DrawBitmapExtractColor(const wstring& _key, Vector2 _position
		, EXTRACT_COLOR _color, float _rotation = 0.f, float _alpha = 1.f);

	// ����Ʈ����Ʈ ���� �׸��� 
	void DrawSpotLight();

	/// <summary>
	/// </summary>
	/// RBG Transition�� �����ϴ� �Լ� 
	/// <param name="_key"></param>
	/// <param name="_position"></param>
	/// <param name="_rgbOffset">RGB������� �����¿� �־ �����Ѵ�</param>
	void DrawRGBTransition(const wstring& _key, Vector2 _position
		, const std::vector<Vector2>& _rgbOffset);

	/// ī�޶� ����
	D2DCamera* GetCamera()const { return m_camera; }

private:
	HRESULT LoadBitmapFromFile(PCWSTR _filePath
		, UINT _destinationWidth, UINT _destinationHeight, ID2D1Bitmap** _bitmap);

private:
	/// ����Ÿ���� ����� �Լ�
	HRESULT CreateDeviceResources();
	void DiscardDeviceResources();

private:
	void SetTransform(float _radian, Vector2 _point);
	// �⺻ ��ķ� ��ȯ
	void SetTransform() { m_deviceContext->SetTransform(m_finalMatrix); }

	void SetFlip(FLIP_TYPE _type, Vector2 _position);
private:
	D2D1_MATRIX_3X2_F m_screenMatrix; // ��ũ�� ��ǥ��� ��ȯ�ϴ� ���
	D2D1_MATRIX_3X2_F m_finalMatrix;

	HWND m_hwnd; // ���� ������ �ڵ�
	ID2D1Factory1* m_factory; // ���丮
	IDWriteFactory* m_writeFactory; // ���� ���� ���丮

	IDWriteTextFormat* m_textFormat[static_cast<int>(FONT_TYPE::END)]; // �ؽ�Ʈ ����

	ID2D1SolidColorBrush* m_tempBrush; // ��� ����ϴ� �뵵

	ID2D1DeviceContext* m_deviceContext; // ����Ÿ��
	D3D_FEATURE_LEVEL m_featureLevel; 
	ID2D1Device* m_device; // D2D Deivice;
	IDXGISwapChain1* m_swapChain; // ����ü��
	ID2D1CommandList* m_commandList; 

	ID2D1Bitmap1* m_memoryBitamap; 
	ID2D1Bitmap1* m_copyBitmap;

 	float m_dpi;

private:
	// ����̽� �������� �ڿ����� �غ�Ǿ��°�?
	HRESULT m_IsD2DResReady;
	D2D1_SIZE_F m_renderTargetSize;

private:
	bool m_cameraAffected;

	/// ��Ʈ�� ���� 
	IWICImagingFactory* m_imagingFactorty;

	/// �ؽ�ó�� �����ϴ� ����
	map<wstring, D2DTexture*> m_textures; 

	/// ī�޶� ����
	D2DCamera* m_camera;

	/// ����Ʈ 
	D2DEffectFactory* m_effectFactory ;

	// SetTransform�� ����ϱ����� friend ����
	friend ID2D1Bitmap* D2DEffectFactory::ConvertImageToBitmap(ID2D1Image** _orgin, D2D1_SIZE_U size);
};

