//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2018 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////

#ifndef _acuiComboBox_h
#define _acuiComboBox_h
#pragma pack (push, 8)

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

//prevent the MS header "use_ansi.h" from outputing
//its linker directives, we expect clients to specify
//what flavor (debug/release) of the C++ runtime they want to
//link against.
#pragma push_macro("_USE_ANSI_CPP")
#define _USE_ANSI_CPP
#include <map>
#pragma pop_macro("_USE_ANSI_CPP")
typedef std::map<int, AcCmColor*>   AcCmColorTable;

class CAdUiImage;

/////////////////////////////////////////////////////////////////////////////
// CAcUiComboBox window

class ACUI_PORT CAcUiComboBox : public CAdUiComboBox {
    DECLARE_DYNAMIC(CAcUiComboBox);

public:
    CAcUiComboBox ();
    virtual ~CAcUiComboBox ();

    // Subclassed EditBox and Validation
public:
    CAcUiEdit *AcUiEditBox ();
    BOOL    Validate ();
    ACUI_ERROR_CODE ValidateData (CString& x);
    void    Convert ();
    BOOL    ConvertData (CString& x);
    void    SetRange (double vMin, double vMax);

    // ClassWizard-controlled
public:
    //{{AFX_VIRTUAL(CAcUiComboBox)
    //}}AFX_VIRTUAL

protected:
    //{{AFX_MSG(CAcUiComboBox)
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CAcUiAngleComboBox window
//
// ComboBox with the persistent CAcUiAngleEdit control for the Edit box

class ACUI_PORT CAcUiAngleComboBox : public CAcUiComboBox {
    DECLARE_DYNAMIC(CAcUiAngleComboBox);

public:
    CAcUiAngleComboBox ();
    virtual ~CAcUiAngleComboBox ();

    // ClassWizard-controlled
public:
    //{{AFX_VIRTUAL(CAcUiAngleComboBox)
    //}}AFX_VIRTUAL

protected:
    //{{AFX_MSG(CAcUiAngleComboBox)
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CAcUiNumericComboBox window
//
// ComboBox with the persistent CAcUiNumericEdit control for the Edit box

class ACUI_PORT CAcUiNumericComboBox : public CAcUiComboBox {
    DECLARE_DYNAMIC(CAcUiNumericComboBox);

public:
    CAcUiNumericComboBox ();
    virtual ~CAcUiNumericComboBox ();

    // ClassWizard-controlled
public:
    //{{AFX_VIRTUAL(CAcUiNumericComboBox)
    //}}AFX_VIRTUAL

protected:
    //{{AFX_MSG(CAcUiNumericComboBox)
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CAcUiStringComboBox window
//
// ComboBox with the persistent CAcUiStringEdit control for the Edit box

class ACUI_PORT CAcUiStringComboBox : public CAcUiComboBox {
    DECLARE_DYNAMIC(CAcUiStringComboBox);

public:
    CAcUiStringComboBox ();
    virtual ~CAcUiStringComboBox ();

    // ClassWizard-controlled
public:
    //{{AFX_VIRTUAL(CAcUiStringComboBox)
    //}}AFX_VIRTUAL

protected:
    //{{AFX_MSG(CAcUiStringComboBox)
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CAcUiSymbolComboBox window
//
// ComboBox with the persistent CAcUiSymbolEdit control for the Edit box

class ACUI_PORT CAcUiSymbolComboBox : public CAcUiComboBox {
    DECLARE_DYNAMIC(CAcUiSymbolComboBox);

public:
    CAcUiSymbolComboBox ();
    virtual ~CAcUiSymbolComboBox ();

    // ClassWizard-controlled
public:
    //{{AFX_VIRTUAL(CAcUiSymbolComboBox)
    //}}AFX_VIRTUAL

protected:
    //{{AFX_MSG(CAcUiSymbolComboBox)
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////////
// MRU Prototypes

#define ACUI_MAX_COMBOBOX_MRU   6
#define ACUI_MAX_TRUECOLOR_COMBOBOX_MRU   16

class ACUI_PORT CAcUiMRUComboBox;
class ACUI_PORT CAcUiMRUListBox;

typedef enum {
    kAcUiMRUCargo_Last = -106, // Make sure this is the last entry
    kAcUiMRUCargo_Option2 = -105,
    kAcUiMRUCargo_Option1 = -104,
    kAcUiMRUCargo_Other2 = -103,
    kAcUiMRUCargo_Other1 = -102,
    kAcUiMRUCargo_None = -101
} ACUI_MRU_CARGO;

//////////////////////////////////////////////////////////////////////////////
// ComboLBox for MRU ComboBox - Provides DrawTip support

class ACUI_PORT CAcUiMRUListBox : public CAcUiListBox {
public:
    CAcUiMRUListBox ();
    virtual ~CAcUiMRUListBox ();

    // Misc.
public:
    virtual void    GetContentExtent (
        int item, LPCTSTR text, int& width, int& height
        );

    // AdUi message handler
protected:
    virtual BOOL    OnGetTipRect (CRect& r);

    // MRU control
protected:
    int     ExtraWidth ();
    CAcUiMRUComboBox *MRUComboBox ();

    // ClassWizard-controlled
public:
    //{{AFX_VIRTUAL(CAcUiMRUListBox)
    //}}AFX_VIRTUAL

protected:
    //{{AFX_MSG(CAcUiMRUListBox)
    //}}AFX_MSG

    DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////////
// MRU ComboBox

class ACUI_PORT CAcUiMRUComboBox : public CAcUiComboBox {
public:
    CAcUiMRUComboBox ();
    virtual ~CAcUiMRUComboBox ();

    // Misc.
    virtual void    GetContentExtent (LPCTSTR text, int& width, int& height);
    virtual BOOL    GetItemColors(DRAWITEMSTRUCT& dis, COLORREF& fgColor, 
        COLORREF& bgColor, COLORREF& fillColor);

    // AdUi message handler
protected:
    virtual BOOL    OnGetTipRect (CRect& r);

    // MRU control
protected:
    bool    m_bIsDynamicCreation : 1;   // TRUE if Create() is used, else FALSE.
    bool    m_bUseOption1       : 1;
    bool    m_bUseOption2       : 1;
    bool    m_bUseOther1        : 1;
    bool    m_bUseOther2        : 1;
    bool    m_bOther1Selected   : 1;
    bool    m_bOther2Selected   : 1;
    int     m_cargoOption1;
    int     m_cargoOption2;
    LOGPALETTE* m_logPalette;
    HPALETTE m_hPalette;
    CPalette* m_pOldPalette;
    int     m_itemHeight;
    int     m_lastSelection;
    int     m_mruCargo[ACUI_MAX_COMBOBOX_MRU];
    int     m_mruLen;
    CString m_mruName[ACUI_MAX_COMBOBOX_MRU];

    virtual int     CalcItemHeight (); 

    // The methods below are subfunctions to support the virtual DrawItem(..)
    // method which is called via message handler OnDrawItem(..).  Derived
    // classes may override the DrawItem(..) method and use these subfunctions
    // to customize the way DrawItemImage(..) is called. For example, the linetype
    // control does not use the cargo value as an index, thus it must replace
    // the cargo parameter of DrawItemImage(..) to instead pass the index of the
    // selection being drawn, then it's derived DrawItemImage(..) must resolve
    // that index to the object id of the linetype
    virtual void    DrawItemImage (CDC& dc, CRect& r, INT_PTR cargo);
    void    DrawItemImageFromCargo(CDC* dc, CRect& r, int i);
    void    DrawTextAndFocusRect(LPDRAWITEMSTRUCT lpDrawItemStruct, 
        CDC* dc, 
        CRect& rItem, 
        int i,
        COLORREF& fgColor,
        COLORREF& bgColor);
    void    CreateAndSelectPalette (LPDRAWITEMSTRUCT lpDrawItemStruct, 
        CDC* dc);
    void    SetupForImageDraw(LPDRAWITEMSTRUCT lpDrawItemStruct, 
        CDC* dc, 
        CRect& rItem,
        CRect& rImage,
        COLORREF& fgColor,
        COLORREF& bgColor);
    void    ResetAndRestorePalette(CDC* dc, int savedState);
    // end DrawItem(..) supporting methods

    BOOL    FindCargoInMRU (int cargo);
    int     GenerateCargoFromMRU (int seed);
    virtual BOOL    GetOptionName (BOOL isOption2, CString& name);
    virtual BOOL    GetOtherName (BOOL isOther2, CString& name);
    virtual void    OnAddItems ();
    virtual void    OnComboBoxInit ();
    virtual BOOL    OnSelectOther (BOOL isOther2, int curSel, int& newSel);
    void    SelectOther (BOOL isOther2);

public:
    int     AddItemToList (LPCTSTR name, INT_PTR cargo);
    int     AddItemToMRU (LPCTSTR name, int cargo); // Returns item index (or -1).
    void    AddItems ();
    virtual BOOL    Create (DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID);
    virtual int     ExtraWidth ();
    int     FindItemByCargo (INT_PTR cargo);            // Get corresponding item index.
    int     GetCargoOption1 ();
    int     GetCargoOption2 ();
    INT_PTR     GetCurrentItemCargo ();                 // Get current item's cargo (or -1).
    INT_PTR     GetItemCargo (int item);                // Get item's cargo (or -1).
    LOGPALETTE *GetLogPalette ();
    HPALETTE GetPalette ();
    BOOL    GetUseOption1 ();
    BOOL    GetUseOption2 ();
    BOOL    GetUseOther1 ();
    BOOL    GetUseOther2 ();
    virtual int     ImageWidth ();
    int     InsertItemInList (int index, LPCTSTR name, INT_PTR cargo);
    int     ItemHeight ();
    void    RecalcHeight ();
    void    RemoveItemFromMRU (int cargo);
    void    SetCargoOption1 (int cargo);
    void    SetCargoOption2 (int cargo);
    void    SetLastSelection (int sel);
    void    SetLogPalette (LOGPALETTE *logPalette);
    void    SetPalette (HPALETTE hPalette);
    void    SetUseOption1 (BOOL use);
    void    SetUseOption2 (BOOL use);
    void    SetUseOther1 (BOOL use);
    void    SetUseOther2 (BOOL use);

    // Aliases for OptionX and OtherX
public:        
    BOOL    GetUseByBlock ();
    BOOL    GetUseByLayer ();
    BOOL    GetUseOther ();
    BOOL    GetUseWindows ();
    void    SetUseByBlock (BOOL use);
    void    SetUseByLayer (BOOL use);
    void    SetUseOther (BOOL use);
    void    SetUseWindows (BOOL use);

    // ClassWizard-controlled
public:
    //{{AFX_VIRTUAL(CAcUiMRUComboBox)
public:
    virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
    virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
protected:
    virtual void PreSubclassWindow();
    virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
    //}}AFX_VIRTUAL

protected:
    //{{AFX_MSG(CAcUiMRUComboBox)
    afx_msg BOOL OnCloseUp();
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg BOOL OnDropDown();
    afx_msg BOOL OnSelEndOk();
    //}}AFX_MSG

    DECLARE_MESSAGE_MAP()
};
//////////////////////////////////////////////////////////////////////////////
class CAcUiLTypeRecord : public CObject {
public:
    CString & ltypeName();
    void setLTypeName(CString sName);
    AcDbObjectId objectId();
    void setObjectId(AcDbObjectId id);
    BOOL isDependent();
    void setIsDependent(BOOL bValue);

private:
    CString m_strLTypeName;
    AcDbObjectId m_idObjectId;
    BOOL m_bIsDependent;
};

/////////////////////////////////////////////////////////////////////////////
// Inlines for CAcUiLTypeRecord 
/////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

inline CString& CAcUiLTypeRecord::ltypeName() 
{
    return m_strLTypeName;
}

inline void CAcUiLTypeRecord::setLTypeName(CString sName) 
{
    m_strLTypeName = sName;
}

inline AcDbObjectId CAcUiLTypeRecord::objectId() 
{
    return m_idObjectId;
}

inline void CAcUiLTypeRecord::setObjectId(AcDbObjectId id) 
{
    m_idObjectId = id;
}

inline BOOL CAcUiLTypeRecord::isDependent()
{
    return m_bIsDependent;
}

inline void CAcUiLTypeRecord::setIsDependent(BOOL bValue)
{
    m_bIsDependent = bValue;
}


//////////////////////////////////////////////////////////////////////////////

class ACUI_PORT CAcUiLineTypeComboBox : public CAcUiMRUComboBox 
{
public:
    CAcUiLineTypeComboBox ();
    virtual ~CAcUiLineTypeComboBox ();

    virtual void    OnComboBoxInit ();

    void    AddItems ();

    // Get/Set AcDbObjectId of current selection
    AcDbObjectId getOIDSel(int sel);
    AcDbObjectId getOIDCurSel();
    void setCurSelByOID(const AcDbObjectId& oidCurSel);       
    bool isOtherSelected();
    void forceSelectOther (BOOL isOther2);
    int  getLastSelection();
    bool getDbReload();
    void setDbReload(bool bReload);
    void emptyLTypeLocalList();
protected:
    virtual void DrawItemImage (CDC& dc, CRect& r, INT_PTR cargo);
    virtual void OnAddItems ();
    virtual BOOL OnSelectOther (BOOL isOther2, int curSel, int& newSel);
    INT_PTR  GetItemCargo (int item);  // Cargo for this class is just the
    // combobox item index.  That needs to
    // be resolved to the item data pointer
    // which is actually a CAcUiLTypeRecord
    // pointer, not an integer
    int  FindItemByCargo (AcDbObjectId cargo);
    void LoadContentsFromDatabase();
    void ShowLTypes(bool bForceReloadDB = false);
    int AddLTypeToControl(CAcUiLTypeRecord * pLTypeRecord);
    CAcUiLTypeRecord* CreateLTRecord(CString& cstrLTName, AcDbObjectId& oidLT);

    virtual int ImageWidth();
    // Get/Set current DB pointer
    AcDbDatabase* getLTLocalMapDB();
    void setLTLocalMapDB(AcDbDatabase* pDb);

    // Member data
    CObList m_LTypeLocalList;  
    AcDbDatabase* m_pLTLocalMapDB;
    bool m_bDbReload;

public:

    // ClassWizard-controlled
public:
    //{{AFX_VIRTUAL(CAcUiLineTypeComboBox)
    virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
    //}}AFX_VIRTUAL

protected:
    //{{AFX_MSG(CAcUiLineTypeComboBox)
    //}}AFX_MSG

    DECLARE_MESSAGE_MAP()
};

// Test for and set whether to reload from the db or not
inline
    bool 
    CAcUiLineTypeComboBox::getDbReload()
{
    return m_bDbReload;
}
inline
    void 
    CAcUiLineTypeComboBox::setDbReload(bool bReload)
{
    m_bDbReload = bReload;
}

// Test for the "Other" selection of the linetype combo
inline
    void 
    CAcUiLineTypeComboBox::forceSelectOther (BOOL isOther2)
{
    SelectOther(isOther2);
}

inline
    int
    CAcUiLineTypeComboBox::getLastSelection()
{
    return m_lastSelection;
}

inline
    bool 
    CAcUiLineTypeComboBox::isOtherSelected()
{
    CString otherName;
    CString curSelName;
    GetOtherName (false, otherName);
    GetLBText(GetCurSel(), curSelName);
    return curSelName == otherName;
}

// Get/Set AcDbObjectId of given selection
inline 
    AcDbObjectId 
    CAcUiLineTypeComboBox::getOIDSel(int sel)
{
    AcDbObjectId oidLT;
    CAcUiLTypeRecord* pLTRec = 
        (CAcUiLTypeRecord*)(GetItemDataPtr(sel));
    if (NULL != pLTRec)
        oidLT = pLTRec->objectId();
    return oidLT;
}

// Get/Set AcDbObjectId of current selection
inline 
    AcDbObjectId 
    CAcUiLineTypeComboBox::getOIDCurSel()
{
    return getOIDSel(GetCurSel());
}

inline 
    void 
    CAcUiLineTypeComboBox::setCurSelByOID(const AcDbObjectId& oidCurSel)
{
    int i = FindItemByCargo(oidCurSel);
    SetCurSel(i >= 0 ? i : m_lastSelection);
    if (i >= 0)
        m_lastSelection = i;
}

//////////////////////////////////////////////////////////////////////////////

class ACUI_PORT CAcUiColorComboBox : public CAcUiMRUComboBox {
public:
    CAcUiColorComboBox ();
    virtual ~CAcUiColorComboBox ();

    // MRU control
protected:
    virtual void    DrawItemImage (CDC& dc, CRect& r, INT_PTR cargo);
    virtual void    OnAddItems ();
    virtual BOOL    OnSelectOther (BOOL isOther2, int curSel, int& newSel);

    // Color control
protected:
    int     m_blockColorIndex;

    virtual BOOL    GetOtherColorIndex (
        int defaultColorIndex, int layerColorIndex, BOOL enableMetaColors,
        int& colorIndex
        );
    virtual BOOL    GetWindowsColor (COLORREF& color);
    virtual BOOL    GetOtherName (BOOL isOther2, CString& name);

    void    RGBFill (CDC& dc, CRect& rFill);
public:
    int     AddColorToMRU (int colorIndex);         // Returns item index (or -1).
    int     FindItemByColorIndex (int colorIndex);  // Get corresponding item index.
    int     GetBlockColorIndex ();
    virtual COLORREF GetColorFromIndex (int colorIndex);    // Returns corresponding color.
    virtual int     GetColorIndex (COLORREF color);         // Returns color index (or -1).
    int     GetCurrentItemColorIndex ();            // Get current item's color index (or -1).
    virtual int     GetCurrentLayerColorIndex ();
    int     GetItemColorIndex (int item);           // Get item's color index (or -1).
    virtual COLORREF LookupColor (                          // Returns corresponding raw color.
        int colorIndex,
        LOGPALETTE *logPalette
        );
    void    SetBlockColorIndex (int colorIndex);

    // ClassWizard-controlled
public:
    //{{AFX_VIRTUAL(CAcUiColorComboBox)
    //}}AFX_VIRTUAL

protected:
    //{{AFX_MSG(CAcUiColorComboBox)
    //}}AFX_MSG

    DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////////

#define ACUI_TRUECOLOR_COMBOBOX_TABLE_SIZE  ACUI_MAX_TRUECOLOR_COMBOBOX_MRU + 9

class ACUI_PORT CAcUiTrueColorComboBox : public CAcUiMRUComboBox {
public:

    enum ColorTableIndex {
        kCargoOption1           =  0,       // index of byLayer
        kCargoOption2           =  1,       // index of byBlock
        kCargoStockItem1        =  2,       // index of Red
        kCargoStockItem2        =  3,       // index of Yellow
        kCargoStockItem3        =  4,       // index of Green
        kCargoStockItem4        =  5,       // index of Cyan
        kCargoStockItem5        =  6,       // index of Blue
        kCargoStockItem6        =  7,       // index of Magenta
        kCargoStockItem7        =  8,       // index of White
        kIndexOfFirstMRUItem    =  9,       // default newt table index
        kCargoOther1            = -1,       // place holder for select color dialog
        kCargoOther2            = -2,       // place holder for windows dialog
        kLastIndex              = ACUI_TRUECOLOR_COMBOBOX_TABLE_SIZE-1      // last index in table
    };

    CAcUiTrueColorComboBox      ();
    virtual                 ~CAcUiTrueColorComboBox     ();

    // MRU List
    void                    AddItems                    ();
    int                     AddItemToList               (LPCTSTR name, int index, INT_PTR cargo);
    int                     AddItemToMRU                (LPCTSTR name, int cargo);           // INTERNAL USE ONLY - Override to sort correctly
    int                     AddColorToMRU               (const AcCmColor& color);

    // Drop down list
    int                     FindItemByColor             (const AcCmColor& color);
    void                    GetCurrentItemColor         (AcCmColor& color);
    DWORD                   getColorByCargo             (int cargo);

    // Members
    const AcCmColor&        GetBlockColor               ();
    void                    SetBlockColor               (const AcCmColor& color);

    virtual COLORREF        GetColorFromIndex           (int colorIndex);
    DWORD                   getColorData                (AcCmColor color);
    int                     GetColorIndex               (COLORREF color);

    void                    SetSupportColorBook         (BOOL newVal);
    BOOL                    GetSupportColorBook         ();

protected:

    // Color Control
    int                     m_cargoOther1;
    int                     m_cargoOther2;
    AcCmColor               m_blockColor;


    virtual void            DrawItemImage               (CDC& dc, CRect& r, INT_PTR cargo);
    virtual void            OnAddItems                  ();


    // Color Pickers
    virtual BOOL            OnSelectOther               (BOOL isOther2,int curSel,int& newSel);
    BOOL                    GetOtherColor               (AcCmColor& defaultColor,
        const AcCmColor& layerColor,
        BOOL enableMetaColors);
    BOOL                    GetWindowsColor             (AcCmColor& color);
    virtual BOOL            GetOtherName                (BOOL isOther2, CString& name);


    // AcCmColor Table
    AcCmColor *             m_AcCmColorTable[ACUI_TRUECOLOR_COMBOBOX_TABLE_SIZE];
    int                     m_nextAcCmColorTableIndex;

    void                    initAcCmColorTable          (void);

    // Color Utilities
    void                    RGBFill                     (CDC& dc, CRect& rFill);

    bool                    GetCurrentLayerColor        (AcCmColor& color);

    virtual COLORREF        LookupColor                 (int colorIndex, LOGPALETTE *logPalette);

    afx_msg void            OnDrawItem                  (int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);

    // ClassWizard-controlled
public:
    //{{AFX_VIRTUAL(CAcUiTrueColorComboBox)
    //}}AFX_VIRTUAL

protected:
    //{{AFX_MSG(CAcUiTrueColorComboBox)
    //}}AFX_MSG

    DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////////

class ACUI_PORT CAcUiLineWeightComboBox : public CAcUiMRUComboBox {
public:
    CAcUiLineWeightComboBox ();
    virtual ~CAcUiLineWeightComboBox ();

    // MRU control
protected:
    virtual void    DrawItemImage (CDC& dc, CRect& r, INT_PTR cargo);
    virtual void    OnAddItems ();

    // LineWeight control
protected:
    double  m_lineWeightScale;

public:
    int     FindItemByLineWeight (int lw);  // Get corresponding item index.
    int     GetCurrentItemLineWeight ();    // Get current item's LW (or -1).
    int     GetCurrentLayerLineWeight ();
    int     GetItemLineWeight (int item);   // Get item's LW (or -1).
    double  GetLineWeightScale ();
    void    SetLineWeightScale (double scale);
    void    SetUseDefault(BOOL b);
    virtual int     ImageWidth ();    
private:
    BOOL    m_bUseDefault;

    // ClassWizard-controlled
public:
    //{{AFX_VIRTUAL(CAcUiLineWeightComboBox)
    //}}AFX_VIRTUAL

protected:
    //{{AFX_MSG(CAcUiLineWeightComboBox)
    //}}AFX_MSG

    DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////////

class ACUI_PORT CAcUiArrowHeadComboBox : public CAcUiMRUComboBox {
public:
    CAcUiArrowHeadComboBox ();
    virtual ~CAcUiArrowHeadComboBox ();

    // MRU control
protected:
    virtual void    DrawItemImage (CDC& dc, CRect& r, INT_PTR cargo);
    virtual int     CalcItemHeight ();
    virtual BOOL    GetOtherName (BOOL isOther2, CString& name);
    virtual void    OnAddItems ();

    /// <summary>
    /// Loads or reloads the images used by items in the combo box.
    /// Call this method in a themed environment after a theme change.
    /// </summary>
    /// <returns>
    /// True if successful or false otherwise.
    /// </returns>
    virtual bool    LoadImages ();

    // Aliases for Option2
public:        
    BOOL    GetUseOrigin2 ();
    void    SetUseOrigin2 (BOOL use);

    // ArrowHead control
private:
    CAdUiImage* m_pArrowImages;
    int     m_arrowCount;           // Number of images in bitmap
    int     m_arrowSize;            // Image height and width in pixels
    BOOL    m_bUseOrigin2;
    BOOL    m_bThemedArrowImagesLoaded;


public:
    int     AddArrowHeadToMRU (LPCTSTR name);   // Returns item index (or -1).
    virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);

    // ClassWizard-controlled
public:
    //{{AFX_VIRTUAL(CAcUiArrowHeadComboBox)
    //}}AFX_VIRTUAL

protected:
    //{{AFX_MSG(CAcUiArrowHeadComboBox)
    //}}AFX_MSG

    DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////////

class ACUI_PORT CAcUiPlotStyleTablesComboBox : public CAcUiMRUComboBox {
public:
    CAcUiPlotStyleTablesComboBox ();
    CAcUiPlotStyleTablesComboBox (BOOL bInitialize);        
    virtual ~CAcUiPlotStyleTablesComboBox ();
    // NOTE: to show color style tables, set both currentDrawing and named to false
    void    SetFileType(bool currentDrawing, bool named);
    int     AddMissingStyleTable(LPCTSTR fullFileName, bool bMissing = true);
    bool    IsMissing(int index);

    virtual int     ImageWidth ();    // Override to allow setting of 0 image width. INTERNAL USE ONLY

    // override getLBText to account for the (missing) string thing
    void GetLBText(int nIndex, CString& rString) const;     // INTERNAL USE ONLY

    // Override to sort correctly.                          // INTERNAL USE ONLY
    int     AddItemToList (LPCTSTR name,    INT_PTR cargo);        
    // MRU control
protected:
    virtual void    DrawItemImage (CDC& dc, CRect& r, INT_PTR cargo);   // INTERNAL USE ONLY
    virtual int     CalcItemHeight ();                              // INTERNAL USE ONLY
    virtual void    OnAddItems ();
    virtual void    OnComboBoxInit ();                              // INTERNAL USE ONLY

    // ArrowHead control
private:
    CBitmap m_plotStyleTablesBitmap;
    int     m_plotStyleTableBitmapSize;         // Image height and width in pixels
    BOOL    m_bImageDisplayed;                  // TRUE if image is displayed in the list.
    bool    m_bCurrentDrawing;   // Which kind of style table to populate the list with.
    bool    m_bNamed;
    BOOL    m_bInitialize;      // TRUE to initialize the contents at create time.
    // ClassWizard-controlled
public:
    //{{AFX_VIRTUAL(CAcUiPlotStyleTablesComboBox)
    virtual BOOL OnChildNotify(UINT, WPARAM, LPARAM, LRESULT*);
    //}}AFX_VIRTUAL

protected:
    //{{AFX_MSG(CAcUiPlotStyleTablesComboBox)
    afx_msg BOOL OnDropDown();
    //}}AFX_MSG

    DECLARE_MESSAGE_MAP()

private:
    BOOL AdjustDropDownListWidth(void);
};

//////////////////////////////////////////////////////////////////////////////

class ACUI_PORT CAcUiPlotStyleNamesComboBox : public CAcUiMRUComboBox {
public:
    CAcUiPlotStyleNamesComboBox ();
    virtual ~CAcUiPlotStyleNamesComboBox ();
    virtual int     ImageWidth ();    // Override to allow setting of 0 image width. INTERNAL USE ONLY
    void            OtherRunsSelectPlotStyle() {m_whatOtherDoes = 0; }
    void            OtherRunsCurrentPlotStyle() {m_whatOtherDoes = 1; }
    void            OtherRunsDefault() {m_whatOtherDoes = -1;}
    void            SetAllowByLayerByBlock(BOOL bAllow) {m_bAllowByLayerByBlock = bAllow;}
    void            SetColorDependentMode();
    void            SetNamedMode();

protected:
    virtual void    OnAddItems ();
    virtual BOOL    OnSelectOther (BOOL isOther2, int curSel, int& newSel); // INTERNAL USE ONLY
    virtual void    OnComboBoxInit ();                                      // INTERNAL USE ONLY       

private:
    // -1 to leave up to control, 0 to run select plot style, 1 to run curent plot style.
    int m_whatOtherDoes;

    // TRUE if this control is in color depedent mode.
    BOOL m_bColorDependentMode;

    // If TRUE the following allows the selection of ByLayer/ByBlock in
    // the "Other..." dialog.
    BOOL m_bAllowByLayerByBlock;

    // Save the last set named mode settings for using ByBlock, ByLayer
    // and Other... when switched to color dependent mode.
    BOOL m_bLastByBlock;
    BOOL m_bLastByLayer;
    BOOL m_bLastUseOther;        

    // ClassWizard-controlled
public:
    //{{AFX_VIRTUAL(CAcUiPlotStyleNamesComboBox)
    //}}AFX_VIRTUAL

protected:
    //{{AFX_MSG(CAcUiPlotStyleNamesComboBox)
    //}}AFX_MSG

    DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////////

class ACUI_PORT CAcUiPredefBlockComboBox : public CAcUiMRUComboBox {
public:
    CAcUiPredefBlockComboBox ();
    virtual ~CAcUiPredefBlockComboBox ();

    // MRU control
protected:
    virtual void    DrawItemImage (CDC& dc, CRect& r, INT_PTR cargo);
    virtual int     CalcItemHeight ();
    virtual BOOL    GetOtherName (BOOL isOther2, CString& name);
    virtual void    OnAddItems ();

    /// <summary>
    /// Loads or reloads the images used by items in the combo box.
    /// Call this method in a themed environment after a theme change.
    /// </summary>
    /// <returns>
    /// True if successful or false otherwise.
    /// </returns>
    virtual bool    LoadImages ();

    // PredefBlock control
private:
    CAdUiImage* m_pBlockImages;
    int     m_blockCount;           // Number of images in bitmap
    int     m_blockSize;            // Image height and width in pixels
    BOOL    m_bThemedBlockImagesLoaded;

public:
    int     AddPredefBlockToMRU (LPCTSTR name);   // Returns item index (or -1).

    // ClassWizard-controlled
public:
    //{{AFX_VIRTUAL(CAcUiPredefBlockComboBox)
    //}}AFX_VIRTUAL

protected:
    //{{AFX_MSG(CAcUiPredefBlockComboBox)
    //}}AFX_MSG

    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#pragma pack (pop)
#endif

/////////////////////////////////////////////////////////////////////////////
