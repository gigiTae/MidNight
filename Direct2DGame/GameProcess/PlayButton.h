#pragma once
#include "MonoBehaviour.h"

class PopupWindow;

/// <summary>
///  �˾�â���� ����� ��ư�� ���� ������Ʈ
/// </summary>
class PlayButton :
    public MonoBehaviour
{
public:
    PlayButton();
    ~PlayButton();
    Component* Clone() override;

    void Start() override;

public:
    void OnMouseClicked() override;
    PopupWindow* m_popupWindow;
};

