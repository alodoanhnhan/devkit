#pragma once

#include "IFWnd.h"
#include "IFGauge.h"
#include "IFStatic.h"

class CIFTargetWindowCommonEnemy : public CIFWnd {
GFX_DECLARE_DYNAMIC_EXISTING(CIFTargetWindowCommonEnemy, 0x00eea59c)

    GFX_DECLARE_DYNCREATE_FN(CIFTargetWindowCommonEnemy)

GFX_DECLARE_MESSAGE_MAP(CIFTargetWindowCommonEnemy)

public:
    /// \address 0069aaa0
    bool OnCreate(long ln) override;

    /// \address 0069a550
    void OnUpdate() override;

private:
    char pad_0x036C[0x4];
    CIFStatic* m_pGDR_TWCE_TEXT_ID; //0x370
    CIFGauge* m_pGDR_TWCE_GAUGE_HPGAUGE; //0x374

private:
BEGIN_FIXTURE()
        ENSURE_SIZE(0x378)
        ENSURE_OFFSET(m_pGDR_TWCE_TEXT_ID, 0x370)
        ENSURE_OFFSET(m_pGDR_TWCE_GAUGE_HPGAUGE, 0x374)
    END_FIXTURE()

    RUN_FIXTURE(CIFTargetWindowCommonEnemy)
};
