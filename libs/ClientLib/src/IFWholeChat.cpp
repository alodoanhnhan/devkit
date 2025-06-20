#include "IFWholeChat.h"
#include "GInterface.h"
#include "Game.h"
#include "IFButton.h"
#include "TextStringManager.h"
#include <remodel/MemberFunctionHook.h>

GFX_IMPLEMENT_DYNAMIC_EXISTING(CIFWholeChat, 0x00eec7a8)
GFX_IMPLEMENT_DYNCREATE_FN(CIFWholeChat, CIFWnd)


enum {
    GDR_WHOLE_CHAT_EDITBOX_INPUT = 36,
    GDR_WHOLE_CHAT_ODDITEM = 35,
    GDR_WHOLE_CHAT_STA_ODDITEM = 34,
    GDR_WHOLE_CHAT_STA_INPUTMSG = 33,
    GDR_WHOLE_CHAT_BTN_CANCEL = 32,
    GDR_WHOLE_CHAT_BTN_OK = 31,
    GDR_WHOLE_CHAT_EDITBOX_BG = 23,
    GDR_WHOLE_CHAT_EDITBOX_BLACKSQUARE = 22,
    GDR_WHOLE_CHAT_EDITBOX_FRAME = 21,
    GDR_WHOLE_CHAT_ICON = 11,
    GDR_WHOLE_CHAT_BG = 1,
};

GFX_BEGIN_MESSAGE_MAP(CIFWholeChat, CIFWnd)
                    ONG_KEYUP()
                    ONG_COMMAND(GDR_WHOLE_CHAT_BTN_OK, &CIFWholeChat::SendGlobalMessage)
                    ONG_COMMAND(GDR_WHOLE_CHAT_BTN_CANCEL, &CIFWholeChat::CloseDialog)
GFX_END_MESSAGE_MAP()


bool CIFWholeChat::OnCreate(long ln) {
    CIFFrame::OnCreate(ln);

    m_IRM.LoadFromFile("resinfo\\ifwholechat.txt");
    m_IRM.CreateInterfaceSection("Create", this);


    wnd_rect rect = GetBounds();

    wnd_rect rect2;
    rect2.pos.x = 10;
    rect2.pos.y = 12;
    rect2.size.height = 12;
    rect2.size.width = rect.size.width - 21;

    this->m_pCreatedStatic = static_cast<CIFStatic *>(CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), rect2, 201, 0));

    RECT someRect = {0, 0, 0, 0};
    m_pCreatedStatic->SetSomeRect(someRect);
    m_pCreatedStatic->SetFont(theApp.GetFont(0));
    m_pCreatedStatic->TB_Func_5(1);
    m_pCreatedStatic->TB_Func_6(0);
    m_pCreatedStatic->SetText(TSM_GETTEXTPTR("UIIT_STT_WHOLECHAT"));

    wnd_rect rect3 = rect2;

    m_pDragableArea = static_cast<CIFDragableArea *>(CreateInstance(this, GFX_RUNTIME_CLASS(CIFDragableArea), rect3, 202, 0));

    m_pDragableArea->SetSomeRect(someRect);
    m_pDragableArea->SetFont(theApp.GetFont(0));
    m_pDragableArea->TB_Func_5(1);
    m_pDragableArea->TB_Func_6(0);

    m_pEdit = m_IRM.GetResObj<CIFEdit>(GDR_WHOLE_CHAT_EDITBOX_INPUT, 1);
    m_pEdit->AddValue_404(2);
    m_pEdit->SetMaxStringInput(100);

    wnd_rect bounds = m_pEdit->GetBounds();

    m_pEdit->SetTextmode(bounds.size.width);

    m_pEdit->SetFocus_MAYBE();

    RECT rect_Slot1_lable = {350,40,46,46};
    CIFFrame *statics = (CIFFrame*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFFrame), rect_Slot1_lable, 6557, 0);
    statics->TB_Func_13("interface\\frame\\frameg_wnd_", 1, 1);
    statics->ShowGWnd(true);
    statics->BringToFront();
    RECT rect_button ={rect_Slot1_lable.left + 6,
                       rect_Slot1_lable.top + 6,
                       rect_Slot1_lable.right - 12,
                       rect_Slot1_lable.bottom - 12};
    m_slowithhelpsss = (CIFSlotWithHelp*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSlotWithHelp), rect_button, 6556, 0);
    m_slowithhelpsss->ShowGWnd(true);
    m_slowithhelpsss->BringToFront();
    m_slowithhelpsss->Type=26;
    return true;
}

void CIFWholeChat::FUN_007ef400(int numberOfItemsLeft) {
    if (numberOfItemsLeft < 0) {
        CSOItem *pItem = g_pCGInterface->GetMainPopup()->GetInventory()->GetItemBySlot(m_SlotOfChattingItem);
        numberOfItemsLeft = pItem->GetQuantity();
    }

    m_NumberOfItemsLeft = numberOfItemsLeft;
    m_IRM.GetResObj<CIFButton>(0x1f, 1)->SetEnabledState(numberOfItemsLeft != 0);

    CIFStatic *sta = m_IRM.GetResObj<CIFStatic>(0x23, 1);
    sta->SetTextFormatted(L"%d", numberOfItemsLeft);
}

int CIFWholeChat::OnKeyUp(UINT nKey, UINT a2, UINT a3) {

    if (nKey == VK_RETURN) {
        SendGlobalMessage();
        return 1;
    }

    if (nKey == VK_ESCAPE) {
        CloseDialog();
        return 1;
    }

    return 0;
}

void CIFWholeChat::SendGlobalMessage() {
    std::n_wstring text = m_pEdit->GetCurrentText();

    if (this->m_NumberOfItemsLeft < 1) {
        m_pEdit->SetText(L"");
        return;
    }

    if (text.length() == 0) {
        g_pCGInterface->WriteSystemMessage(SYSLOG_NONE, TSM_GETTEXTPTR("UIIT_STT_WHOLECHAT_INPUTMSG"));
        m_pEdit->SetText(L"");
        return;
    }

    if (CGame::GetBadwordFilter()->sub_8C4020(text)) {
        g_pCGInterface->WriteSystemMessage(SYSLOG_NONE, TSM_GETTEXTPTR("UIIT_MSG_WHOLECHATERR_NOTINUSEMSG"));
        m_pEdit->SetText(L"");
        return;
    }

    g_pCGInterface->WriteGlobalMessage(GetSlotOfChattingItem(), text);
    if(m_slowithhelpsss->ItemInfo != 0)
    {
        m_slowithhelpsss->FUN_006871d0(0);
        m_slowithhelpsss->TB_Func_13("", 1, 1);
    }

    m_pEdit->SetText(L"");
}

void CIFWholeChat::CloseDialog() {
    OnCloseWnd();
}

undefined1 CIFWholeChat::OnCloseWnd() {
    g_pCGInterface->FUN_0079b8a0(0, 0xffffffff);
    return 1;
}

void CIFWholeChat::SetGWndSize(int width, int height) {
    CIFTileWnd::SetGWndSize(width, height);
    UpdateLayout();
}

void CIFWholeChat::UpdateLayout() {
    wnd_rect rect = GetBounds();

    m_pCreatedStatic->MoveGWnd(rect.pos.x + 10, rect.pos.y + 12);
    m_pCreatedStatic->SetGWndSize(rect.size.width - 21, 12);

    m_pDragableArea->MoveGWnd(rect.pos.x + 10, rect.pos.y + 12);
    m_pDragableArea->SetGWndSize(rect.size.width - 21, 34);
}

int CIFWholeChat::GetSlotOfChattingItem() const {
    return m_SlotOfChattingItem;
}

void CIFWholeChat::SetSlotOfChattingItem(int slot) {
    m_SlotOfChattingItem = slot;
}
void CIFWholeChat::SetIcon(CSOItem * iteminfo)
{
    if(iteminfo==NULL)
        return;
    m_slowithhelpsss->FUN_006871d0(iteminfo);
}