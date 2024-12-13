#pragma once

class D2DRenderer;

/// <summary>
/// ����Ʈ�� ����ϴ� Ŭ���� 
/// 
/// ��ȯ���ִ� ��Ʈ���� ����ڰ� ���� Release�ؾ��Ѵ�
/// ComPtr�� ����ұ�?
///  
/// 2023.7.20 22:41 gitae
/// </summary>
class D2DEffectFactory
{
public:
	D2DEffectFactory() = default;
	~D2DEffectFactory();

	void Initalize(ID2D1DeviceContext* _deviceContext, D2DRenderer* _renderer);
	void Finalize();
	// 
	ID2D1Bitmap* Luminance(ID2D1Bitmap* _orgin);

	ID2D1Bitmap* Cromakey(ID2D1Bitmap* _orgin);

	// ��� ȿ�� 
	ID2D1Bitmap* BloomEffect(ID2D1Bitmap* _orgin);

	// �̹����� ��Ʈ������ �ٲ��ִ� �Լ�
	ID2D1Bitmap* ConvertImageToBitmap(ID2D1Image** _orgin, D2D1_SIZE_U size);

	ID2D1Bitmap* EdgeDetection(ID2D1Bitmap* _orgin);

	// RGB ���� �����ϴ� �Լ�
	ID2D1Bitmap* ExtractColor(ID2D1Bitmap* _orgin, EXTRACT_COLOR _color, float _ratio);

	// ���� �Լ�
	ID2D1Bitmap* Blend(ID2D1Bitmap* _source, ID2D1Bitmap* _destination, D2D1_BLEND_MODE _mode);

	ID2D1Bitmap* PointDiffuse(ID2D1Bitmap* _origin);

	ID2D1Image* PointDiffuseImage(ID2D1Bitmap* _origin, float _intensity, D2D1_VECTOR_3F _rgb);

	// ����Ʈ����Ʈ ȿ��
	ID2D1Image* SpotLightImage(ID2D1Bitmap* _origin
		, D2D1_VECTOR_3F _lightPosition
		, D2D1_VECTOR_3F _pointAt
		, float _focus,float _limitConeAngle
		, float _diffuse, D2D1_VECTOR_3F _color);

	// ���� ���ĸ���ũ ȿ��
	ID2D1Image* AlphaMask(ID2D1Image* _orgin, ID2D1Bitmap* _alhpaMap);
private:
	// ����Ʈ Ȯ�� ����ȿ��
	ID2D1Effect* m_pointDiffuse;

	// ����Ʈ����Ʈ ȿ��
	ID2D1Effect* m_spotDiffuse;

	// �÷� ��Ʈ���� ȿ��
	ID2D1Effect* m_colorMatrix;

	ID2D1Effect* m_alphaMask;

	// ����þ� ��
	ID2D1Effect* m_gaussianBlur;

	// ũ�θ�Ű ȿ�� 
	ID2D1Effect* m_chromakey;

	// ���� 
	ID2D1Effect* m_opacity;
	
	// ������
	ID2D1Effect* m_flood;

	// ���� �� �𸣰���
	ID2D1Effect* m_luminanceToAlpha;
	
	// �����ڸ� ����
	ID2D1Effect* m_edgeDetection;

	// �������� ȿ������ �ռ�
	ID2D1Effect* m_compositeEffect;

	// ���� ���� 
	ID2D1Effect* m_blend;

	D2DRenderer* m_d2DRenderer;
	ID2D1DeviceContext* m_memDC;
	ID2D1DeviceContext* m_deviceContext;
};
