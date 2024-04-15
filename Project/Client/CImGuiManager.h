#pragma once

class EditorUI;

class CImGuiManager : public CSingleton<CImGuiManager>

{
    SINGLE(CImGuiManager);
private:
    HWND                    m_hMainHwnd;
    map<string, EditorUI*>  m_mapUI;

public:
    int Init(HWND hwnd);
    void Tick();

private:
    void CreateEditorUI();

};

