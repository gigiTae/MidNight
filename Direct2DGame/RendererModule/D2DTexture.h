#pragma once
#include "D2DResource.h"

/// <summary>
/// ��Ʈ�� ������ �����ϰ� �ִ� �ؽ�ó
/// </summary>
class D2DTexture :
    public D2DResource
{
public:
    // ��Ʈ���� ����� ��ȯ�Ѵ�.
    Vector2 GetSize();

private:
    void SetBitMap(ID2D1Bitmap* _bitmap) { m_bitmap = _bitmap; }
    ID2D1Bitmap* GetBitmap() { return m_bitmap;}

    D2DTexture();
	~D2DTexture();

    ID2D1Bitmap* m_bitmap; // ��Ʈ�� ����

    friend class D2DRenderer;
};
 
