#pragma once
#include "MonoBehaviour.h"

/// <summary>
/// ������ ��ư �뵵 ������Ʈ
/// 
/// 2023.8.6 1:31 gitae
/// </summary>
class SceneChangeButton :
    public MonoBehaviour
{
public:
    SceneChangeButton();
    ~SceneChangeButton();

    Component* Clone() override;

    void SetSceneName(const wstring& _name) { m_chageScneName = _name; }
    
    void OnMouseClicked() override;
    
private:
    wstring m_chageScneName; // ��ư �������� �����ϴ� �� �̸� 
   
};

