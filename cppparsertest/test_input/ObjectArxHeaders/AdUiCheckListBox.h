//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2018 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////

#pragma once


/// <summary>
/// Represents a CCheckListBox supporting high DPI display and customizations.
/// </summary>
class ADUI_PORT CAdUiCheckListBox : public CCheckListBox
{
    DECLARE_DYNAMIC(CAdUiCheckListBox)
public:
    CAdUiCheckListBox();
    virtual ~CAdUiCheckListBox();


    // Attributes
public:

    /// <summary>
    /// Enables in-place tooltip when an item cannot be fully displayed.
    /// </summary>
    void EnableItemToolTip();

    /// <summary>
    /// Specifies how items are displayed when exceeding the width of the control's client area.
    /// </summary>
    enum HorizontalStyle
    {
        /// <summary>
        /// Item text is truncated.
        /// </summary>
        kHorizontalClip,
        /// <summary>
        /// Item text is truncated and ellipses are added like DT_END_ELLIPSIS.
        /// </summary>
        kHorizontalEndEllipsis,
        /// <summary>
        /// Characters in the middle are replaced with ellipses like DT_PATH_ELLIPSIS.
        /// </summary>
        kHorizontalPathEllipsis,
        /// <summary>
        /// Item text is truncated and ellipses are added like DT_WORD_ELLIPSIS.
        /// </summary>
        kHorizontalWordEllipsis,
        /// <summary>
        /// A horizontal scroll bar is shown in the control when needed.
        /// For this style to work, the control must have been created with the WS_HSCROLL style.
        /// This style is not applicable to multicolumn list boxes.
        /// </summary>
        kHorizontalScroll,
    };

    /// <summary>
    /// Retrieves the current value of HorizontalStyle for the control.
    /// </summary>
    /// <returns>The current value of HorizontalStyle for the control.</returns>
    HorizontalStyle GetHorizontalStyle() const
    {
        return _horizontalStyle;
    }

    /// <summary>
    /// Specifies how items are displayed when exceeding the width of the control's client area.
    /// </summary>
    /// <param name="style">The HorizontalStyle value to use.</param>
    void SetHorizontalStyle(HorizontalStyle style);


    // Overridables and other helpers
public:

    /// <summary>
    /// Called by the framework for drawing the text portion of an item.
    /// </summary>
    /// <param name="lpDrawItemStruct">
    /// A pointer to a DRAWITEMSTRUCT structure that contains information about the drawing required.
    /// The rcItem member defines the rectangle of the text portion.
    /// The itemAction and itemState members define the drawing action to be performed.
    /// </param>
    /// <remarks>
    /// Before this function is called by the framework, the foreground and background color are already set 
    /// according to the current state of the item using the default color defined by Windows.
    /// The default implementation of this function fills the item background and draws the item text.
    /// Override this function to implement customized drawing, such as items that aren't plain strings.
    /// </remarks>
    virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) override;

    /// <summary>
    /// Called by the framework for determining the heights of the list items.
    /// </summary>
    /// <param name="lpMeasureItemStruct">
    /// A pointer to a MEASUREITEMSTRUCT structure.
    /// </param>
    /// <remarks>
    /// The default implementation calls <see cref="CalcMinimumItemHeight"/> to get the heights of the list items.
    /// If the control is created with the LBS_OWNERDRAWVARIABLE style, the framework calls this member function for each item in the list box.
    /// Otherwise, this member is called only once.
    /// </remarks>
    virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct) override;

protected:

    /// <summary>
    /// Called by the framework for determining the horizontal extent of items.
    /// </summary>
    /// <param name="index">
    /// Specifies the zero-based index of the item whose extent is to be calculated; 
    /// or LB_ERR indicates that all items should be calculated and return the maximum value.
    /// </param>
    /// <param name="text">
    /// Specifies the text of the current item.
    /// The value is nullptr when <paramref name="index"/> is LB_ERR, or when the control was not created with the LBS_HASSTRINGS style.
    /// </param>
    /// <returns>
    /// The horizontal extent of the items to be calculated, in pixels. 
    /// </returns>
    /// <remarks>
    /// The calculation should take into account the checkbox portion of items.
    /// The framework uses the returned value to determine when to show the horizontal scrollbar 
    /// and when to show the tooltip for an item that cannot be fully displayed.
    /// Override this function to implement customized calculation, such as items that aren't plain strings.
    /// </remarks>
    virtual int CalcHorizontalExtent(int index, LPCTSTR text);

    /// <summary>
    /// Called by the framework for determining the rectangles for the checkbox portion and the text portion of an item.
    /// </summary>
    /// <param name="index">
    /// Specifies the zero-based index of the item to be calculated.
    /// </param>
    /// <param name="item">
    /// Specifies the rectangle of the item to be calculated.
    /// </param>
    /// <param name="checkBox">
    /// Specifies a pointer to a CRect that receives the rectangle of the checkbox portion; 
    /// or nullptr indicates this information is not needed in this call.
    /// </param>
    /// <param name="text">
    /// Specifies a pointer to a CRect that receives the rectangle of the text portion; 
    /// or nullptr indicates this information is not needed in this call.
    /// </param>
    /// <remarks>
    /// The framework uses the returned values to determine the sizes and the layout of the checkbox portion and the text portion of an item.
    /// Override this function to implement customization such as displaying the checkbox at the right side.
    /// </remarks>
    virtual void CalcItemParts(int index, const CRect& item, CRect* checkBox, CRect* text);

    /// <summary>
    /// Called by the framework for determining the minimum height for the items.
    /// </summary>
    /// <returns>
    /// The minimum height for the items, in pixels.
    /// </returns>
    virtual int CalcMinimumItemHeight();

    /// <summary>
    /// Called by the framework for drawing the checkbox portion of an item.
    /// </summary>
    /// <param name="lpDrawItemStruct">
    /// A pointer to a DRAWITEMSTRUCT structure that contains information about the drawing required.
    /// The rcItem member defines the rectangle of the checkbox portion.
    /// </param>
    /// <remarks>
    /// Override this function to implement customized checkboxes.
    /// </remarks>
    virtual void DrawCheckBox(LPDRAWITEMSTRUCT lpDrawItemStruct);

    /// <summary>
    /// Called by the framework for drawing a rectangle to indicate that the item has the focus.
    /// </summary>
    /// <param name="lpDrawItemStruct">
    /// A pointer to a DRAWITEMSTRUCT structure that contains information about the drawing required.
    /// The rcItem member defines the rectangle of the item.
    /// </param>
    virtual void DrawFocus(LPDRAWITEMSTRUCT lpDrawItemStruct);

    /// <summary>
    /// Called by the framework for determining whether and how a tooltip should be displayed, 
    /// if in-place tooltip for an item is enabled on this control.
    /// </summary>
    /// <param name="index">
    /// Specifies the zero-based index of the item.
    /// </param>
    /// <param name="item">
    /// Specifies the rectangle of the item.
    /// </param>
    /// <param name="mouse">
    /// Specifies the coordinates of the cursor, relative to the upper-left corner of the control.
    /// </param>
    /// <param name="tipPosition">
    /// Specifies the location of the tooltip, relative to the upper-left corner of the control.
    /// By default, the value is the top-left corner of the text portion in the current item.
    /// Change the value to provide a customized location.
    /// </param>
    /// <param name="tipText">
    /// Specifies the text of the tooltip.
    /// By default, the value is the text of the current item.
    /// Change the value to provide a customized tooltip text.
    /// </param>
    /// <returns>
    /// true if the tooltip should be displayed for the current item; otherwise, false.
    /// </returns>
    virtual bool OnItemToolTip(int index, const CRect& item, const CPoint& mouse, CPoint& tipPosition, CString& tipText);


    // Helpers hiding buggy implementation of base class
    int CheckFromPoint(CPoint point, BOOL& checkBox);
    void InvalidateCheck(int index);
    void PreDrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);


    // Implementation
public:
    virtual void DeleteItem(LPDELETEITEMSTRUCT lpDeleteItemStruct) override;
    virtual void PreSubclassWindow() override;
protected:
    virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam) override;
    virtual BOOL OnChildNotify(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult) override;
    DECLARE_MESSAGE_MAP()
    afx_msg void OnDestroy();
    afx_msg LRESULT OnLBAddString(WPARAM wParam, LPARAM lParam);
    afx_msg LRESULT OnLBInsertString(WPARAM wParam, LPARAM lParam);
    afx_msg LRESULT OnLBResetContent(WPARAM wParam, LPARAM lParam);
    afx_msg LRESULT OnLBSetItemHeight(WPARAM wParam, LPARAM lParam);
    afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    afx_msg void OnSetFont(CFont* pFont, BOOL bRedraw);
private:
    BOOL OnLButtonDown(int index, BOOL checkBox);
    bool ToolTip();
private:
    bool _deleteItem;
    HorizontalStyle _horizontalStyle;
    CToolTipCtrl* _toolTipCtrl;
};
