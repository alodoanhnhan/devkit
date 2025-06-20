#pragma once
#include "IFWnd.h"

class CIFCheckBox : public CIFWnd {
GFX_DECLARE_DYNAMIC_EXISTING(CIFCheckBox, 0x00EE9848)
public:
    /// \brief Probably tells of the checkbox is currently checked or not
    /// \address 00656db0
    bool GetCheckedState_MAYBE() const;

    /// \brief Probably sets the checkbox checked state
    /// \address 00656d50
    void FUN_00656d50(bool state);

};
