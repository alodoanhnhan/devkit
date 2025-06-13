#include "IFSTTotalPointSlot.h"
#include "ICPlayer.h"

#define GXVSRO_SLOT_UNIQUELOG_NUM 1
#define GXVSRO_SLOT_UNIQUELOG_NUM_PIC 2
#define GXVSRO_SLOT_UNIQUELOG_NAME 3
#define GXVSRO_SLOT_UNIQUELOG_Guild 5
#define GXVSRO_SLOT_UNIQUELOG_POINT 6

GFX_IMPLEMENT_DYNCREATE(CIFSTTotalPointSlot, CIFWnd)
GFX_BEGIN_MESSAGE_MAP(CIFSTTotalPointSlot, CIFWnd)
GFX_END_MESSAGE_MAP()

CIFSTTotalPointSlot::CIFSTTotalPointSlot(void)
{
    //printf("> " __FUNCTION__ "\n");
}


CIFSTTotalPointSlot::~CIFSTTotalPointSlot(void)
{
    //printf("> " __FUNCTION__ "\n");
}

bool CIFSTTotalPointSlot::OnCreate(long ln)
{
    // Populate inherited members
    CIFWnd::OnCreate(ln);

    RECT rect0 = { 20,5,25,13 };
    RECT rect1 = { 68,5,20,20 };
    RECT rect2 = { 110,5,115,13 };
    RECT rect3 = { 320,5,80,13 };

    m_custom_label1 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), rect0, GXVSRO_SLOT_UNIQUELOG_NUM, 0);
    m_custom_label2 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), rect1, GXVSRO_SLOT_UNIQUELOG_NUM_PIC, 0);
    m_custom_label3 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), rect2, GXVSRO_SLOT_UNIQUELOG_NAME, 0);
    m_custom_label4 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), rect3, GXVSRO_SLOT_UNIQUELOG_Guild, 0);


    m_custom_label2->MoveGWnd(GetPos().x + 1, m_custom_label1->GetPos().y-3);
    m_custom_label3->MoveGWnd(m_custom_label1->GetPos().x + m_custom_label1->GetSize().width + 5, m_custom_label1->GetPos().y);
    m_custom_label4->MoveGWnd(m_custom_label3->GetPos().x + m_custom_label3->GetSize().width + 30, m_custom_label1->GetPos().y);


    m_custom_label1->SetTextColor(0xffffff);
    m_custom_label2->SetTextColor(0xffffff);
    m_custom_label3->SetTextColor(0xffffff);
    m_custom_label4->SetTextColor(0xffffff);
    m_custom_label2->ShowGWnd(false);
    ShowGWnd(true);
    return true;
}

void CIFSTTotalPointSlot::OnUpdate()
{
}

void CIFSTTotalPointSlot::WriteLine(const wchar_t* num, const wchar_t* Charname, const wchar_t* Guild)
{
    m_custom_label1->SetText(num);
    m_custom_label3->SetText(Charname);
    m_custom_label4->SetText(Guild);


    if (wcscmp(g_pCICPlayer->GetCharName().c_str(), Charname) == 0)
    {
        m_custom_label1->m_FontTexture.SetColor(0xFFB2FF08);
        m_custom_label3->m_FontTexture.SetColor(0xFFB2FF08);
        m_custom_label4->m_FontTexture.SetColor(0xFFB2FF08);
    }
    else
    {
        m_custom_label1->m_FontTexture.SetColor(0xFFFFFFFF);
        m_custom_label3->m_FontTexture.SetColor(0xFFFFFFFF);
        m_custom_label4->m_FontTexture.SetColor(0xFFFFFFFF);
    }
}

void CIFSTTotalPointSlot::ShowIcon()
{
    m_custom_label2->ShowGWnd(true);
}