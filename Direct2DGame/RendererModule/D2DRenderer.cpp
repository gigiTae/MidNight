#include "RendererPCH.h"
#include "D2DRenderer.h"
#include "macro.h"
#include "D2DTexture.h"
#include "D2DEffectFactory.h"
#include "D2DCamera.h"

D2DRenderer::D2DRenderer()
	:m_hwnd(nullptr)
	,m_factory(nullptr)
	,m_IsD2DResReady(S_FALSE)
	,m_renderTargetSize{}
	,m_tempBrush(nullptr)
	,m_screenMatrix{}
	,m_camera(nullptr)
	,m_writeFactory(nullptr)
	,m_textFormat{}
	,m_imagingFactorty(nullptr)
	,m_finalMatrix{}
	,m_cameraAffected(true)
	,m_device(nullptr)
	,m_deviceContext(nullptr)
	,m_dpi(0.f)
	,m_memoryBitamap(nullptr)
	,m_featureLevel{}
	,m_swapChain(nullptr)
	,m_effectFactory(nullptr)
{
}

D2DRenderer::~D2DRenderer()
{
}


void D2DRenderer::Initalize(HWND _hwnd)
{
	// ���� ������ �ڵ� ����
	m_hwnd = _hwnd;

	HRESULT hr = S_OK;

	// Direct2D ���ҽ��� ����µ� ����� �� �ִ� ���͸� ��ü����
	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED
		, &m_factory);
	assert(hr == S_OK);

	/// WIC���丮 ����
	if (SUCCEEDED(hr))
	{
		hr = CoCreateInstance(
			CLSID_WICImagingFactory,
			NULL,
			CLSCTX_INPROC_SERVER,
			IID_IWICImagingFactory,
			reinterpret_cast<void**>(&m_imagingFactorty)
		);
	}

	// �������� ���丮 ����
	if (SUCCEEDED(hr))
	{
		hr = DWriteCreateFactory(
			DWRITE_FACTORY_TYPE_SHARED
			, __uuidof(m_writeFactory)
			, reinterpret_cast<IUnknown**>(&m_writeFactory)
		);
	}

	if (SUCCEEDED(hr))
	{
		// default ��Ʈ ����
		hr = m_writeFactory->CreateTextFormat(
			L"����",
			NULL,
			DWRITE_FONT_WEIGHT_SEMI_BOLD,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_NORMAL,
			15,
			L"", //locale
			&m_textFormat[static_cast<int>(FONT_TYPE::DEFALUT)]
		);

		// ��ǳ�� ��Ʈ ����
		hr = m_writeFactory->CreateTextFormat(
			L"����",
			NULL,
			DWRITE_FONT_WEIGHT_EXTRA_BOLD,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_NORMAL,
			55,
			L"", //locale
			&m_textFormat[static_cast<int>(FONT_TYPE::SPEECH_BUBBLE)]
		);

			const std::wstring& path = L"BMJUA.ttf";
		AddFontResource(path.c_str());
		::SendMessage(HWND_BROADCAST, WM_FONTCHANGE, NULL, NULL);

		hr = m_writeFactory->CreateTextFormat(
			L"����ǹ��� �־�",	
			NULL,
			DWRITE_FONT_WEIGHT_NORMAL,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_NORMAL,
			35,
			L"", //locale
			&m_textFormat[static_cast<int>(FONT_TYPE::TALK)]
		);

	}

	// �ؽ�Ʈ ���� ���
 	if (SUCCEEDED(hr))
	{
		// Left-Top the text horizontally and vertically.
		m_textFormat[static_cast<int>(FONT_TYPE::DEFALUT)]->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
		m_textFormat[static_cast<int>(FONT_TYPE::DEFALUT)]->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);

		m_textFormat[static_cast<int>(FONT_TYPE::SPEECH_BUBBLE)]->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
		m_textFormat[static_cast<int>(FONT_TYPE::SPEECH_BUBBLE)]->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);

		m_textFormat[static_cast<int>(FONT_TYPE::TALK)]->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
		m_textFormat[static_cast<int>(FONT_TYPE::TALK)]->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
	}

	hr = CreateDeviceResources();
	assert(hr == S_OK);

	if (SUCCEEDED(hr))
	{
		// Ŀ�ǵ� ����Ʈ����
		m_deviceContext->CreateCommandList(&m_commandList);
	}
	

	m_renderTargetSize = m_deviceContext->GetSize();

	/// ������ ������ �߾���ǥ�� �̵��ϴ� ���
	Vector2 translation{m_renderTargetSize.width * 0.5f, m_renderTargetSize.height * 0.5f };
	Matrix3x2F transformMatrix = Matrix3x2F::Translation(translation.x, translation.y);

	/// ��ũ�� ��� 
	m_screenMatrix = transformMatrix;

	/// ī�޶� ����
	m_camera = new D2DCamera();
	m_camera->ResetCamera(Vector2(m_renderTargetSize.width,m_renderTargetSize.height));

	/// ����Ʈ ����
	m_effectFactory = new D2DEffectFactory;
	m_effectFactory->Initalize(m_deviceContext,this);


}

void D2DRenderer::BeginRender()
{
	m_IsD2DResReady = CreateDeviceResources();

	// ����̽� ������ �ڿ����� ���� ����, �������� �� �� �ִ� ��Ȳ�� �� 
	if(SUCCEEDED(m_IsD2DResReady))
	{
		m_renderTargetSize = m_deviceContext->GetSize();

		m_deviceContext->BeginDraw();

		/// ���� ��� ���
		D2D1_MATRIX_3X2_F cameraMatix = m_camera->GetCameraMatrix();
		m_finalMatrix = cameraMatix * m_screenMatrix;

		m_deviceContext->SetTransform(m_finalMatrix);

		m_deviceContext->Clear(D2D1::ColorF(D2D1::ColorF::Black));
	}
}

void D2DRenderer::EndRender()
{

	if (SUCCEEDED(m_IsD2DResReady))	
	{
		HRESULT hr = m_deviceContext->EndDraw();

		DXGI_PRESENT_PARAMETERS parameters{};
		parameters.DirtyRectsCount = 0;
		parameters.pDirtyRects = nullptr;
		parameters.pScrollOffset = nullptr;
		parameters.pScrollRect = nullptr;

		m_swapChain->Present1(0, 0, &parameters);
		//m_swapChain->Present1(0, 0, &parameters); ->ȭ�� �ֻ��� ���� �����ϰ� ������ �Ʒ��� ���

		//������ �� �ִ� ���������̼� ������ �ֽ��ϴ�. ȣ���ڴ� �ٽ� �����
		//��ü �������� �ٽ� �������ϰ�, ���縦 �ٽ� �õ��ؾ� �մϴ�.
		if (hr == D2DERR_RECREATE_TARGET)
		{
			hr = S_OK;
			DiscardDeviceResources();
		}
	}
}

void D2DRenderer::SetCameraAffected(bool _isAffected)
{
	if (m_cameraAffected != _isAffected)
	{
		m_cameraAffected = _isAffected;

		// ī�޶� ������ �޴� ���
		if (m_cameraAffected)
		{
			m_finalMatrix = m_camera->GetCameraMatrix() * m_screenMatrix;
		}
		else // ���� �ʴ� ���
		{
			m_finalMatrix = m_screenMatrix;
		}

		SetTransform();
	}
}

void D2DRenderer::ClearRenderTarget()
{
	m_deviceContext->Clear(D2D1::ColorF(D2D1::ColorF::Black));
}


Vector2 D2DRenderer::GetBitmapSize(const wstring& _name)
{
	auto iter = m_textures.find(_name);
	assert(iter != m_textures.end());

	return iter->second->GetSize();
}

void D2DRenderer::Finalize()
{
	/// ���ҽ� �޸� ����
	for (auto iter = m_textures.begin(); iter != m_textures.end(); ++iter)
	{
		if (iter->second != nullptr)
		{
			delete iter->second;
		}
	}

	SafeRelease(&m_memoryBitamap);
	SafeRelease(&m_writeFactory);
	
	SafeRelease(&m_imagingFactorty);
	SafeRelease(&m_deviceContext);
	SafeRelease(&m_factory);

	// ��Ʈ ����
	for (int i = 0; i < static_cast<int>(FONT_TYPE::END); ++i)
	{
		SafeRelease(&m_textFormat[i]);
	}

	// ��Ʈ ����
	const std::wstring& path = L"BMJUA.ttf";
	RemoveFontResource(path.c_str());
	::SendMessage(HWND_BROADCAST, WM_FONTCHANGE, NULL, NULL);

	// ī�޶� ����
	if (m_camera != nullptr)
		delete m_camera;

	m_effectFactory->Finalize();
	delete m_effectFactory;

	//���� �����忡�� COM ���̺귯���� �ݰ�, �����忡 ���� �ε�� ��� DLL�� ��ε��ϰ�
	//, �����尡 ���� �����ϴ� �ٸ� ��� ���ҽ��� �����ϰ�, �������� ��� RPC ������ ������ �ݽ��ϴ�.
	CoUninitialize();
}

void D2DRenderer::SetTransform(float _radian, Vector2 _point)
{
	/// radian�� �����Ҽ��� �ݽð�������� ȸ���Ѵ�
	float angle = -FMath::RadToDeg(_radian);

	// ��ĺ�ȯ
	D2D1_MATRIX_3X2_F matrix = D2D1::Matrix3x2F::Rotation(angle, _point.ToPoint2F());
	
	matrix = matrix * m_finalMatrix;

	m_deviceContext->SetTransform(matrix);
}

void D2DRenderer::SetFlip(FLIP_TYPE _type, Vector2 _position)
{
	Matrix3x2F mat{};
	
	switch (_type)
	{
	case FLIP_TYPE::NONE:
		return;
		break;
	case FLIP_TYPE::X_FLIP:
	{
		mat = Matrix3x2F::Scale(D2D1_SIZE_F{ -1.f,1.f }, _position.ToPoint2F());
	}
		break;
	case FLIP_TYPE::Y_FLIP:
	{
		mat = Matrix3x2F::Scale(D2D1_SIZE_F{ 1.f,-1.f }, _position.ToPoint2F());
	}
		break;
	case FLIP_TYPE::XY_FLIP:
	{
		mat = Matrix3x2F::Scale(D2D1_SIZE_F{ -1.f,-1.f }, _position.ToPoint2F());
	}
		break;
	default:
		break;
	}

	m_deviceContext->SetTransform(mat * m_finalMatrix);
}

void D2DRenderer::DrawLine(Vector2 _point1, Vector2 _point2, ColorF color)
{
	Vector2 point1 = _point1.ChangeYSign();
	Vector2 point2 = _point2.ChangeYSign();

	D2D1_POINT_2F start = point1.ToPoint2F();
	D2D1_POINT_2F end = point2.ToPoint2F();

	m_deviceContext->CreateSolidColorBrush(color, &m_tempBrush);
	assert(m_tempBrush);

	m_deviceContext->DrawLine(start, end, m_tempBrush, 1.0f);	

	SafeRelease(&m_tempBrush);
}

void D2DRenderer::DrawEllipse(Vector2 _point , Vector2 _scale, ColorF color)
{
	Vector2 point = _point.ChangeYSign();

	D2D1_ELLIPSE region{};
	region.point = point.ToPoint2F();
	region.radiusX = _scale.x * 0.5f;
	region.radiusY = _scale.y * 0.5f;

	m_deviceContext->CreateSolidColorBrush(D2D1::ColorF(color), &m_tempBrush);
	assert(m_tempBrush);

	m_deviceContext->DrawEllipse(region, m_tempBrush,1.f);

	SafeRelease(&m_tempBrush);
}

void D2DRenderer::DrawEllipse(Vector2 _point, float _radius, ColorF color)
{
	Vector2 point = _point.ChangeYSign();

	D2D1_ELLIPSE region{};
	region.point = point.ToPoint2F();
	region.radiusX = _radius;
	region.radiusY = _radius;

	m_deviceContext->CreateSolidColorBrush(D2D1::ColorF(color), &m_tempBrush);
	assert(m_tempBrush);

	m_deviceContext->DrawEllipse(region, m_tempBrush, 2.f);

	SafeRelease(&m_tempBrush);
}

void D2DRenderer::DrawFillElipse(Vector2 _point, Vector2 _scale, ColorF _color /*= D2D1::ColorF::White*/)
{
	Vector2 point = _point.ChangeYSign();

	D2D1_ELLIPSE region{};
	region.point = point.ToPoint2F();
	region.radiusX = _scale.x * 0.5f;
	region.radiusY = _scale.y * 0.5f;

	m_deviceContext->CreateSolidColorBrush(_color, &m_tempBrush);
	assert(m_tempBrush)	;

	m_deviceContext->FillEllipse(&region, m_tempBrush);

	SafeRelease(&m_tempBrush);
}

void D2DRenderer::DrawRectangle(Vector2 _leftTop
	, Vector2 _rightBottom, ColorF color,float _rotation)
{
	Vector2 leftTop = _leftTop.ChangeYSign();
	Vector2 rightBottom = _rightBottom.ChangeYSign();

	D2D1_RECT_F rt{};
	rt.left = leftTop.x;
	rt.top = leftTop.y;
	rt.right = rightBottom.x;
	rt.bottom = rightBottom.y;	

	m_deviceContext->CreateSolidColorBrush(color, &m_tempBrush);
	assert(m_tempBrush);

	Vector2 middle((rightBottom.x + leftTop.x) * 0.5f, (leftTop.y + rightBottom.y) * 0.5f);
	SetTransform(_rotation, middle);

	m_deviceContext->DrawRectangle(rt, m_tempBrush, 2.f);

	SetTransform();

	SafeRelease(&m_tempBrush);
}


void D2DRenderer::DrawFillRectangle(Vector2 _position, Vector2 _scale, ColorF color /*= D2D1::ColorF(ColorF::White,1.f)*/, float _rotation /*= 0.f*/)
{
	Vector2 position = _position.ChangeYSign();

	D2D1_RECT_F rt{};
	rt.left = position.x - _scale.x * 0.5f;
	rt.top = position.y - _scale.y * 0.5f;
	rt.right = position.x + _scale.x * 0.5f;
	rt.bottom = position.y + _scale.y * 0.5f;

	m_deviceContext->CreateSolidColorBrush(color, &m_tempBrush);
	assert(m_tempBrush);

	SetTransform(_rotation, position);

	m_deviceContext->FillRectangle(rt, m_tempBrush);

	SetTransform(); 

	SafeRelease(&m_tempBrush);
}

void D2DRenderer::DrawFillRectangle2(Vector2 _leftTop, Vector2 _rightBottom, ColorF color /*= ColorF(ColorF::WhiteSmoke)*/, float _rotation /*= 0.f*/)
{
	Vector2 leftTop = _leftTop.ChangeYSign();
	Vector2 rightBottom = _rightBottom.ChangeYSign();

	D2D1_RECT_F rt{};
	rt.left = leftTop.x;
	rt.top = leftTop.y;
	rt.right = rightBottom.x;
	rt.bottom = rightBottom.y;

	m_deviceContext->CreateSolidColorBrush(color, &m_tempBrush);
	assert(m_tempBrush);

	Vector2 middle((rightBottom.x + leftTop.x) * 0.5f, (leftTop.y + rightBottom.y) * 0.5f);
	SetTransform(_rotation, middle);

	m_deviceContext->FillRectangle(rt, m_tempBrush);

	SetTransform();

	SafeRelease(&m_tempBrush);
}


void D2DRenderer::DrawTextW(const std::wstring& _str, Vector2 _leftTop, Vector2 _rightBottom, ColorF _color /*= D2D1::ColorF::White */, FONT_TYPE _type /*= FONT_TYPE::DEFALUT */)
{
	Vector2 leftTop = _leftTop.ChangeYSign();
	Vector2 rightBottom = _rightBottom.ChangeYSign();

	// ���� ��¹���
	D2D1_RECT_F rect = D2D1::RectF(leftTop.x, leftTop.y, rightBottom.x, rightBottom.y);

	// �귯�� ����
	m_deviceContext->CreateSolidColorBrush(D2D1::ColorF(_color), &m_tempBrush);
	assert(m_tempBrush);
	m_deviceContext->DrawTextW(_str.c_str(), static_cast<UINT32>(_str.length())
		, m_textFormat[static_cast<int>(_type)], rect, m_tempBrush);

	m_tempBrush->Release();

}

D2DTexture* D2DRenderer::LoadBitmap(const wstring& _key, const wchar_t* _filePath)
{
	HRESULT hr = S_OK;

	// �̹� ������ �ؽ�ó�̸� �ε����� �ʴ´�.
	auto iter = m_textures.find(_key);
	if (iter != m_textures.end())
	{
		return iter->second;
	}

	ID2D1Bitmap* bitmap = nullptr;

	hr = LoadBitmapFromFile(_filePath, 0, 0, &bitmap);

	assert(bitmap || !L"��Ʈ�� �ҷ����⿡ �����Ͽ����ϴ�");

	/// ��Ʈ�� �ε忡 ����
	if (!SUCCEEDED(hr))
	{
		return nullptr;
	}

	/// D2D �ؽ�ó ����
	D2DTexture* texture = new D2DTexture();
	texture->SetBitMap(bitmap);
	texture->SetFilePath(_filePath);
	texture->SetKey(_key);

	m_textures.insert(std::make_pair(_key, texture));

	return texture;
}

void D2DRenderer::DrawBitmap(const wstring& _key, Vector2 _position, Vector2 _textureLeftTop, Vector2 _sliceSize, float _rotation /*= 0.f*/, float _alpha /*= 1.f*/, FLIP_TYPE _type /*= FLIP_TYPE::NONE*/)
{
	// texture �ҷ����� 
	auto iter = m_textures.find(_key);
	assert(iter != m_textures.end() || !L"�ؽ�ó ������ �ε���� �ʾҽ��ϴ�");
	D2DTexture* texture = iter->second;

	// ��ũ�� ��ǥ��� ��ȯ 
	Vector2 position = _position.ChangeYSign();
	Vector2 halfSize = _sliceSize * 0.5f;

	// ȭ�鿡 ����ϴ� �뵵
	D2D1_RECT_F screen{};
	screen.left = position.x - halfSize.x;
	screen.right = position.x + halfSize.x;
	screen.top = position.y + halfSize.y;
	screen.bottom = position.y - halfSize.y;

	// ��Ʈ���� �ڸ��� �뵵
	D2D1_RECT_F textureRect{};
	textureRect.left = _textureLeftTop.x;
	textureRect.top = _textureLeftTop.y;
	textureRect.right = _textureLeftTop.x + _sliceSize.x;
	textureRect.bottom = _textureLeftTop.y + _sliceSize.y;

	if (_rotation != 0.f)
		SetTransform(_rotation, position);

	SetFlip(_type, position);

	m_deviceContext->DrawBitmap(texture->GetBitmap(), screen
		, _alpha, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, textureRect);

	SetTransform();
}

void D2DRenderer::DrawBitmap(const wstring& _key, Vector2 _position, float _rotation /*= 0.f*/, float _alpha /*= 1.f*/, FLIP_TYPE _type /*= FLIP_TYPE::NONE */, Vector2 _scale /*= Vector2::One*/)
{
	auto iter = m_textures.find(_key);

	assert(iter != m_textures.end() || !L"�ؽ�ó ������ �ε���� �ʾҽ��ϴ�");

	D2DTexture* texture = iter->second;
	Vector2 position = _position.ChangeYSign();
	Vector2 halfSize = texture->GetSize() * 0.5f;
	halfSize.x *= _scale.x;
	halfSize.y *= _scale.y;

	D2D1_RECT_F rect{};
	rect.left = position.x - halfSize.x;
	rect.right = position.x + halfSize.x;
	rect.top = position.y - halfSize.y;
	rect.bottom = position.y + halfSize.y;

	if (_rotation != 0.f)
	{
		SetTransform(_rotation, position);
	}

	SetFlip(_type, position);
	
	m_deviceContext->DrawBitmap(texture->GetBitmap(), rect
		, _alpha, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, nullptr);

	SetTransform();
}

void D2DRenderer::DrawFreezeBitmap(const wstring& _key, Vector2 _position, Vector2 _textureLeftTop, Vector2 _sliceSize, float _ratio, float _rotation /*= 0.f*/, float _alpha /*= 1.f*/, FLIP_TYPE _type /*= FLIP_TYPE::NONE*/)
{
	
	// texture �ҷ����� 
	auto iter = m_textures.find(_key);
	assert(iter != m_textures.end() || !L"�ؽ�ó ������ �ε���� �ʾҽ��ϴ�");
	D2DTexture* texture = iter->second;

	ID2D1Bitmap* bitmap = m_effectFactory->ExtractColor(texture->GetBitmap(), EXTRACT_COLOR::BLUE, _ratio);

	// ��ũ�� ��ǥ��� ��ȯ 
	Vector2 position = _position.ChangeYSign();
	Vector2 halfSize = _sliceSize * 0.5f;

	// ȭ�鿡 ����ϴ� �뵵
	D2D1_RECT_F screen{};
	screen.left = position.x - halfSize.x;
	screen.right = position.x + halfSize.x;
	screen.top = position.y + halfSize.y;
	screen.bottom = position.y - halfSize.y;

	// ��Ʈ���� �ڸ��� �뵵
	D2D1_RECT_F textureRect{};
	textureRect.left = _textureLeftTop.x;
	textureRect.top = _textureLeftTop.y;
	textureRect.right = _textureLeftTop.x + _sliceSize.x;
	textureRect.bottom = _textureLeftTop.y + _sliceSize.y;

	if (_rotation != 0.f)
		SetTransform(_rotation, position);

	SetFlip(_type, position);

	m_deviceContext->DrawBitmap(bitmap, screen
		, _alpha, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, textureRect);

	SetTransform();

	bitmap->Release();
}

void D2DRenderer::DrawPointLight(Vector2 _position, float _intensity, D2D1_VECTOR_3F _rgb, Vector2 _scale, float _angle)
{
	Vector2 position = _position.ChangeYSign();

	// ����Ʈ����Ʈ ���� ��Ʈ�� �ҷ�����
	auto bitmap = m_textures.find(L"PointLight")->second->GetBitmap();
	Vector2 halfSize{ bitmap->GetSize().width * 0.5f,  bitmap->GetSize().height * 0.5f };

	// ����Ʈ ����Ʈ �̹��� ����
	ID2D1Image* image = m_effectFactory->PointDiffuseImage(bitmap,_intensity, _rgb);

	// ���ĸ���ũ ����
	ID2D1Image* image2  = m_effectFactory->AlphaMask(image, m_textures.find(L"AlphaMask")->second->GetBitmap());
	
	D2D1_POINT_2F offset{ position.x - halfSize.x,position.y - halfSize.y };

	D2D1_SIZE_F size{ _scale.x,_scale.y };
	D2D1::Matrix3x2F rotationMat = Matrix3x2F::Rotation(_angle, position.ToPoint2F());
	D2D1::Matrix3x2F scaleMat = Matrix3x2F::Scale(size, position.ToPoint2F());

	// ���� ��ȯ ��� ���
	m_deviceContext->SetTransform(scaleMat * rotationMat * m_finalMatrix);

	m_deviceContext->DrawImage(image2, offset, D2D1_INTERPOLATION_MODE_LINEAR, D2D1_COMPOSITE_MODE_PLUS);

	m_deviceContext->SetTransform(m_finalMatrix);


	image->Release();
}

void D2DRenderer::DrawBlendBitmap(const wstring& _sourceKey, const wstring& _destination, D2D1_BLEND_MODE _mode, Vector2 _position, float _rotation, float _alpha /*= 1.f*/)
{
	auto source = m_textures.find(_sourceKey);
	auto dest = m_textures.find(_destination);

	ID2D1Bitmap* bitmap = m_effectFactory->Blend(source->second->GetBitmap(), dest->second->GetBitmap(), _mode);

	Vector2 position = _position.ChangeYSign();

	Vector2 halfSize{ bitmap->GetSize().width * 0.5f,  bitmap->GetSize().height * 0.5f };

	D2D1_RECT_F rect{};
	rect.left = position.x - halfSize.x;
	rect.right = position.x + halfSize.x;
	rect.top = position.y - halfSize.y;
	rect.bottom = position.y + halfSize.y;

	if (_rotation != 0.f)
		SetTransform(_rotation, position);

	m_deviceContext->DrawBitmap(bitmap, rect
		, _alpha, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, nullptr);

	if (_rotation != 0.f)
		SetTransform();

	bitmap->Release();
}

void D2DRenderer::DrawBitmapBloom(const wstring& _key, Vector2 _position, float _rotation /*= 0.f*/, float _alpha /*= 1.f*/)
{
	m_deviceContext->SetTransform(D2D1::Matrix3x2F::Identity());
	auto iter = m_textures.find(_key);

	assert(iter != m_textures.end() || !L"�ؽ�ó ������ �ε���� �ʾҽ��ϴ�");

	D2DTexture* texture = iter->second;

	ID2D1Bitmap* output = m_effectFactory->Cromakey(texture->GetBitmap());
	Vector2 position = _position.ChangeYSign();
	Vector2 halfSize{};
	halfSize.x = output->GetSize().width * 0.5f;
	halfSize.y = output->GetSize().height * 0.5f;
	D2D1_RECT_F rect{};

	rect.left = position.x - halfSize.x;
	rect.right = position.x + halfSize.x;
	rect.top = position.y + halfSize.y;
	rect.bottom = position.y - halfSize.y;

	SetTransform(_rotation, position);

	m_deviceContext->DrawBitmap(output, rect
		, _alpha, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, nullptr);	

	SetTransform();
	
	output->Release();
}

void D2DRenderer::DrawBitmapExtractColor(const wstring& _key, Vector2 _position
	, EXTRACT_COLOR _color, float _rotation /*= 0.f*/, float _alpha /*= 1.f*/)
{
	auto iter = m_textures.find(_key);

	assert(iter != m_textures.end() || !L"�ؽ�ó ������ �ε���� �ʾҽ��ϴ�");

	D2DTexture* texture = iter->second;
	ID2D1Bitmap* output = m_effectFactory->ExtractColor(texture->GetBitmap(), _color,0.f);

	Vector2 position = _position.ChangeYSign();
	Vector2 halfSize{};
	halfSize.x = output->GetSize().width * 0.5f;
	halfSize.y = output->GetSize().height * 0.5f;

	D2D1_RECT_F rect{};
	rect.left = position.x - halfSize.x;
	rect.right = position.x + halfSize.x;
	rect.top = position.y + halfSize.y;
	rect.bottom = position.y - halfSize.y;

	SetTransform(_rotation, position);

	m_deviceContext->DrawBitmap(output, rect
		, _alpha, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, nullptr);

	SetTransform();

	output->Release();
}

void D2DRenderer::DrawSpotLight()
{
	ID2D1Bitmap* spotLightBase = m_textures.find(L"SpotLightBase")->second->GetBitmap();

	D2D1_VECTOR_3F lightPosition{ 500.f,500.f,10.f };
	D2D1_VECTOR_3F pointAt{ 590.f,590.f,0.f };
	float focus = 20.f;
	float limitConeAngle = 90.f;
	float diffuse = 1.f;
	D2D1_VECTOR_3F color{ 1.f,1.f,1.f };

	Microsoft::WRL::ComPtr<ID2D1Image> output = m_effectFactory->SpotLightImage(spotLightBase, lightPosition, pointAt, focus, limitConeAngle, diffuse, color);

	Vector2 zero = Vector2::Zero;

	m_deviceContext->SetTransform(D2D1::Matrix3x2F::Identity());

	m_deviceContext->DrawImage(output.Get(),zero.ToPoint2F() ,D2D1_INTERPOLATION_MODE_MULTI_SAMPLE_LINEAR, D2D1_COMPOSITE_MODE_PLUS);
	
	m_deviceContext->SetTransform(m_finalMatrix);

}

void D2DRenderer::DrawRGBTransition(const wstring& _key, Vector2 _position, const std::vector<Vector2>& _rgbOffset)
{
	// RBG������ �����ʾҴٸ� ���
	assert(_rgbOffset.size() == 3);

	auto iter = m_textures.find(_key);

	assert(iter != m_textures.end() || !L"�ؽ�ó ������ �ε���� �ʾҽ��ϴ�");
	D2DTexture* texture = iter->second;

	// RBB ���󺰷� Color ���� �����ؼ� �����Ѵ�. �ϴ� �������Ӹ��� ���������� ����ϰԵǸ� �����ص� �ʿ䰡 ����
	ID2D1Bitmap* red = m_effectFactory->ExtractColor(texture->GetBitmap(), EXTRACT_COLOR::RED,0.f);
	ID2D1Bitmap* blue = m_effectFactory->ExtractColor(texture->GetBitmap(), EXTRACT_COLOR::BLUE,0.f);
	ID2D1Bitmap* green = m_effectFactory->ExtractColor(texture->GetBitmap(), EXTRACT_COLOR::GREEN,0.f);

	// �׸��� ��� ��ġ 
	Vector2 position = _position.ChangeYSign();
	Vector2 halfSize{};
	halfSize.x = texture->GetBitmap()->GetSize().width * 0.5f;
	halfSize.y = texture->GetBitmap()->GetSize().height * 0.5f;

	// ��Ʈ�� ����
	D2D1_RECT_F orgin{};
	orgin.left = position.x - halfSize.x;
	orgin.right = position.x + halfSize.x;
	orgin.top = position.y + halfSize.y;
	orgin.bottom = position.y - halfSize.y;

	// RGB������ ��� RGB �������
	D2D1_RECT_F rect[3]{};

	// ������ rect���� ����Ѵ�.
	for (int i = 0; i < 3; ++i)
	{
		rect[i].left = orgin.left + _rgbOffset[i].x;
		rect[i].right = orgin.right + _rgbOffset[i].x;
		rect[i].top = orgin.top + _rgbOffset[i].y;
		rect[i].bottom = orgin.bottom + _rgbOffset[i].y;
	}


	// �⺻ ��Ʈ���� ���
	m_deviceContext->DrawBitmap(texture->GetBitmap(), orgin
		, 1.f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, nullptr);

	// �������� ���� ��� ���� ADD ���� �����ؾ� RBGTransition�� ���ڰ� ����
	m_deviceContext->SetPrimitiveBlend(D2D1_PRIMITIVE_BLEND_MAX);

	m_deviceContext->DrawBitmap(red, rect[0]
		, 1.f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, nullptr);
	m_deviceContext->DrawBitmap(blue, rect[1]
		, 1.f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, nullptr);
	m_deviceContext->DrawBitmap(green, rect[2]
		, 1.f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, nullptr);

	//  ������带 ǥ������ �����Ѵ� 
	m_deviceContext->SetPrimitiveBlend(D2D1_PRIMITIVE_BLEND_SOURCE_OVER);

	// ����� ��Ʈ���� �������ش�
	red->Release();
	blue->Release();
	green->Release();
}

HRESULT D2DRenderer::LoadBitmapFromFile(PCWSTR _filePath
	, UINT _destinationWidth, UINT _destinationHeight, ID2D1Bitmap** _bitmap)
{
	HRESULT hr = S_OK;

	IWICBitmapDecoder* decoder = NULL;
	IWICBitmapFrameDecode* source = NULL;
	IWICStream* stream = NULL;
	IWICFormatConverter* converter = NULL;
	IWICBitmapScaler* scaler = NULL;

	assert(m_imagingFactorty);

	hr = m_imagingFactorty->CreateDecoderFromFilename(
		_filePath, NULL, GENERIC_READ, WICDecodeMetadataCacheOnLoad, &decoder);

	if (SUCCEEDED(hr))
	{
		// Create the initial frame.
		hr = decoder->GetFrame(0, &source);
	}

	if (SUCCEEDED(hr))
	{
		// Convert the image format to 32bppPBGRA
		// (DXGI_FORMAT_B8G8R8A8_UNORM + D2D1_ALPHA_MODE_PREMULTIPLIED).
		hr = m_imagingFactorty->CreateFormatConverter(&converter);
	}

	if (SUCCEEDED(hr))
	{
		// If a new width or height was specified, create an
		// IWICBitmapScaler and use it to resize the image.
		if (_destinationWidth != 0 || _destinationHeight != 0)
		{
			UINT originalWidth, originalHeight;
			hr = source->GetSize(&originalWidth, &originalHeight);
			if (SUCCEEDED(hr))
			{
				if (_destinationWidth == 0)
				{
					FLOAT scalar = static_cast<FLOAT>(_destinationHeight) / static_cast<FLOAT>(originalHeight);
					_destinationWidth = static_cast<UINT>(scalar * static_cast<FLOAT>(originalWidth));
				}
				else if (_destinationHeight == 0)
				{
					FLOAT scalar = static_cast<FLOAT>(_destinationWidth) / static_cast<FLOAT>(originalWidth);
					_destinationHeight = static_cast<UINT>(scalar * static_cast<FLOAT>(originalHeight));
				}

				hr = m_imagingFactorty->CreateBitmapScaler(&scaler);
				if (SUCCEEDED(hr))
				{
					hr = scaler->Initialize(
						source,
						_destinationWidth,
						_destinationHeight,
						WICBitmapInterpolationModeCubic
					);
				}
				if (SUCCEEDED(hr))
				{
					hr = converter->Initialize(
						scaler,
						GUID_WICPixelFormat32bppPBGRA,
						WICBitmapDitherTypeNone,
						NULL,
						0.f,
						WICBitmapPaletteTypeMedianCut
					);
				}
			}
		}
		else // Don't scale the image.
		{
			hr = converter->Initialize(
				source,
				GUID_WICPixelFormat32bppPBGRA,
				WICBitmapDitherTypeNone,
				NULL,
				0.f,
				WICBitmapPaletteTypeMedianCut
			);
		}
	}
	if (SUCCEEDED(hr))
	{
		// Create a Direct2D bitmap from the WIC bitmap.
		hr = m_deviceContext->CreateBitmapFromWicBitmap(
			converter,
			NULL,
			_bitmap
		);
	}

	SafeRelease(&decoder);
	SafeRelease(&source);
	SafeRelease(&stream);
	SafeRelease(&converter);
	SafeRelease(&scaler);

	return hr;
}


HRESULT D2DRenderer::CreateDeviceResources()
{
	
	HRESULT hr = S_OK;

	if (m_deviceContext == nullptr)
	{
		// This flag adds support for surfaces with a different color channel ordering than the API default.
		// You need it for compatibility with Direct2D.
		UINT creationFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;

		// This array defines the set of DirectX hardware feature levels this app  supports.
		// The ordering is important and you should  preserve it.
		// Don't forget to declare your app's minimum required feature level in its
		// description.  All apps are assumed to support 9.1 unless otherwise stated.
		D3D_FEATURE_LEVEL featureLevels[] =
		{
			D3D_FEATURE_LEVEL_11_1,
			D3D_FEATURE_LEVEL_11_0,
			D3D_FEATURE_LEVEL_10_1,
			D3D_FEATURE_LEVEL_10_0,
			D3D_FEATURE_LEVEL_9_3,
			D3D_FEATURE_LEVEL_9_2,
			D3D_FEATURE_LEVEL_9_1
		};

		// Create the DX11 API device object, and get a corresponding context.
		ID3D11Device* _D3D11Device;
		ID3D11DeviceContext* _D3D11DeviceContext;		// DirectX Core Objects. Required for 2D and 3D.

		D3D11CreateDevice(
			nullptr,                    // specify null to use the default adapter
			D3D_DRIVER_TYPE_HARDWARE,
			0,
			creationFlags,              // optionally set debug and Direct2D compatibility flags
			featureLevels,              // list of feature levels this app can support
			ARRAYSIZE(featureLevels),   // number of possible feature levels
			D3D11_SDK_VERSION,
			&_D3D11Device,              // returns the Direct3D device created
			&m_featureLevel,            // returns feature level of device created
			&_D3D11DeviceContext		// returns the device immediate context
		);

		assert(_D3D11Device);

		// Obtain the underlying DXGI device of the Direct3D11 device.
		IDXGIDevice* dxgiDevice;
		_D3D11Device->QueryInterface(&dxgiDevice);	/// ComPtr.As()
		assert(dxgiDevice);

		// Obtain the Direct2D device for 2-D rendering.
		m_factory->CreateDevice(dxgiDevice, &m_device);

		// Get Direct2D device's corresponding device context object.
		hr = m_device->CreateDeviceContext(D2D1_DEVICE_CONTEXT_OPTIONS_NONE,
			&m_deviceContext);

		// Allocate a descriptor.
		DXGI_SWAP_CHAIN_DESC1 swapChainDesc = { 0 };
		swapChainDesc.Width = 0;                           // 0 : use automatic sizing
		swapChainDesc.Height = 0;
		swapChainDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM; // this is the most common swapchain format
		swapChainDesc.Stereo = false;
		swapChainDesc.SampleDesc.Count = 1;                // don't use multi-sampling
		swapChainDesc.SampleDesc.Quality = 0;
		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapChainDesc.BufferCount = 2;                     // use double buffering to enable flip
		swapChainDesc.Scaling = DXGI_SCALING_STRETCH;

		//swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD; // all apps must use this SwapEffect
		swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD; // �ֻ��� ���� ����
		swapChainDesc.Flags = 0;

		// Identify the physical adapter (GPU or card) this device is runs on.
		IDXGIAdapter* dxgiAdapter;
		dxgiDevice->GetAdapter(&dxgiAdapter);

		// Get the factory object that created the DXGI device.
		IDXGIFactory2* dxgiFactory;
		dxgiAdapter->GetParent(IID_PPV_ARGS(&dxgiFactory));

		// Get the final swap chain for this window from the DXGI factory.
		DXGI_RATIONAL rate{};
		rate.Denominator = 60;
		rate.Numerator = 1;

		DXGI_SWAP_CHAIN_FULLSCREEN_DESC swapChainDescFull{};
		swapChainDescFull.RefreshRate = rate;
		//swapChainDescFull.Scaling = DXGI_MODE_SCALING_STRETCHED; // ȭ�� �ػ󵵿��� �°� ȭ���� �ø��� ����
		swapChainDescFull.Scaling = DXGI_MODE_SCALING_CENTERED; // ȭ�� �ػ󵵿��� �°� ȭ���� �ø��� ����

		swapChainDescFull.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER::DXGI_MODE_SCANLINE_ORDER_LOWER_FIELD_FIRST;
		swapChainDescFull.Windowed = true; // â��� ����
		//swapChainDescFull.Windowed = false; // ��üȭ�� ����

		dxgiFactory->CreateSwapChainForHwnd(_D3D11Device,
			m_hwnd,
			&swapChainDesc,
			&swapChainDescFull, // ��üȭ�� ����ü�� ����
		    //NULL, // â��� ȭ�� ���� 
			nullptr,
			&m_swapChain);

		// Ensure that DXGI doesn't queue more than one frame at a time.
		//dxgiDevice->SetMaximumFrameLatency(1);

		// Get the backbuffer for this window which is be the final 3D render target.
		ID3D11Texture2D* _backBuffer;
		m_swapChain->GetBuffer(0, IID_PPV_ARGS(&_backBuffer));

		//	Now we set up the Direct2D render target bitmap linked to the swapchain. 
		// Whenever we render to this bitmap, it is directly rendered to the 
		// swap chain associated with the window.
		D2D1_BITMAP_PROPERTIES1 _bitmapProperties =
			BitmapProperties1(
				D2D1_BITMAP_OPTIONS_TARGET | D2D1_BITMAP_OPTIONS_CANNOT_DRAW,
				PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_IGNORE),
				m_dpi,
				m_dpi
			);

		// Direct2D needs the dxgi version of the backbuffer surface pointer.
		IDXGISurface* dxgiBackBuffer;
		m_swapChain->GetBuffer(0, IID_PPV_ARGS(&dxgiBackBuffer));
		assert(dxgiBackBuffer);

		// Get a D2D surface from the DXGI back buffer to use as the D2D render target.
		HRESULT hr = m_deviceContext->CreateBitmapFromDxgiSurface(
			dxgiBackBuffer,
			&_bitmapProperties,
			&m_memoryBitamap
		);

		// Now we can set the Direct2D render target.
		m_deviceContext->SetTarget(m_memoryBitamap);
	}

	

	return hr;
}

void D2DRenderer::DiscardDeviceResources()
{
	SafeRelease(&m_deviceContext);
}
