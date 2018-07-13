//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2018 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////


#ifndef _acuiListBox_h
#define _acuiListBox_h
#pragma pack (push, 8)

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CAcUiListBox window

/*
class ACUI_PORT CAcUiListBox : public CAdUiListBox {
//    DECLARE_DYNAMIC(CAcUiListBox);

public:
                CAcUiListBox ();
virtual         ~CAcUiListBox ();

// ClassWizard-controlled
public:
    //{{AFX_VIRTUAL(CAcUiListBox)
    //}}AFX_VIRTUAL
protected:
    //{{AFX_MSG(CAcUiListBox)
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};
*/
//typedef CAdUiListBox    CAcUiListBox;
//The first release (2/2002) of the VC7 compiler has
//a bug that causes the above typedef not to work
//properly in certain situations.
//Here's some minimal code that demonstrates the problem.
//If/when they fix the problem we can go back using
//the typedef.
/*
class A 
{
protected:
    static void f() {}
};

typedef A B;

class C : public B
{
    static void* p;
};
void * C::p = &B::f;  //error C2248: 'A::f' : cannot access protected member declared in class 'A'

void main()
{
}
*/
#define CAcUiListBox CAdUiListBox
/////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#pragma pack (pop)
#endif

/////////////////////////////////////////////////////////////////////////////
