#include "IFTargetWindow.h"
#include "IFflorian0Guide.h"
#include "GInterface.h"

GFX_IMPLEMENT_DYNAMIC_EXISTING(CIFTargetWindow, 0x00eea57c)

GFX_IMPLEMENT_DYNCREATE_FN(CIFTargetWindow, CIFWnd)

enum {
    GDR_TW_BUFF = 100, // CIFBuffViewer
    GDR_TW_CLOSE = 11, // CIFCloseButton
    GDR_TW_FORTRESSSTRUCTER = 8, // CIFTargetWindowFortressStructure
    GDR_TW_COMMONENEMY = 4, // CIFTargetWindowCommonEnemy
    GDR_TW_SPECIALMOBWND = 2, // CIFTargetWindowSpecialMob
    GDR_TW_JOB_PLAYERWND = 1, // CIFTargetWindowJobPlayer
    GDR_TW_PLAYERWND = 0, // CIFTargetWindowPlayer
};

GFX_BEGIN_MESSAGE_MAP(CIFTargetWindow, CIFWnd)
                    ONG_COMMAND(GDR_TW_CLOSE, &CIFTargetWindow::OnClick_11)
GFX_END_MESSAGE_MAP()

void CIFTargetWindow::OnTimer(int timerId) {
    //printf("%s\n", __FUNCTION__);
    reinterpret_cast<void (__thiscall *)(const CIFTargetWindow*, int)>(0x006993a0)(this, timerId);
}

bool CIFTargetWindow::OnCreate(long ln) {
    //printf("%s\n", __FUNCTION__);
    // return reinterpret_cast<bool (__thiscall *)(const CIFTargetWindow*, long)>(0x00699080)(this, ln);

    m_IRM.LoadFromFile("resinfo\\iftargetwindow.txt");
    m_IRM.CreateInterfaceSection("Create", this);

    m_pGDR_TW_PLAYERWND = m_IRM.GetResObj<CIFTargetWindowPlayer>(GDR_TW_PLAYERWND, 1); // 0x0
    m_pGDR_TW_JOB_PLAYERWND = m_IRM.GetResObj<CIFTargetWindowJobPlayer>(GDR_TW_JOB_PLAYERWND, 1); // 0x1
    m_pGDR_TW_SPECIALMOBWND = m_IRM.GetResObj<CIFTargetWindowSpecialMob>(GDR_TW_SPECIALMOBWND, 1); // 0x2
    m_pGDR_TW_COMMONENEMY = m_IRM.GetResObj<CIFTargetWindowCommonEnemy>(GDR_TW_COMMONENEMY, 1); // 0x4
    m_pCIFBuffViewer = m_IRM.GetResObj<CIFBuffViewer>(GDR_TW_BUFF, 1); // 0x64

    m_pGDR_TW_PLAYERWND->ShowGWnd(false);
    m_pGDR_TW_JOB_PLAYERWND->ShowGWnd(false);
    m_pGDR_TW_SPECIALMOBWND->ShowGWnd(false);
    m_pGDR_TW_COMMONENEMY->ShowGWnd(false);

    m_pCIFBuffViewer->ShowGWnd(false);

    m_pGDR_TW_FORTRESSSTRUCTER = m_IRM.GetResObj<CIFTargetWindowFortressStructure>(GDR_TW_FORTRESSSTRUCTER, 1); // 0x8
    m_pGDR_TW_FORTRESSSTRUCTER->ShowGWnd(false);

    return true;
}

void CIFTargetWindow::OnUpdate() {
    //printf("%s\n", __FUNCTION__);
    reinterpret_cast<void (__thiscall *)(const CIFTargetWindow*)>(0x00698ae0)(this);
}

void CIFTargetWindow::ShowGWnd(bool bVisible) {
    //printf("%s\n", __FUNCTION__);
    //reinterpret_cast<void (__thiscall *)(const CIFTargetWindow*, bool)>(0x00698b50)(this, bVisible);
    if (bVisible == false) {
        m_pGDR_TW_JOB_PLAYERWND->ShowGWnd(false);
        m_pGDR_TW_SPECIALMOBWND->ShowGWnd(false);
        m_pGDR_TW_COMMONENEMY->ShowGWnd(false);
        m_pGDR_TW_FORTRESSSTRUCTER->ShowGWnd(false);
        m_pCIFBuffViewer->ShowGWnd(false);
        g_pCGInterface->GetCharInfoGUI()->ShowGWnd(false);
    }
    CIFWnd::ShowGWnd(bVisible);
}

undefined1 CIFTargetWindow::OnCloseWnd() {
    //printf("%s\n", __FUNCTION__);
    return reinterpret_cast<undefined1 (__thiscall *)(const CIFTargetWindow*)>(0x0069a300)(this);
}

void CIFTargetWindow::OnClick_11() {
    //printf("%s\n", __FUNCTION__);
    reinterpret_cast<undefined1 (__thiscall *)(const CIFTargetWindow*)>(0x00698be0)(this);
}
