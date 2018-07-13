//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2018 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////

#ifndef _acuiEdit_h
#define _acuiEdit_h
#pragma pack (push, 8)

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////

// data styles
#define AC_ES_STRING                        0x01	
#define	AC_ES_SYMBOL                        0x02
#define AC_ES_NUMERIC                       0x04
#define AC_ES_ANGLE                         0x08

// behavior styles
#define AC_ES_VAL_ONKILLFOCUS               0x10
#define AC_ES_CONV_ONKILLFOCUS              0x20
#define AC_ES_SHOW_ERRMSG                   0x40
#define AC_ES_ERRMSG_ALLOWIGNORE            0x80

// validation styles
#define AC_ES_NOZERO                        0x100
#define AC_ES_NOBLANK                       0x200	
#define AC_ES_NONEGATIVE                    0x400
#define	AC_ES_INRANGE                       0x800

typedef enum {
    kAcUiError_None,                    // No error; OK.
    kAcUiError_Blank,                   // Data is blank
    kAcUiError_Symbol,                  // Detected illegal symbol syntax
    kAcUiError_Numeric,                 // Detected non-numeric data
    kAcUiError_Angle,                   // Data does not represent an angle
    kAcUiError_Zero,                    // Data is zero
    kAcUiError_Negative,                // Data is negative
    kAcUiError_Range                    // Data is out of range
} ACUI_ERROR_CODE;

////////////////////////////////////////////////////////////////////////////
// CAcUiEdit window
class ACUI_PORT CAcUiEdit : public CAdUiEdit {
    DECLARE_DYNAMIC(CAcUiEdit)

public:
                CAcUiEdit ();
virtual         ~CAcUiEdit ();

private:
        BOOL    m_bWantsFocus;
        BOOL    m_bWasValid;

protected:
virtual ADUI_REPLY DoAdUiMessage (
                    ADUI_NOTIFY notifyCode, UINT controlId, LPARAM lParam
                );
// Validation style
public:
virtual void    SetStyleMask (DWORD mask);

// Validation
private:
        void    DisplayError (UINT);    // display error dialog box
public:
        BOOL    m_bChanged;             // value changed flag
        double  m_dMinValue;           // min value for range checking
        double  m_dMaxValue;           // max value for range checking
        CString m_csMsg;                // generic message string
        BOOL    m_bTouch;               // flag to detect changes in text

        void    Convert ();             // data style conversion
        BOOL    ConvertData (CString& x);
        BOOL    HasChanged ();          // detect user changes
        void    SetDirty ();
        void    SetRange (double vMin, double vMax);
        BOOL    Validate ();			// data validation
        ACUI_ERROR_CODE ValidateData (CString& x);

// ClassWizard-controlled
public:
	//{{AFX_VIRTUAL(CAcUiEdit)
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(CAcUiEdit)
	afx_msg BOOL OnChange();
    afx_msg void OnErrSpace();
    afx_msg void OnKillFocus(CWnd* pNewWnd);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CAcUiAngleEdit class

class ACUI_PORT CAcUiAngleEdit : public CAcUiEdit {
    DECLARE_DYNAMIC(CAcUiAngleEdit)

public:
                CAcUiAngleEdit ();
virtual         ~CAcUiAngleEdit ();

// Validation style
public:
virtual void    SetStyleMask (DWORD mask);

// ClassWizard-controlled
public:
	//{{AFX_VIRTUAL(CAcUiAngleEdit)
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(CAcUiAngleEdit)
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CAcUiNumericEdit class

class ACUI_PORT CAcUiNumericEdit : public CAcUiEdit {
    DECLARE_DYNAMIC(CAcUiNumericEdit)

public:
                CAcUiNumericEdit ();
virtual         ~CAcUiNumericEdit ();

// Validation style
public:
virtual void    SetStyleMask (DWORD mask);

// ClassWizard-controlled
public:
	//{{AFX_VIRTUAL(CAcUiNumericEdit)
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(CAcUiNumericEdit)
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CAcUiStringEdit class

class ACUI_PORT CAcUiStringEdit : public CAcUiEdit {
    DECLARE_DYNAMIC(CAcUiStringEdit)

public:
	            CAcUiStringEdit ();
virtual         ~CAcUiStringEdit ();

// Validation style
public:
virtual void    SetStyleMask (DWORD mask);

// ClassWizard-controlled
public:
	//{{AFX_VIRTUAL(CAcUiStringEdit)
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(CAcUiStringEdit)
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CAcUiSymbolEdit class

class ACUI_PORT CAcUiSymbolEdit : public CAcUiEdit {
    DECLARE_DYNAMIC(CAcUiSymbolEdit)

public:
                CAcUiSymbolEdit ();
virtual         ~CAcUiSymbolEdit ();

// Validation style
public:
virtual void    SetStyleMask (DWORD mask);

// ClassWizard-controlled
public:
	//{{AFX_VIRTUAL(CAcUiSymbolEdit)
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(CAcUiSymbolEdit)
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#pragma pack (pop)
#endif

/////////////////////////////////////////////////////////////////////////////
