//
//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2018 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
//
// dbtexteditor.h
//
#pragma once

#include "acadstrc.h"
#include "dbmtext.h"
#include "AcString.h"
#include "PAL/api/charset.h"

class TextEditor;
class TextEditorLocation;

class AcDbTextEditor;

class AcDbTextEditorColumn;
class AcDbTextEditorParagraph;
class AcDbTextEditorParagraphIterator;

class AcDbImpTextEditorParagraph;
class AcDbImpTextEditorParagraphIterator;
class AcDbImpTextEditorColumn;

class AcDbTextEditorParagraphTab;
class AcDbImpTextEditorParagraphTab;

class AcDbTextEditorStack;
class AcDbImpTextEditorStack;

class AcDbImpTextEditorSelectionBase;
class AcDbImpTextEditorCursor;
class AcDbImpTextEditorSelection;

///<summary> 
/// The AcDbTextEditorLocation represent information about the location in the 
/// core text editor. When you have the object, you can call the functions in the
/// AcDbTextEditor like makeSelection(), findText() and so on.
/// Note that the location in text editor is volatile object. If you saved one location,
/// then call some some functions (for example the columns setting functions, paragraph
/// setting function, selection/cursor inserting functions and so on.)who will make text 
/// editor re-wrap itself. The saved location is in invalid state.
///</summary>
class AcDbTextEditorLocation
{
public:
    ///<summary> 
    /// Delete this AcDbTextEditorLocation.
    ///</summary>
    ACDBCORE2D_PORT void release();

private:
    ~AcDbTextEditorLocation();
    AcDbTextEditorLocation();
    bool operator==(const AcDbTextEditorLocation& other);

    friend class AcDbTextEditor;
    friend class AcDbTextEditorServices;
    friend class AcDbTextEditorCursor;

    TextEditorLocation* m_pImp;
};

///<summary> 
/// The AcDbTextEditorSelectable is a pure interface to represent the locations for
/// the start and end position of the selectable objects in text editor. 
///</summary>
class AcDbTextEditorSelectable
{
public:
    virtual ~AcDbTextEditorSelectable() { };

    ///<summary> 
    /// Gets the start location of a selectable object.
    ///</summary>
    /// <returns>
    /// Returns an AcDbTextEditorLocation object for the start of a selectable object.
    /// </returns>
    virtual AcDbTextEditorLocation* startOfText() = 0;
    ///<summary> 
    /// Gets the end location of a selectable object.
    ///</summary>
    /// <returns>
    /// Returns an AcDbTextEditorLocation object for the end of a selectable object.
    /// </returns>
    virtual AcDbTextEditorLocation* endOfText() = 0;
};

///<summary> 
/// The AcDbTextEditorSelectionBase is the base class for the AcDbTextEditorCursor
/// and AcDbTextEditorSelection. It includes all the common functions for the two
/// classes. After you call the functions via AcDbTextEditorSelection object it will 
/// change the properties for the whole selection. If you call the function via the
/// AcDbTextEditorCursor all the input text properties after the current cursor will
/// be changed.
///</summary>
class AcDbTextEditorSelectionBase
{
public:
    /// <summary>
    /// This enumerator describe the flow align types.
    /// </summary>
    enum FlowAlign
    {
        /// <summary>
        /// The flow type is base align.
        /// </summary>
        kFlowBase,
        /// <summary>
        /// The flow type is center align.
        /// </summary>
        kFlowCenter,
        /// <summary>
        /// The flow type is top align.
        /// </summary>
        kFlowTop
    };

    /// <summary>
    /// This enumerator describe the insert text format types.
    /// </summary>
    enum InsertTextType {
        /// <summary>
        /// The insert text is in unicode MText format.
        /// </summary>
        kUnicodeMTextFormat,
        /// <summary>
        /// The insert text is in MText format.
        /// </summary>
        kMTextFormat,
        /// <summary>
        /// The insert text is in rich text format.
        /// </summary>
        kRichTextFormat,
        /// <summary>
        /// The insert text is in unicode DText format.
        /// </summary>
        kUnicodeDTextFormat,
        /// <summary>
        /// The insert text is in DText format.
        /// </summary>
        kDTextFormat,
        /// <summary>
        /// The insert text is in unicode text format.
        /// </summary>
        kUnicodeTextFormat,
        /// <summary>
        /// The insert text is in multibyte text format.
        /// </summary>
        kMultibyteTextFormat
    };

    ///<summary> 
    /// Set current language. Now we only support the following charset:
    /// ANSI_CHARSET
    /// GB2312_CHARSET
    /// HANGEUL_CHARSET
    /// CHINESEBIG5_CHARSET
    /// SHIFTJIS_CHARSET
    /// HEBREW_CHARSET
    /// ARABIC_CHARSET
    /// GREEK_CHARSET
    /// TURKISH_CHARSET
    /// VIETNAMESE_CHARSET
    /// THAI_CHARSET
    /// EASTEUROPE_CHARSET
    /// RUSSIAN_CHARSET
    /// BALTIC_CHARSET
    /// DEFAULT_CHARSET
    /// If you set the language for the current selection, you should check if the
    /// current selection supports the language. Otherwise it will return Acad::eInvalidInput.
    /// If you input DEFAULT_CHARSET, the language will be set the default language
    /// the system is currently running on. 
    ///</summary>
    /// <param name="charset">CharSet of language to set.</param>
    /// <returns>
    /// Returns Acad::eOk if the operation succeeded.
    /// Returns Acad::eInvalidInput if the operation fails.
    /// </returns>
    ACDBCORE2D_PORT Acad::ErrorStatus setLanguage(Charset charset);
    ///<summary> 
    /// Get current language.
    ///</summary>
    /// <returns>
    /// Returns current language.
    /// </returns>
    ACDBCORE2D_PORT Charset               language() const;

    ///<summary> 
    /// Set current font. If you set the font for the current selection, you 
    /// should check if the current selection supports the font. Otherwise it 
    /// will return Acad::eInvalidInput.
    ///</summary>
    /// <param name="fontname">Font name.</param>
    /// <param name="bTrueType">True if font is a TrueType font.</param>
    /// <returns>
    /// Returns Acad::eOk if the operation succeeded.
    /// Returns Acad::eInvalidInput if the operation fails.
    /// </returns>
    ACDBCORE2D_PORT Acad::ErrorStatus setFont(const AcString& fontname, bool bTrueType);
    ///<summary> 
    /// Get current font name. If the font is a SHX font, the returned name has 
    /// the .SHX extension.
    ///</summary>
    /// <returns>
    /// Returns current font name.
    /// </returns>
    ACDBCORE2D_PORT AcString          font() const;

    ///<summary> 
    /// Check if current font is a TrueType font.
    ///</summary>
    /// <returns>
    /// Returns true if current font is TrueType.
    /// </returns>
    ACDBCORE2D_PORT bool              isTrueType() const;

    ///<summary> 
    /// Set the text height of selectable object .
    ///</summary>
    /// <param name="height">Value to set. It should be positive value.</param>
    /// <returns>
    /// Returns Acad::eOk if the operation succeeded.
    /// Returns Acad::eInvalidInput if the operation fails.
    /// </returns>
    ACDBCORE2D_PORT Acad::ErrorStatus setHeight(double height);
    ///<summary> 
    /// Get current text height.
    ///</summary>
    /// <returns>
    /// Returns current text height.
    /// </returns>
    ACDBCORE2D_PORT double            height() const;

    ///<summary> 
    /// Get current text color. This can apply to a selection or to the current cursor.
    ///</summary>
    /// <param name="color">The input color.</param>
    /// <returns>
    /// Returns Acad::eOk if the operation succeeded.
    /// Returns Acad::eInvalidInput if the operation fails.
    /// </returns>
    ACDBCORE2D_PORT Acad::ErrorStatus setColor(const AcCmColor& color);
    ///<summary> 
    /// Get current text color.
    ///</summary>
    /// <returns>
    /// Returns AcCmColor of current text.
    /// </returns>
    ACDBCORE2D_PORT AcCmColor         color() const;

    ///<summary> 
    /// Toggles bold state. This can apply to a selection or to the current cursor.
    /// If the current selectable object's font is SHX, there is no effect after 
    /// toggling bold.
    ///</summary>
    /// <returns>
    /// Returns Acad::eOk if the operation succeeded.
    /// Returns Acad::eInvalidInput if the operation fails.
    /// </returns>
    ACDBCORE2D_PORT Acad::ErrorStatus toggleBold();
    ///<summary> 
    /// Get current bold state.
    ///</summary>
    /// <returns>
    /// Returns true if bold is on, false otherwise.
    /// </returns>
    ACDBCORE2D_PORT bool              bold() const;

    ///<summary> 
    /// Toggles italic state. This can apply to a selection or to the current cursor.
    /// If the current selectable object's font is SHX, there is no effect after 
    /// toggling italic.
    ///</summary>
    /// <returns>
    /// Returns Acad::eOk if the operation succeeded.
    /// Returns Acad::eInvalidInput if the operation fails.
    /// </returns>
    ACDBCORE2D_PORT Acad::ErrorStatus toggleItalic();
    ///<summary> 
    /// Get current italic state.
    ///</summary>
    /// <returns>
    /// Returns true if italic is on, false otherwise.
    /// </returns>
    ACDBCORE2D_PORT bool              italic() const;

    ///<summary> 
    /// Toggles underline state. This can apply to a selection or to the current
    /// cursor.
    ///</summary>
    /// <returns>
    /// Returns Acad::eOk if the operation succeeded.
    /// Returns Acad::eInvalidInput if the operation fails.
    /// </returns>
    ACDBCORE2D_PORT Acad::ErrorStatus toggleUnderline();
    ///<summary> 
    /// Get current underline state.
    ///</summary>
    /// <returns>
    /// Returns true if underline is on, false otherwise.
    /// </returns>
    ACDBCORE2D_PORT bool              underline() const;

    ///<summary> 
    /// Toggles overline state. This can apply to a selection or to the current cursor.
    ///</summary>
    /// <returns>
    /// Returns Acad::eOk if the operation succeeded.
    /// Returns Acad::eInvalidInput if the operation fails.
    /// </returns>
    ACDBCORE2D_PORT Acad::ErrorStatus toggleOverline();
    ///<summary> 
    /// Get current overline state.
    ///</summary>
    /// <returns>
    /// Returns true if overline is on, false otherwise.
    /// </returns>
    ACDBCORE2D_PORT bool              overline() const;

    ///<summary> 
    /// Toggles strikethrough state. This can apply to a selection or to the current cursor.
    ///</summary>
    /// <returns>
    /// Returns Acad::eOk if the operation succeeded.
    /// Returns Acad::eInvalidInput if the operation fails.
    /// </returns>
    ACDBCORE2D_PORT Acad::ErrorStatus toggleStrikethrough();
    ///<summary> 
    /// Get current strikethrough state.
    ///</summary>
    /// <returns>
    /// Returns true if overline is on, false otherwise.
    /// </returns>
    ACDBCORE2D_PORT bool              strikethrough() const;

    ///<summary> 
    /// Set oblique angle. This can apply to a selection or to the current 
    /// cursor.
    ///</summary>
    /// <param name="angle">Oblique angle. The value must be between the AcDbTextEditorSelectionBase::minObliqueAngle()
    /// and AcDbTextEditorSelectionBase::maxObliqueAngle(). </param>
    /// <returns>
    /// Returns Acad::eOk if the operation succeeded.
    /// Returns Acad::eInvalidInput if the operation fails.
    /// </returns>
    ACDBCORE2D_PORT Acad::ErrorStatus setObliqueAngle(double angle);

    ///<summary> 
    /// Get oblique angle. This can apply to a selection or to the current 
    /// cursor.
    ///</summary>
    /// <returns>
    /// Returns oblique angle.
    /// </returns>
    ACDBCORE2D_PORT double            obliqueAngle() const;

    ///<summary> 
    /// Set tracking factor. This can apply to a selection or to the current 
    /// cursor.
    ///</summary>
    /// <param name="angle">Tracking factor. The value must be between the AcDbTextEditorSelectionBase::minTrackingFactor()
    /// and AcDbTextEditorSelectionBase::maxTrackingFactor().</param>
    /// <returns>
    /// Returns Acad::eOk if the operation succeeded.
    /// Returns Acad::eInvalidInput if the operation fails.
    /// </returns>
    ACDBCORE2D_PORT Acad::ErrorStatus setTrackingFactor(double factor);

    ///<summary> 
    /// Get tracking factor.
    ///</summary>
    /// <returns>
    /// Returns tracking factor.
    /// </returns>
    ACDBCORE2D_PORT double            trackingFactor() const;

    ///<summary> 
    /// Set width scale for each character. This can apply to the characters in
    /// a selection or to the current cursor.
    ///</summary>
    /// <param name="angle">Width scale. The value must be between the AcDbTextEditorSelectionBase::minWidthScale()
    /// and AcDbTextEditorSelectionBase::maxWidthScale().</param>
    /// <returns>
    /// Returns Acad::eOk if the operation succeeded.
    /// Returns Acad::eInvalidInput if the operation fails.
    /// </returns>
    ACDBCORE2D_PORT Acad::ErrorStatus setWidthScale(double scale);
    ///<summary> 
    /// Get width scale.
    ///</summary>
    /// <returns>
    /// Returns width scale.
    /// </returns>
    ACDBCORE2D_PORT double            widthScale() const;

    ///<summary> 
    /// Set flow align.
    ///</summary>
    /// <param name="flowAlign">Flow align.</param>
    /// <returns>
    /// Returns Acad::eOk if the operation succeeded.
    /// Returns Acad::eInvalidInput if the operation fails.
    /// </returns>
    ACDBCORE2D_PORT Acad::ErrorStatus setFlowAlign(FlowAlign flowAlign);
    ///<summary> 
    /// Get flow align.
    ///</summary>
    /// <returns>
    /// Returns flow align.
    /// </returns>
    ACDBCORE2D_PORT FlowAlign         flowAlign() const;

    ///<summary> 
    /// Minimum allowable oblique angle.
    ///</summary>
    /// <returns>
    /// Returns minimum allowable oblique angle.
    /// </returns>
    ACDBCORE2D_PORT static double     minObliqueAngle();
    ///<summary> 
    /// Maximum allowable oblique angle.
    ///</summary>
    /// <returns>
    /// Returns maximum allowable oblique angle.
    /// </returns>
    ACDBCORE2D_PORT static double     maxObliqueAngle();
    ///<summary> 
    /// Minimum allowable tracking factor.
    ///</summary>
    /// <returns>
    /// Returns minimum allowable tracking factor.
    /// </returns>
    ACDBCORE2D_PORT static double     minTrackingFactor();
    ///<summary> 
    /// Maximum allowable tracking factor.
    ///</summary>
    /// <returns>
    /// Returns maximum allowable tracking factor.
    /// </returns>
    ACDBCORE2D_PORT static double     maxTrackingFactor();
    ///<summary> 
    /// Minimum allowable width scale.
    ///</summary>
    /// <returns>
    /// Returns minimum allowable width scale.
    /// </returns>
    ACDBCORE2D_PORT static double     minWidthScale();
    ///<summary> 
    /// Maximum allowable width scale.
    ///</summary>
    /// <returns>
    /// Returns maximum allowable width scale.
    /// </returns>
    ACDBCORE2D_PORT static double     maxWidthScale();

    ///<summary> 
    /// Insert a symbol. If you call the function via the current selection object,
    /// it will delete the current text editor selection.
    ///</summary>
    /// <param name="wch">Insert symbol.</param>
    /// <param name="charset">Language type. If you input a -1, 
    /// it will insert the symbol using the current keyboard charset.</param>
    /// <returns>
    /// Returns Acad::eOk if the operation succeeded.
    /// Returns Acad::eInvalidInput if the operation fails.
    /// </returns>
    ACDBCORE2D_PORT Acad::ErrorStatus insertSymbol(ACHAR wch, Charset charset);

    ///<summary> 
    /// Insert a string. If you call the function via the current selection object,
    /// it will delete the current text editor selection.
    ///</summary>
    /// <param name="str">Insert string.</param>
    /// <returns>
    /// Returns Acad::eOk if the operation succeeded.
    /// Returns Acad::eInvalidInput if the operation fails.
    /// </returns>
    ACDBCORE2D_PORT Acad::ErrorStatus insertString(const AcString& str);

    ///<summary> 
    /// Insert Text. The text can come from some import operation. The type of 
    /// text is defined with InsertTextType. If you call the function via the 
    /// current selection object, it will delete the current text editor selection.
    ///</summary>
    /// <param name="insertType">InsertTextType type of text.</param>
    /// <param name="pData">Imported text to be inserted.</param>
    /// <returns>
    /// Returns Acad::eOk if the operation succeeded.
    /// Returns Acad::eInvalidInput if the operation fails.
    /// </returns>
    ACDBCORE2D_PORT Acad::ErrorStatus insertImportedText(InsertTextType insertType, void * pData);

    ///<summary> 
    /// Move current cursor position or delete character. If you call the function
    /// via the current selection object, it will delete the current text editor 
    /// selection. You can input the following chars:
    /// VK_LEFT,
    /// VK_RIGHT,
    /// VK_UP,
    /// VK_DOWN,
    /// VK_HOME,
    /// VK_END,
    /// VK_PRIOR,
    /// VK_NEXT,
    /// VK_BACK,
    /// VK_DELETE
    ///</summary>
    /// <param name="c">Input char.</param>
    /// <returns>
    /// Returns Acad::eOk if the redo succeeded.
    /// Returns Acad::eInvalidInput if the operation fails.
    /// </returns>
    ACDBCORE2D_PORT Acad::ErrorStatus inputSpecialChar(Adesk::UInt32 c);

    ///<summary> 
    /// Insert a column break code.  A kColumnBreakCode is inserted. If the column
    /// type is AcDbMText::kNoColumns, it will return Acad::eInvalidInput. 
    /// If you call the function via the current selection object, it will delete
    /// the current text editor selection.
    ///</summary>
    /// <returns>
    /// Returns Acad::eOk if the operation succeeds.
    /// Returns Acad::eInvalidInput if the operation fails.
    /// </returns>
    ACDBCORE2D_PORT Acad::ErrorStatus insertColumnBreak();

protected:
    AcDbTextEditorSelectionBase();
    virtual ~AcDbTextEditorSelectionBase();
    AcDbTextEditorSelectionBase(const AcDbTextEditorSelectionBase&);
    AcDbTextEditorSelectionBase& operator=(const AcDbTextEditorSelectionBase&);

    friend class AcDbTextEditor;
    AcDbImpTextEditorSelectionBase* m_pImp;
};

///<summary> 
/// The AcDbTextEditorSelection represents the current selection object in text 
/// editor. From the class you can get/set the selected stack and change the stack
/// properties. Note that after called the AcDbTextEditor::clearSelection() function,
/// the text editor doesn't have a valid selection and if you call the functions
/// in the class it will give you the error code to imply that it has empty selection.
/// After called the AcDbTextEditor::makeSelection() or AcDbTextEditor::selectAll() 
/// there is a valid selection object in editor and you get the selection to call its 
/// functions.
///</summary>
class AcDbTextEditorSelection : public AcDbTextEditorSelectionBase
{
public:
    ///<summary> 
    /// Check if the current selection supports the specified language. If one of 
    /// the characters or the font of the text in the current selection doesn't support
    /// the language, it will return false.
    ///</summary>
    /// <param name="charset">language type. It is one of the languages listed in 
    /// the AcDbTextEditorSelectionBase::setLanguage(int charset) function.</param>
    /// <returns>
    /// Returns true if the current selection supports the language.
    /// Returns false if the current selection doesn't support the language.
    /// </returns>
    ACDBCORE2D_PORT bool languageSupported(Charset charset) const;
    ///<summary> 
    /// Check if the current selection supports the specified font. If one of the 
    /// characters or the language of the text in the current selection doesn't 
    /// support the font, it it will return false.
    ///</summary>
    /// <param name="fontname">font name.</param>
    /// <param name="bTrueType">specify if it is a true type font.</param>
    /// <returns>
    /// Returns true if the current selection supports the font.
    /// Returns false if the current selection doesn't support the font.
    /// </returns>
    ACDBCORE2D_PORT bool fontSupported(const AcString& fontname, bool bTrueType) const;

    ///<summary> 
    /// Check that current selection is stackable. Currently it only can stack the
    /// selected text which contains the following chars:
    /// / this is the horizontal stack;
    /// # this is the diagonal stack;
    /// ^ this is the tolerance stack;
    /// ~ this is the decimal stack.
    ///</summary>
    /// <returns>
    /// Returns true if selection is stackable.
    /// </returns>
    ACDBCORE2D_PORT bool canStack() const;

    ///<summary> 
    /// Stack the contents of the current selection. It uses the default stack scale
    /// factor and alignment (AcDbTextEditor::defaultStackScale() and 
    /// AcDbTextEditor::defaultStackAlignment()) to create the stack.
    ///</summary>
    /// <returns>
    /// Returns Acad::eOk if the contents of the selection was stacked.
    /// Returns Acad::eInvalidInput if the operation fails.
    /// </returns>
    ACDBCORE2D_PORT Acad::ErrorStatus stack();

    ///<summary> 
    /// Check that current selection is unstack able.
    ///</summary>
    /// <returns>
    /// Returns true if selection is stackable.
    /// </returns>
    ACDBCORE2D_PORT bool canUnStack() const;
    ///<summary> 
    /// UnStack the contents of the current selection. After unstacked the text 
    /// will contain the separator chars which specify the stack type:
    /// For the horizontal stack, the separator char is /.
    /// For the diagonal stack, the separator char is #.
    /// For the tolerance stack, the separator char is ^.
    /// For the decimal stack, the separator char is ~.
    /// For the decial stack the unstacked text will also contains the decimal char.
    ///</summary>
    /// <returns>
    /// Returns Acad::eOk if the contents of the selection was un-stacked.
    /// Returns Acad::eInvalidInput if the operation fails.
    /// </returns>
    ACDBCORE2D_PORT Acad::ErrorStatus    unStack();

    ///<summary> 
    ///Check if the single stack object is selected in editor.
    ///</summary>
    /// <returns>
    /// Returns true if the single stack object is active.
    /// </returns>
    ACDBCORE2D_PORT bool     singleStackSelected() const;

    ///<summary> 
    /// Get the stack properties from current selected stack. 
    ///</summary>
    /// <param name="stack">AcDbTextEditorStack object of current stack.</param>
    /// <returns>
    /// Returns Acad::eOk if the operation succeeded.
    /// Returns Acad::eInvalidInput if the operation fails.If there is no
    /// single stack selected, it will return Acad::eNotApplicable.
    /// </returns>
    ACDBCORE2D_PORT Acad::ErrorStatus    getStack(AcDbTextEditorStack& stack) const;
    ///<summary> 
    /// Set the stack properties for the current selected stack. 
    ///</summary>
    /// <param name="stack">The current stack setting you want to set.</param>
    /// <returns>
    /// Returns Acad::eOk if the operation succeeded.
    /// Returns Acad::eInvalidInput if the operation fails. If there is no
    /// single stack selected, it will return Acad::eNotApplicable.
    /// </returns>
    ACDBCORE2D_PORT Acad::ErrorStatus    setStack(const AcDbTextEditorStack& stack);

    ///<summary> 
    /// Get the AcDbTextEditorParagraph associated with the current TextEditor
    /// selection.
    ///</summary>
    /// <param name="paragraphs">Return the paragraphs in the current selection.</param>
    /// <returns>
    /// Returns AcDbTextEditorParagraph for the current selection.
    /// </returns>
    ACDBCORE2D_PORT void paragraph(AcArray<AcDbTextEditorParagraph*>& paragraphs);

    ///<summary> 
    /// Combines selected paragraphs into one paragraph paragraphs.
    ///</summary>
    /// <returns>
    /// Returns Acad::eOk if the paragraphs were combined okay.
    /// Returns Acad::eInvalidInput if the operation fails.
    /// </returns>
    ACDBCORE2D_PORT Acad::ErrorStatus combineParagraphs();

    ///<summary> 
    /// Removes character formatting from the selection. It includes the following
    /// character formatting properties: font, bold, italic, overline, underline,
    /// oblique angle and width scale.
    ///</summary>
    /// <returns>
    /// Returns Acad::eOk if the operation succeeds.
    /// Returns Acad::eInvalidInput if the operation fails.
    /// </returns>
    ACDBCORE2D_PORT Acad::ErrorStatus removeCharacterFormatting();

    ///<summary> 
    /// Removes paragraph formatting from the selection. It includes the following
    /// paragraph formatting properties: first indent, left indent, right indent,
    /// before space, after space, line space factor, line space style, paragraph
    /// alignment, paragraph tabs and numbering.
    ///</summary>
    /// <returns>
    /// Returns Acad::eOk if the operation succeeds.
    /// Returns Acad::eInvalidInput if the operation fails.
    /// </returns>
    ACDBCORE2D_PORT Acad::ErrorStatus removeParagraphFormatting();

    ///<summary> 
    ///Removes character formatting and paragraph formatting from the selection.
    ///</summary>
    /// <returns>
    /// Returns Acad::eOk if the operation succeeds.
    /// Returns Acad::eInvalidInput if the operation fails.
    /// </returns>
    ACDBCORE2D_PORT Acad::ErrorStatus removeAllFormatting();

    ///<summary> 
    /// Check if it can change the case for current selected text. For example it can't
    /// change case for field object.
    ///</summary>
    /// <returns>
    /// Returns true if it can change the case.
    /// Returns false if it can't change the case.
    /// </returns>
    ACDBCORE2D_PORT bool canChangeCase() const;
    ///<summary> 
    /// Change case of characters in the selection to uppercase.
    ///</summary>
    /// <returns>
    /// Returns true if selection changed.
    /// Returns false if no change was made.
    /// </returns>
    ACDBCORE2D_PORT bool changeToUppercase();

    ///<summary> 
    ///Change case of characters in the selection to lowercase.
    ///</summary>
    /// <returns>
    /// returns true if selection changed.
    /// returns false if no change was made.
    /// </returns>
    ACDBCORE2D_PORT bool changeToLowercase();

    ///<summary> 
    /// Get the text content for the current selection.
    ///</summary>
    /// <returns>
    /// Returns text of the current selection.
    /// </returns>
    ACDBCORE2D_PORT Acad::ErrorStatus getSelectionText(AcString& txt) const;

    ///<summary> 
    ///Check if the single field object is selected in editor.
    ///</summary>
    /// <returns>
    /// Returns true if the single field object is active.
    /// </returns>
    ACDBCORE2D_PORT bool     singleFieldSelected() const;

    ///<summary> 
    /// Get AcDbField* pointer if the current selection is a single field. You 
    /// should not delete or close the field object. The life time of the object
    /// is controlled by internal TextEditor object.
    ///</summary>
    /// <returns>
    /// Returns AcDbField* for AcDbTextEditorSelection.
    /// Returns NULL if no field or selection is not a field.
    /// </returns>
    ACDBCORE2D_PORT AcDbField* field() const;

    ///<summary> 
    /// Update the filed object in the text editor.It is only enabled when there is a single active field
    /// object (the isSingleFieldSelected() returns true).
    ///</summary>
    /// <returns>
    /// Returns Acad::eOk if the operation succeeds.
    /// Returns Acad::eInvalidInput if the operation fails. If there is no
    /// single field selected, it will return Acad::eNotApplicable.
    /// </returns>
    ACDBCORE2D_PORT Acad::ErrorStatus  updateField();

    ///<summary> 
    /// Convert the special text object (for example the field object) to plain text.
    /// It is only enabled when there is a single field object selected.
    ///</summary>
    /// <returns>
    /// Returns Acad::eOk if the operation succeeds.
    /// Returns Acad::eInvalidInput if the operation fails. If there is no
    /// single field selected, it will return Acad::eNotApplicable.
    /// </returns>
    ACDBCORE2D_PORT Acad::ErrorStatus  convertToPlainText();
protected:
    ACDBCORE2D_PORT AcDbTextEditorSelection(const TextEditor* pImp);
    ACDBCORE2D_PORT ~AcDbTextEditorSelection();
    AcDbTextEditorSelection(const AcDbTextEditorSelection&);
    AcDbTextEditorSelection& operator=(const AcDbTextEditorSelection&);

    AcDbImpTextEditorSelection* m_pImpSelection;
    friend class TextEditor;
};

///<summary> 
/// The AcDbTextEditorCursor class represents the current cursor object in text
/// editor. User can change the text properties and type text at the current cursor
/// (if you typed new text at the cursor it will have the new properties you set).
/// What's more, user can move the cursor like you do in the other type editor like
/// Notepad. Please note that the current cursor and the current selection object are
/// vice versa completely. If there is a valid selection, there is a NULL cursor object.
/// Otherwise if there is a valid cursor object, the editor has a empty selection. 
/// So if you get the current cursor firstly, then call the AcDbTextEditor::makeSelection()
/// or AcDbTextEditor::selectionAll(). The cursor object you saved is in invalid state.
///</summary>
class AcDbTextEditorCursor : public AcDbTextEditorSelectionBase
{
public:
    ///<summary> 
    /// Get the AcDbTextEditorParagraph associated with the current TextEditor
    /// location.
    ///</summary>
    /// <returns>
    /// Returns AcDbTextEditorParagraph for the current location.
    /// </returns>
    ACDBCORE2D_PORT AcDbTextEditorParagraph* paragraph();

    ///<summary> 
    /// Get the AcDbTextEditorColumn associated with the current TextEditor
    /// location.
    ///</summary>
    /// <returns>
    /// Returns AcDbTextEditorColumn for the current location.
    /// </returns>
    ACDBCORE2D_PORT AcDbTextEditorColumn*    column();
    
    ///<summary> 
    /// Set the AcDbTextEditorLocation associated with the current TextEditor
    /// location.
    ///</summary>
    /// <param name="location">AcDbTextEditorLocation to set.</param>
    /// <returns>
    /// Returns Acad::eOk if the operation succeeds.
    /// Returns Acad::eInvalidInput if the operation fails.
    /// </returns>
    ACDBCORE2D_PORT Acad::ErrorStatus        setLocation(const AcDbTextEditorLocation& location);
    ///<summary> 
    /// Get the AcDbTextEditorLocation associated with the current TextEditor
    /// location.
    ///</summary>
    /// <returns>
    /// Returns AcDbTextEditorLocation for the current location.
    /// </returns>
    ACDBCORE2D_PORT AcDbTextEditorLocation* location() const;

protected:
    ACDBCORE2D_PORT AcDbTextEditorCursor(const TextEditor* pImp);
    ACDBCORE2D_PORT ~AcDbTextEditorCursor();
    AcDbTextEditorCursor(const AcDbTextEditorCursor&);
    AcDbTextEditorCursor& operator=(const AcDbTextEditorCursor&);

    AcDbImpTextEditorCursor* m_pImpCursor;
    friend class TextEditor;
};

///<summary> 
/// The AcDbTextEditorParagraphTab represents the tab object in the editor. You can
/// get/set the paragraph tab object properties. From its constructor it will create
/// a tab object which has default properties.
///</summary>
class AcDbTextEditorParagraphTab
{
public:
    /// <summary>
    /// This enumerator describes the paragraph tab types.
    /// </summary>
    enum ParagraphTabType
    {
        /// <summary>
        /// The text align the paragraph tab to the left.
        /// </summary>
        kLeftTab,
        /// <summary>
        /// The text align the paragraph tab to the center.
        /// </summary>
        kCenterTab,
        /// <summary>
        /// The text align the paragraph tab to the right.
        /// </summary>
        kRightTab,
        /// <summary>
        /// The text align the paragraph tab to the decimal separator.
        /// </summary>
        kDecimalTab,
    };

    ///<summary> 
    /// Constructor. It will create a left tab with 0 offset distance.
    ///</summary>
    ACDBCORE2D_PORT  AcDbTextEditorParagraphTab();
    ///<summary> 
    /// Destructor.
    ///</summary>
    ACDBCORE2D_PORT ~AcDbTextEditorParagraphTab();
    ///<summary> 
    /// Copy Constructor.
    ///</summary>
    ACDBCORE2D_PORT AcDbTextEditorParagraphTab(const AcDbTextEditorParagraphTab&);
    ///<summary> 
    /// Operator =.
    ///</summary>
    ACDBCORE2D_PORT AcDbTextEditorParagraphTab& operator=(const AcDbTextEditorParagraphTab&);
    ///<summary> 
    /// Get the offset distance for paragraph tab.
    ///</summary>
    /// <returns>
    /// Returns offset of paragraph tab.
    /// </returns>
    ACDBCORE2D_PORT double            offset() const;
    ///<summary> 
    /// Set the offset distance for paragraph tab.
    ///</summary>
    /// <param name="off">Offset value. The value must be between 0 and 2000. </param>
    /// <returns>
    /// Returns Acad::eOk if the operation succeeds.
    /// Returns Acad::eInvalidInput if the operation fails.
    /// </returns>
    ACDBCORE2D_PORT Acad::ErrorStatus setOffset(double offdist);

    ///<summary> 
    /// Get the type of paragraph tab. For a paragraph tab its default value of 
    /// tab type is kLeftTab.
    ///</summary>
    /// <returns>
    /// Returns type of paragraph tab.
    /// </returns>
    ACDBCORE2D_PORT ParagraphTabType  type() const;
    ///<summary> 
    /// Set type of paragraph tab.
    ///</summary>
    /// <param name="type">Type value.</param>
    /// <returns>
    /// Returns Acad::eOk if the operation succeeds.
    /// Returns Acad::eInvalidInput if the operation fails.
    /// </returns>
    ACDBCORE2D_PORT Acad::ErrorStatus setType(ParagraphTabType type);

    ///<summary> 
    /// Get decimal character of paragraph tab.
    ///</summary>
    /// <returns>
    /// Returns decimal character paragraph tab.
    /// </returns>
    ACDBCORE2D_PORT wchar_t             decimalChar() const;
    ///<summary> 
    /// Set decimal character of paragraph tab.
    ///</summary>
    /// <param name="decchar">Decimal character.</param>
    /// <returns>
    /// Returns Acad::eOk if the operation succeeds.
    /// Returns Acad::eInvalidInput if the operation fails.
    /// </returns>
    ACDBCORE2D_PORT Acad::ErrorStatus setDecimalChar(wchar_t decchar);

private:
    AcDbImpTextEditorParagraphTab* m_pImp;
};

///<summary> 
/// The AcDbTextEditorParagraph represents the paragraph object in the editor.
/// If you don't need it, please call its release() function. Otherwise it will result
/// in a memory leak.
/// If the current text editor defined width(AcDbTextEditor::definedWidth()) is zero or
/// the current text editor text style is vertical SHX, it can't support the properties
/// in paragraph like indent, space, alignment, tabs and so on. Call those functions will
/// return Acad::eNotApplicable.
///</summary>
class AcDbTextEditorParagraph : public AcDbTextEditorSelectable
{
public:
    /// <summary>
    /// Text editor paragraph alignment type.
    /// </summary>
    enum AlignmentType
    {
        /// <summary>
        /// Default paragraph alignment.
        /// </summary>
        kAlignmentDefault,
        /// <summary>
        /// Paragraph is left alignment.
        /// </summary>
        kAlignmentLeft,
        /// <summary>
        /// Paragraph is center alignment.
        /// </summary>
        kAlignmentCenter,
        /// <summary>
        /// Paragraph is right alignment.
        /// </summary>
        kAlignmentRight,
        /// <summary>
        /// Paragraph is justify alignment.
        /// </summary>
        kAlignmentJustify,
        /// <summary>
        /// Paragraph is distribute alignment.
        /// </summary>
        kAlignmentDistribute
    };

    /// <summary>
    /// Text editor paragraph line spacing type.
    /// </summary>
    enum LineSpacingStyle{
        /// <summary>
        /// Default line spacing.
        /// </summary>
        kLineSpacingDefault,
        /// <summary>
        /// Line spacing is fixed and is never adjusted .
        /// </summary>
        kLineSpacingExactly,
        /// <summary>
        /// Line spacing is a minimum that may be adjusted to accommodate larger
        /// font sizes or graphics that would not otherwise fit within the specified spacing.
        /// </summary>
        kLineSpacingAtLeast,
        /// <summary>
        /// Multiple line spacing.
        /// </summary>
        kLineSpacingMultiple,
    };

    /// <summary>
    /// Text editor paragraph numbering type.
    /// </summary>
    enum NumberingType{
        /// <summary>
        /// Numbering off.
        /// </summary>
        kOff = 0,
        /// <summary>
        /// Bullet numbering.
        /// </summary>
        kBullet,
        /// <summary>
        /// Number numbering.
        /// </summary>
        kNumber,
        /// <summary>
        /// Letter lower numbering.
        /// </summary>
        kLetterLower,
        /// <summary>
        /// Letter upper numbering.
        /// </summary>
        kLetterUpper,
        /// <summary>
        /// Number wide numbering.
        /// </summary>
        kNumberWide,
        /// <summary>
        /// Letter lower numbering.
        /// </summary>
        kLetterLowerWide,
        /// <summary>
        /// Letter upper numbering.
        /// </summary>
        kLetterUpperWide,
    };

    ///<summary> 
    /// Set alignment for paragraph.  AlignmentType defines the paragraph 
    /// alignment.
    ///</summary>
    /// <param name="AlignmentType">Alignment type value you wan to set.</param>
    /// <returns>
    /// Returns Acad::eOk if the operation succeeds.
    /// Returns Acad::eInvalidInput if the operation fails.
    /// </returns>
    ACDBCORE2D_PORT Acad::ErrorStatus setAlignment(AlignmentType AlignmentType);

    ///<summary> 
    /// First indent for paragraph.
    ///</summary>
    /// <returns>
    /// Returns the AlignmentType for the paragraph.
    /// </returns>
    ACDBCORE2D_PORT AlignmentType alignment() const;

    ///<summary> 
    /// Set first indent for paragraph.
    ///</summary>
    /// <param name="firstIndent">First indent value you wan to set. The value 
    /// must be between 0 and 10000 * AcDbTextEditor::textHeight().</param>
    /// <returns>
    /// Returns Acad::eOk if the operation succeeds.
    /// Returns Acad::eInvalidInput if the operation fails.
    /// </returns>
    ACDBCORE2D_PORT Acad::ErrorStatus setFirstIndent(double firstIndent);

    ///<summary> 
    /// First indent for paragraph.
    ///</summary>
    /// <returns>
    /// Returns first indent.
    /// </returns>
    ACDBCORE2D_PORT double firstIndent() const;

    ///<summary> 
    /// Set left indent for paragraph. This is also referred to as a hanging indent.
    ///</summary>
    /// <param name="leftIndent">Left indent value. The value must be between 0
    /// and 10000 * AcDbTextEditor::textHeight().</param>
    /// <returns>
    /// Returns Acad::eOk if the operation succeeds.
    /// Returns Acad::eInvalidInput if the operation fails.
    /// </returns>
    ACDBCORE2D_PORT Acad::ErrorStatus setLeftIndent(double leftIndent);

    ///<summary> 
    /// Left indent for paragraph. This is also referred to as a hanging indent.
    ///</summary>
    /// <returns>
    /// Returns first indent.
    /// </returns>
    ACDBCORE2D_PORT double leftIndent() const;

    ///<summary> 
    /// Set right indent for paragraph.
    ///</summary>
    /// <param name="rightIndent">Right indent value. The value must be between 
    /// 0 and 10000 * AcDbTextEditor::textHeight().</param>
    /// <returns>
    /// Returns Acad::eOk if the operation succeeds.
    /// Returns Acad::eInvalidInput if the operation fails.
    /// </returns>
    ACDBCORE2D_PORT Acad::ErrorStatus setRightIndent(double rightIndent);

    ///<summary> 
    /// Right indent for paragraph.
    ///</summary>
    /// <returns>
    /// Returns right indent.
    /// </returns>
    ACDBCORE2D_PORT double rightIndent() const;

    ///<summary> 
    /// Set line spacing style for paragraph.
    ///</summary>
    /// <param name="lineSpacingStyle">LineSpacingStyle value.</param>
    /// <returns>
    /// Returns Acad::eOk if the operation succeeds.
    /// Returns Acad::eInvalidInput if the operation fails.
    /// </returns>
    ACDBCORE2D_PORT Acad::ErrorStatus setLineSpacingStyle(LineSpacingStyle lineSpacingStyle);
    ///<summary> 
    /// Line spacing style for paragraph.
    ///</summary>
    /// <returns>
    /// Returns LineSpacingStyle for paragraph.
    /// </returns>
    ACDBCORE2D_PORT LineSpacingStyle  lineSpacingStyle() const;

    ///<summary> 
    /// Set line spacing factor for paragraph. If the line space style is kLineSpacingDefault
    /// the function will return Acad::eInvalidInput for you.
    ///</summary>
    /// <param name="lineSpacingFactor">Factor value. When the line spacing style is
    /// kLineSpacingMultiple, the value must be between AcDbTextEditorParagraph::minLineSpacingFactor()
    /// and AcDbTextEditorParagraph::maxLineSpacingFactor(). For the other line spacing type
    /// the value must be between AcDbTextEditorParagraph::minLineSpacingFactor() * AcDbTextEditor::textHeight()
    /// and AcDbTextEditorParagraph::maxLineSpacingFactor() * AcDbTextEditor::textHeight().</param>
    /// <returns>
    /// Returns Acad::eOk if the operation succeeds.
    /// Returns Acad::eInvalidInput if the operation fails.
    /// </returns>
    ACDBCORE2D_PORT Acad::ErrorStatus setLineSpacingFactor(double lineSpacingFactor);
    ///<summary> 
    /// Line spacing factor for paragraph.
    ///</summary>
    /// <returns>
    /// Returns line spacing factor for paragraph.
    /// </returns>
    ACDBCORE2D_PORT double            lineSpacingFactor() const;

    ///<summary> 
    /// Set "space before" for paragraph. 
    ///</summary>
    /// <param name="spaceBefore">"space before" value. The value must be between 
    /// AcDbTextEditorParagraph::minLineSpacingFactor() and AcDbTextEditorParagraph::maxLineSpacingFactor().</param>
    /// <returns>
    /// Returns Acad::eOk if the operation succeeds.
    /// Returns Acad::eInvalidInput if the operation fails.
    /// </returns>
    ACDBCORE2D_PORT Acad::ErrorStatus setSpaceBefore(double spaceBefore);
    ///<summary> 
    /// Line "space before" for paragraph.
    ///</summary>
    /// <returns>
    /// Returns "space before" for paragraph.
    /// </returns>
    ACDBCORE2D_PORT double            spaceBefore() const;

    ///<summary> 
    /// Set "space after" for paragraph.
    ///</summary>
    /// <param name="spaceAfter">"space after" value. The value must be between 
    /// AcDbTextEditorParagraph::minLineSpacingFactor() and AcDbTextEditorParagraph::maxLineSpacingFactor().</param>
    /// <returns>
    /// Returns Acad::eOk if the operation succeeds.
    /// Returns Acad::eInvalidInput if the operation fails.
    /// </returns>
    ACDBCORE2D_PORT Acad::ErrorStatus setSpaceAfter(double spaceAfter);
    ///<summary> 
    /// Line "space after" for paragraph.
    ///</summary>
    /// <returns>
    /// Returns "space after" for paragraph.
    /// </returns>
    ACDBCORE2D_PORT double            spaceAfter() const;

    ///<summary> 
    /// Set Numbering type for paragraph. You can only call the function when
    /// the numbering is enabled, otherwise it will return Acad::eInvalidInput.
    ///</summary>
    /// <param name="type">NumberingType value.</param>
    /// <returns>
    /// Returns Acad::eOk if the operation succeeds.
    /// Returns Acad::eInvalidInput if the operation fails.
    /// </returns>
    ACDBCORE2D_PORT Acad::ErrorStatus setNumberingType(NumberingType type);
    ///<summary> 
    /// Get the numbering type for paragraph. If the numbering is not enabled, it
    /// will return AcDbTextEditorParagraph::kOff for you.
    ///</summary>
    /// <returns>
    /// Returns NumberingType numbering type for paragraph.
    /// </returns>
    ACDBCORE2D_PORT NumberingType     numberingType() const;

    ///<summary> 
    /// Starts a new letter or number sequence for the paragraph. You can only 
    /// call the function when the numbering is enabled, otherwise it will return
    /// Acad::eInvalidInput. If the paragraph has no numbering, it has no effect
    /// after calling the function.
    /// If the next paragraphs' type is the same as this one, it will also restart
    /// next pragraphs' numbering.
    ///</summary>
    /// <returns>
    /// Returns Acad::eOk if the operation succeeds.
    /// Returns Acad::eInvalidInput if the operation fails.
    /// </returns>
    ACDBCORE2D_PORT Acad::ErrorStatus restartNumbering();
    ///<summary> 
    /// Adds the paragraph to the last list above and continues the sequence. You 
    /// can only call the function when the numbering is enabled, otherwise it
    /// will return Acad::eInvalidInput. If the paragraph has no numbering, it has
    /// no effect after calling the function.
    /// If the next paragraphs' type is the same as this one, it will also continue
    /// next pragraphs' numbering.
    ///</summary>
    /// <returns>
    /// Returns Acad::eOk if the operation succeeds.
    /// Returns Acad::eInvalidInput if the operation fails.
    /// </returns>
    ACDBCORE2D_PORT Acad::ErrorStatus continueNumbering();

    ///<summary> 
    /// Get the count of paragraph tabs for current paragraph.
    ///</summary>
    /// <returns>
    /// Returns count of tabs.
    /// </returns>
    ACDBCORE2D_PORT int               tabsCount() const;

    ///<summary> 
    /// Add a tab. Note that for the specified offset distance the text editor paragraph
    /// can be added one paragraph tab. If the current offset distance has already one
    /// tab, the function will return Acad::eInvalidInput for you.
    ///</summary>
    /// <param name="tab">AcDbTextEditorParagraphTab to add.</param>
    /// <returns>
    /// Returns Acad::eOk if the operation succeeds.
    /// Returns Acad::eInvalidInput if the operation fails.
    /// </returns>
    ACDBCORE2D_PORT Acad::ErrorStatus addTab(const AcDbTextEditorParagraphTab& tab);

    ///<summary> 
    /// Remove the specified tab from tabs container.
    ///</summary>
    /// <param name="tab">AcDbTextEditorParagraphTab to remove.</param>
    /// <returns>
    /// Returns Acad::eOk if the operation succeeds.
    /// Returns Acad::eInvalidInput if the operation fails.
    /// </returns>
    ACDBCORE2D_PORT Acad::ErrorStatus removeTab(const AcDbTextEditorParagraphTab& tab);

    ///<summary> 
    /// Get a AcDbTextEditorParagraphTab object from current paragraph.
    ///</summary>
    /// <param name="i">Index of AcDbTextEditorParagraphTab object to get. It must be 0 and
    /// AcDbTextEditorParagraph::count().</param>
    /// <param name="tab">AcDbTextEditorParagraphTab object for returned tab.</param>
    /// <returns>
    /// Returns Acad::eOk if the operation succeeds and the parameter tab contains
    /// the returned AcDbTextEditorParagraphTab object.
    /// Returns Acad::eInvalidInput if the operation fails.
    /// </returns>
    ACDBCORE2D_PORT Acad::ErrorStatus getTab(int i, AcDbTextEditorParagraphTab& tab);

    ///<summary> 
    /// Gets the location of the start of a selection.
    ///</summary>
    /// <returns>
    /// Returns an AcDbTextEditorLocation object for the start of a selection.
    /// </returns>
    ACDBCORE2D_PORT virtual AcDbTextEditorLocation* startOfText() ADESK_OVERRIDE;
    ///<summary> 
    /// Gets the location of the end of a selection.
    ///</summary>
    /// <returns>
    /// Returns an AcDbTextEditorLocation object for the end of a selection.
    /// </returns>
    ACDBCORE2D_PORT virtual AcDbTextEditorLocation* endOfText() ADESK_OVERRIDE;

    ///<summary> 
    /// Minimum allowable  line spacing factor.
    ///</summary>
    /// <returns>
    /// Returns minimum allowable  line spacing factor.
    /// </returns>
    ACDBCORE2D_PORT double     minLineSpacingFactor() const;
    ///<summary> 
    /// Maximum allowable line spacing factor.  
    ///</summary>
    /// <returns>
    /// Returns Maximum allowable  line spacing factor.
    /// </returns>
    ACDBCORE2D_PORT double     maxLineSpacingFactor() const;

    ///<summary> 
    /// Minimum allowable after/before space value.
    ///</summary>
    /// <returns>
    /// Returns minimum allowable after/before space value.
    /// </returns>
    ACDBCORE2D_PORT double     minSpaceValue() const;
    ///<summary> 
    /// Maximum allowable after/before space value.
    ///</summary>
    /// <returns>
    /// Returns maximum allowable after/before space value.
    /// </returns>
    ACDBCORE2D_PORT double     maxSpaceValue() const;

    ///<summary> 
    /// Delete this AcDbTextEditorParagraph.
    ///</summary>
    ACDBCORE2D_PORT void             release();

private:
    friend class AcDbTextEditorParagraphIterator;
    friend class AcDbTextEditorServices;
    AcDbImpTextEditorParagraph* m_pImp; //struct with TextEditor and an index

    AcDbTextEditorParagraph() {}
    virtual ~AcDbTextEditorParagraph();
    AcDbTextEditorParagraph(const AcDbTextEditorParagraph&);
    AcDbTextEditorParagraph& operator=(const AcDbTextEditorParagraph&);
};

///<summary> 
/// This is the paragraph iterator in text editor. 
///</summary>
class AcDbTextEditorParagraphIterator
{
public:
    ///<summary> 
    /// Constructor.
    ///</summary>
    ACDBCORE2D_PORT AcDbTextEditorParagraphIterator(const AcDbTextEditor& textEditor);
    ///<summary> 
    /// Destructor.
    ///</summary>
    ACDBCORE2D_PORT ~AcDbTextEditorParagraphIterator();

    ///<summary> 
    /// End of AcDbTextEditorParagraphIterator Iterator.
    ///</summary>
    /// <returns>
    /// Returns true if end of iterator.
    /// </returns>
    ACDBCORE2D_PORT bool done();

    ///<summary> 
    /// Get current AcDbTextEditorParagraphIterator Iterator.
    ///</summary>
    /// <returns>
    /// Returns AcDbTextEditorParagraph* of current iterator.
    /// </returns>
    ACDBCORE2D_PORT AcDbTextEditorParagraph* current();

    ///<summary> 
    /// Increments AcDbTextEditorParagraphIterator Iterator.
    ///</summary>
    ACDBCORE2D_PORT void next();
private:
    AcDbImpTextEditorParagraphIterator* m_pImp;
};

///<summary> 
/// The AcDbTextEditorColumn repersents the column object in text editor. All the 
/// columns in editor can have different height value but they have the same width.
/// If you don't need it, please call its release() function. Otherwise it will has
/// some memory leak.
///</summary>
class AcDbTextEditorColumn : public AcDbTextEditorSelectable
{
public:
    ///<summary> 
    /// Column height.
    ///</summary>
    /// <returns>
    /// Returns column height.
    /// </returns>
    ACDBCORE2D_PORT double height();
    ///<summary> 
    /// Set the column height. Note that you can only set the column height when
    /// the column type is kDynamicColumns and the column is not auto height column.
    ///</summary>
    /// <param name="height">Column height you wan to set. The value must be between 
    /// AcDbTextEditor::textHeight() and AcDbTextEditor::textHeight() * 1000.</param>
    /// <returns>
    /// Returns Acad::eOk if the operation succeeds.
    /// Returns Acad::eInvalidInput if the operation fails.
    /// Returns Acad::eNotApplicable if current column type is not kDynamicColumns
    /// or the column is auto height column.
    /// </returns>
    ACDBCORE2D_PORT Acad::ErrorStatus setHeight(double height);

    ///<summary> 
    /// Delete this AcDbTextEditorColumn.
    ///</summary>
    ACDBCORE2D_PORT void              release();

    ///<summary> 
    /// Gets the start location for the column.
    ///</summary>
    /// <returns>
    /// Returns an AcDbTextEditorLocation object for the start of a column.
    /// </returns>
    ACDBCORE2D_PORT virtual AcDbTextEditorLocation* startOfText() ADESK_OVERRIDE;
    ///<summary> 
    /// Gets the end location for the column.
    ///</summary>
    /// <returns>
    /// Returns an AcDbTextEditorLocation object for the end of a column.
    /// </returns>
    ACDBCORE2D_PORT virtual AcDbTextEditorLocation* endOfText() ADESK_OVERRIDE;
private:
    AcDbImpTextEditorColumn* m_pImp;
    friend class AcDbTextEditorServices;

    AcDbTextEditorColumn();
    virtual ~AcDbTextEditorColumn();
    AcDbTextEditorColumn(const AcDbTextEditorColumn&);
    AcDbTextEditorColumn& operator=(const AcDbTextEditorColumn&);
};

///<summary> 
/// This class keeps the common properties for all the column objects in text editor.
/// User can get the object from the AcDbTextEditor::columns() function. Don't try to
/// release the object. Its life cycle is managed by the core.
///</summary>
class AcDbTextEditorColumns
{
public:
    ///<summary> 
    /// Maximum number of columns supported by the TextEditor.
    ///</summary>
    /// <returns>
    /// Returns maximum number of columns supported by the TextEditor.
    /// </returns>
    ACDBCORE2D_PORT static int maxCount();

    ///<summary> 
    /// Number of columns.
    ///</summary>
    /// <returns>
    /// Returns number of columns.
    /// </returns>
    ACDBCORE2D_PORT int count() const;

    ///<summary> 
    /// Set number of columns. This can't be set if current column type is kNoColumns
    /// or kDynamicColumns.
    ///</summary>
    /// <param name="count">Number of columns to set. The value must be between 1 
    /// and AcDbTextEditorColumns::maxCount(). </param>
    /// <returns>
    /// Returns Acad::eOk if the operation succeeds.
    /// Returns Acad::eInvalidInput if the operation fails.
    /// Returns Acad::eNotApplicable if current column type is kNoColumns or kDynamicColumns.
    /// </returns>
    ACDBCORE2D_PORT Acad::ErrorStatus setCount(int count);

    ///<summary> 
    /// Get AcDbTextEditorColumn pointer for a column. If the current column type is
    /// kNoColumns it will return NULL.
    ///</summary>
    /// <param name="i">Column to get. The input value must be between 0 and
    /// AcDbTextEditorColumns::count(). </param>
    /// <returns>
    /// Returns AcDbTextEditorColumn* for requested column.
    /// </returns>
    ACDBCORE2D_PORT AcDbTextEditorColumn* getAt(int i);
    
    ///<summary> 
    /// Set column type(one of the following): AcDbMText::kNoColumns, 
    /// AcDbMText::kStaticColumns or AcDbMText::kDynamicColumns. 
    ///</summary>
    /// <param name="type">Column type.</param>
    /// <returns>
    /// Returns Acad::eOk if the operation succeeds.
    /// Returns Acad::eInvalidInput if the operation fails.
    /// Returns Acad::eNotApplicable if current column type is kNoColumns.
    /// </returns>
    ACDBCORE2D_PORT Acad::ErrorStatus setColumnType(AcDbMText::ColumnType type);

    ///<summary> 
    /// Column type. Columns can be Static or Dynamic.
    /// Dynamic columns can have automatic height or manual height.
    ///</summary>
    /// <returns>
    /// Returns ColumnType.
    /// </returns>
    ACDBCORE2D_PORT AcDbMText::ColumnType columnType() const;

    ///<summary> 
    /// Sets the flag whether heights for each dynamic column is equal to the MText height
    /// (auto-height), or user-controlled for each dynamic column (manual-height). 
    /// This is only valid for dynamic columns.
    ///</summary>
    /// <param name="bAutoHeight">Flag to set/unset the auto height flag for columns.</param>
    /// <returns>
    /// Returns Acad::eOk if the operation succeeds.
    /// Returns Acad::eInvalidInput if the operation fails.
    /// Returns Acad::eNotApplicable if the current columns type is not AcDbMText::kDynamicColumns.
    /// </returns>
    ACDBCORE2D_PORT Acad::ErrorStatus setAutoHeight(bool bAutoHeight);

    ///<summary> 
    /// Gets the auto height setting, which specifies whether dynamic columns use 
    /// the MText height or a per-column user-defined height. Only valid for dynamic
    /// columns.
    ///</summary>
    /// <returns>
    /// Returns column auto height setting.
    /// </returns>
    ACDBCORE2D_PORT bool autoHeight() const;

    ///<summary> 
    /// Set the column width. All columns have the same width. This can't be set 
    /// if current column type is kNoColumns.
    ///</summary>
    /// <param name="value">Column width. The value must be between AcDbTextEditor::textHeight()
    /// and AcDbTextEditor::textHeight() * 1000. </param>
    /// <returns>
    /// Returns Acad::eOk if the operation succeeds.
    /// Returns Acad::eInvalidInput if the operation fails.
    /// Returns Acad::eNotApplicable if current column type is kNoColumns.
    /// </returns>
    ACDBCORE2D_PORT Acad::ErrorStatus setWidth(double value);

    ///<summary> 
    /// Column width. All columns have the same width.
    ///</summary>
    /// <returns>
    /// Returns column width.
    /// </returns>
    ACDBCORE2D_PORT double width() const;

    ///<summary> 
    /// Set the column gutter width. All columns have the same gutter width.
    /// This can't be set if current column type is kNoColumns.
    ///</summary>
    /// <param name="value">Gutter width value. The value must be between 
    /// 0 and AcDbTextEditor::textHeight() * 1000.</param>
    /// <returns>
    /// Returns Acad::eOk if the operation succeeds.
    /// Returns Acad::eInvalidInput if the operation fails.
    /// Returns Acad::eNotApplicable if current column type is kNoColumns.
    /// </returns>
    ACDBCORE2D_PORT Acad::ErrorStatus setGutter(double value);

    ///<summary> 
    /// Column gutter width. All columns have the same gutter width.
    ///</summary>
    /// <returns>
    /// Returns column width.
    /// </returns>
    ACDBCORE2D_PORT double gutter() const;

    ///<summary> 
    ///Set the total width of the columns. The actual width of the columns and 
    ///the gutter width is adjusted to fit within this total. This can't be set 
    ///if current column type is kNoColumns.
    ///</summary>
    /// <param name="value">Total width value. The value must be between 
    /// AcDbTextEditor::textHeight() and AcDbTextEditor::textHeight() * 1000.</param>
    /// <returns>
    ///Returns Acad::eOk if the operation succeeds.
    ///Returns Acad::eInvalidInput if the operation fails.
    ///Returns Acad::eNotApplicable if current column type is kNoColumns.
    /// </returns>
    ACDBCORE2D_PORT Acad::ErrorStatus setTotalWidth(double value);

    ///<summary> 
    ///Get the total width for all the static columns.
    ///</summary>
    /// <returns>
    ///Returns total width of the static columns.  The gutter width is included
    ///in the total.
    /// </returns>
    ACDBCORE2D_PORT double totalWidth() const;

    ///<summary> 
    ///Gets the flow reversed setting, which determines how columns are added. 
    ///Normally columns flow from left (the first) to right (the last).
    ///</summary>
    /// <returns>
    ///Returns true if the flow of the column is reversed.
    /// </returns>
    ACDBCORE2D_PORT bool   isFlowReversed() const;

    ///<summary> 
    ///Set the flow reverse flag of the columns. This can't be set if current 
    ///column type is kNoColumns.
    ///</summary>
    /// <param name="isFlowReversed">Flag to set/unset the flow reversed.</param>
    /// <returns>
    ///Returns Acad::eOk if the operation succeeds.
    ///Returns Acad::eInvalidInput if the operation fails.
    ///Returns Acad::eNotApplicable if current column type is kNoColumns.
    /// </returns>
    ACDBCORE2D_PORT Acad::ErrorStatus setIsFlowReversed(bool isFlowReversed);

private:
    friend class TextEditor;
    AcDbTextEditorColumns();
    ~AcDbTextEditorColumns();
    AcDbTextEditorColumns(const AcDbTextEditorColumns&);
    AcDbTextEditorColumns& operator=(const AcDbTextEditorColumns&);

    TextEditor* m_pImp;
};

///<summary> 
/// The AcDbTextEditorWipeout class represents the wipe out object in editor.
/// User can get the object from the AcDbTextEditor::wipeout() function. Don't 
/// try to release the object. Its life cycle is managed by the core.
///</summary>
class AcDbTextEditorWipeout
{
public:
    ///<summary> 
    /// Minimum allowable value of background scale factor.
    ///</summary>
    ///<returns>
    /// Minimum allowable value.
    ///</returns>
    ACDBCORE2D_PORT static double     minBackgroundScaleFactor();
    ///<summary> 
    ///Maximum allowable value of background scale factor.
    ///</summary>
    ///<returns>
    ///Maximum allowable value.
    ///</returns>
    ACDBCORE2D_PORT static double     maxBackgroundScaleFactor();

    ///<summary> 
    /// Get Enable background fill (wipeout) state.
    ///</summary>
    ///<returns>
    /// Return true if background fill is enabled.
    ///</returns>
    ACDBCORE2D_PORT bool              enableBackgroundFill() const;
    ///<summary> 
    /// Enable background fill (wipeout).
    ///</summary>
    /// <param name="bEnable">Set true to enable background fill (wipeout).</param>
    ///<returns>
    ///Returns Acad::eOk if the operation succeeds.
    ///Returns Acad::eInvalidInput if the operation fails.
    ///</returns>
    ACDBCORE2D_PORT Acad::ErrorStatus setEnableBackgroundFill(bool bEnable);

    ///<summary> 
    /// Get the current background fill color.
    ///</summary>
    ///<returns>
    /// Returns background fill color.
    ///</returns>
    ACDBCORE2D_PORT AcCmColor         getBackgroundFillColor() const;
    ///<summary> 
    /// Set background fill (wipeout) color.
    ///</summary>
    /// <param name="color">AcCmColor color to set.</param>
    /// <returns>
    /// Returns Acad::eOk if the operation succeeds.
    /// Returns Acad::eInvalidInput if the operation fails.
    ///</returns>
    ACDBCORE2D_PORT Acad::ErrorStatus setBackgroundFillColor(AcCmColor color);

    ///<summary> 
    /// Returns true if background color is in use. Otherwise, returns false. 
    ///</summary>
    ///<returns>
    ///Return true if use background color is in use.
    ///</returns>
    ACDBCORE2D_PORT bool              useBackgroundColor() const;
    ///<summary> 
    /// Enable background fill (wipeout).
    ///</summary>
    /// <param name="bUse">If bUse is true, this function sets background color 
    /// to be used for this object. Otherwise, it turns off the background.
    /// color.
    /// </param>
    ///<returns>
    ///Returns Acad::eOk if the operation succeeds.
    ///Returns Acad::eInvalidInput if the operation fails.
    ///</returns>
    ACDBCORE2D_PORT Acad::ErrorStatus setUseBackgroundColor(bool bUse);

    ///<summary> 
    /// Get the current background scale factor.
    ///</summary>
    ///<returns>
    ///Returns Background scale factor.
    ///</returns>
    ACDBCORE2D_PORT double            getBackgroundScaleFactor()const;
    ///<summary> 
    ///Set background scale factor.
    ///</summary>
    /// <param name="factor">Scale factor. The value must be between 
    /// AcDbTextEditorWipeout::minBackgroundScaleFactor() and 
    /// AcDbTextEditorWipeout::minBackgroundScaleFactor().</param>
    ///<returns>
    ///Returns Acad::eOk if the operation succeeds.
    ///Returns Acad::eInvalidInput if the operation fails.
    ///</returns>
    ACDBCORE2D_PORT Acad::ErrorStatus setBackgroundScaleFactor(double factor);

private:
    AcDbTextEditorWipeout();
    ~AcDbTextEditorWipeout();
    AcDbTextEditorWipeout(const AcDbTextEditorWipeout&);
    AcDbTextEditorWipeout& operator=(const AcDbTextEditorWipeout&);

    TextEditor* m_pEditor;
    friend class TextEditor;
};

///<summary> 
/// The AcDbTextEditorStack represents the stack object properties in text editor. 
/// The stack object is to manage the text like fraction. From the class you can
/// get/set the properties for the selected stack, like change the top text, the 
/// bottom text or the stack type.
///</summary>
class AcDbTextEditorStack
{
public:
    /// <summary>
    /// This enumerator describe the stack type.
    /// </summary>
    enum StackType
    {
        /// <summary>
        /// Stacks the selected text with the first number on top of the second 
        /// number separated by a horizontal line. 
        /// </summary>
        kHorizontalStack,
        /// <summary>
        /// Stacks the selected text with the first number on top of the second 
        /// number separated by a diagonal line. 
        /// </summary>
        kDiagonalStack,
        /// <summary>
        /// Stacks the selected text with the first number on top of the second
        /// number. There is no line between the numbers. 
        /// </summary>
        kToleranceStack,
        /// <summary>
        /// A variation of the Tolerance style that aligns the decimal point of
        /// both the upper and lower numbers of selected text.
        /// </summary>
        kDecimalStack,
    };

    ///<summary> 
    /// Constructor. It will create a horizontal stack with 1.0 scale factor.
    ///</summary>
    ACDBCORE2D_PORT AcDbTextEditorStack();
    ///<summary> 
    /// Destructor.
    ///</summary>
    ACDBCORE2D_PORT ~AcDbTextEditorStack();
    ///<summary> 
    /// Copy constructor.
    ///</summary>
    ACDBCORE2D_PORT AcDbTextEditorStack(const AcDbTextEditorStack&);
    ///<summary> 
    /// Operator =.
    ///</summary>
    ACDBCORE2D_PORT AcDbTextEditorStack& operator=(const AcDbTextEditorStack&);

    ///<summary> 
    /// Get StackType.
    ///</summary>
    /// <returns>
    /// Returns StackType.
    /// </returns>
    ACDBCORE2D_PORT StackType        type() const;
    ///<summary> 
    /// Set StackType.
    ///</summary>
    /// <param name="type">StackType to set.</param>
    /// <returns>
    /// Returns Acad::eOk if the operation succeeded.
    /// Returns Acad::eInvalidInput if the operation fails.
    /// </returns>
    ACDBCORE2D_PORT Acad::ErrorStatus setType(StackType type);

    ///<summary> 
    /// Get the fraction's alignment type. The default alignment is kFlowCenter.
    /// kFlowTop: Aligns the top of the fraction with the top of the text line. 
    /// kFlowCenter: Centers the fraction vertically at the center of the text line. 
    /// kFlowBase: Aligns the bottom of the fraction with the text baseline. 
    ///</summary>
    /// <returns>
    /// Returns stack flow alignment.
    /// </returns>
    ACDBCORE2D_PORT AcDbTextEditorSelectionBase::FlowAlign alignType() const;
    ///<summary> 
    /// Set the fraction's alignment type.
    ///</summary>
    /// <param name="align">alignment type to set.</param>
    /// <returns>
    /// Returns Acad::eOk if the operation succeeded.
    /// Returns Acad::eInvalidInput if the operation fails.
    /// </returns>
    ACDBCORE2D_PORT Acad::ErrorStatus setAlignType(AcDbTextEditorSelectionBase::FlowAlign align);

    ///<summary> 
    /// Get top of stack string.
    ///</summary>
    /// <returns>
    /// Returns top of stack string.
    /// </returns>
    ACDBCORE2D_PORT AcString top() const;
    ///<summary> 
    /// Set top of stack string.
    ///</summary>
    /// <param name="top">Top of stack string.</param>
    /// <returns>
    /// Returns Acad::eOk if the operation succeeded.
    /// Returns Acad::eInvalidInput if the operation fails.
    /// </returns>
    ACDBCORE2D_PORT Acad::ErrorStatus setTop(const AcString& top);

    ///<summary> 
    /// Get bottom of stack string.
    ///</summary>
    /// <returns>
    /// Returns bottom of stack string.
    /// </returns>
    ACDBCORE2D_PORT AcString           bottom() const;
    ///<summary> 
    /// Set bottom of stack string.
    ///</summary>
    /// <param name="bottom">Bottom of stack string.</param>
    /// <returns>
    /// Returns Acad::eOk if the operation succeeded.
    /// Returns Acad::eInvalidInput if the operation fails.
    /// </returns>
    ACDBCORE2D_PORT Acad::ErrorStatus setBottom(const AcString& bottom);

    ///<summary> 
    /// Get stack scale.
    ///</summary>
    /// <returns>
    /// Returns stack scale.
    /// </returns>
    ACDBCORE2D_PORT double            scale() const;
    ///<summary> 
    /// Set stack scale.
    ///</summary>
    /// <param name="scale">Stack scale. This value must be AcDbTextEditorStack::minStackScale()
    /// and AcDbTextEditorStack::maxStackScale().</param>
    /// <returns>
    /// Returns Acad::eOk if the operation succeeded.
    /// Returns Acad::eInvalidInput if the operation fails.
    /// </returns>
    ACDBCORE2D_PORT Acad::ErrorStatus setScale(double scale);

    ///<summary> 
    /// Get stack decimal character.
    ///</summary>
    /// <returns>
    /// Returns stack decimal character.
    /// </returns>
    ACDBCORE2D_PORT wchar_t             decimalChar() const;
    ///<summary> 
    /// Set stack decimal character.
    ///</summary>
    /// <param name="decimalChar">Stack decimal character.</param>
    /// <returns>
    /// Returns Acad::eOk if the operation succeeded.
    /// Returns Acad::eInvalidInput if the operation fails.
    /// </returns>
    ACDBCORE2D_PORT Acad::ErrorStatus setDecimalChar(wchar_t decimalChar);

    ///<summary> 
    /// Maximum allowable stack scale.
    ///</summary>
    /// <returns>
    /// Returns minimum allowable stack scale.
    /// </returns>
    ACDBCORE2D_PORT static double       minStackScale();
    ///<summary> 
    /// Minimum allowable stack scale.
    ///</summary>
    /// <returns>
    /// Returns Minimum allowable stack scale.
    /// </returns>
    ACDBCORE2D_PORT static double       maxStackScale();

private:
    AcDbImpTextEditorStack*   m_pImpStack;
};

///<summary> 
/// The AcDbTextEditor represent the text editor in the db. You can create a text 
/// editor from a AcDbMtext entity. From text editor user can acesss the information
/// about the MTEXT objects like selection, cursor, columns, paragraphs, wipeout 
/// and so on. You can also input/delete some charactors in the current cursor 
/// position (AcDbTextEditorCursor). When you don't need the text editor, make sure 
/// to call the close() function to release the allocated resource. In that function
/// it has a parameter to tell editor to save/don't save the changes back to MTEXT
/// object. Also please note that the text editor need a opened MTEXT object. And after
/// the editor is closed it will not close your MTEXT object. Please manage the input
/// entity life time by hand.
/// Note that the location in text editor is volatile object. If you saved one location,
/// then call some some functions (for example the columns setting functions, paragraph
/// setting function, selection/cursor inserting functions and so on.)who will make text 
/// editor re-wrap itself. The saved location is in invalid state.
///</summary>
class AcDbTextEditor : public AcDbTextEditorSelectable
{
public:
    /// <summary>
    /// These flags describe text find mode.
    /// </summary>
    enum TextFindFlags {
        /// <summary>
        /// Set this flag to find the text with case sensitive.
        /// </summary>
        kFindMatchCase = 1 << 0,
        /// <summary>
        /// Set this flag to find the text to match the whole word.
        /// </summary>
        kFindWholeWord = 1 << 1,
        /// <summary>
        /// Set this flag to find the text to match half/full form.
        /// </summary>
        kFindHalfFullForm = 1 << 2,
        /// <summary>
        /// Set this flag to find the text without the comparison of accent.
        /// </summary>
        kFindIgnoreAccent = 1 << 3,
        /// <summary>
        /// Set this flag to find the text with wild cards.
        /// </summary>
        kFindUseWildcards = 1 << 4,
    };

    /// <summary>
    /// This enumerator describes text find exit status.
    /// </summary>
    enum ExitStatus
    {
        /// <summary>
        /// Exit find and replace directly without changes.
        /// </summary>
        kExitQuit = 0,
        /// <summary>
        /// Exit find and replace, saving the changes to the entity.
        /// </summary>
        kExitSave,
    };
    ///<summary> 
    /// Factory method, it creates the text editor object from a AcDbMText entity.
    ///</summary>
    /// <param name="pMText">MTEXT object.</param>
    /// <returns>
    /// AcDbTextEditor object pointer. If you don't use it, please call close() 
    /// to release it.
    /// </returns>
    ACDBCORE2D_PORT static AcDbTextEditor* createDbTextEditor(AcDbMText* pMText);

    ///<summary> 
    /// Close the AcDbTextEditor object.
    ///</summary>
    /// <param name="stat">Exit flag to specify if save the text editor changes 
    /// back to entity.</param>
    ACDBCORE2D_PORT virtual void  close(ExitStatus stat);

    ///<summary> 
    /// Re-wrap, re-adjust and refresh all the text lines in editor.
    ///</summary>
    ACDBCORE2D_PORT void   redraw();

    ///<summary> 
    /// Gets TextEditor AcDbTextEditorColumns Object. If the defined width of the
    /// MTEXT is zero, it doesn't support the columns. It will return NULL in that
    /// case.
    ///</summary>
    /// <returns>
    /// Returns the AcDbTextEditorColumns object for the TextEditor.
    /// </returns>
    ACDBCORE2D_PORT AcDbTextEditorColumns* columns();

    ///<summary> 
    /// Gets TextEditor AcDbTextEditorWipeout Object.
    ///</summary>
    /// <returns>
    /// Returns the AcDbTextEditorWipeout object for the TextEditor.
    /// </returns>
    ACDBCORE2D_PORT AcDbTextEditorWipeout* wipeout();

    ///<summary> 
    /// Gets AcDbTextEditorParagraphIterator that iterates all the paragraphs 
    /// in the TextEditor. The caller of this function must delete the iterator
    /// object when it is no longer needed.
    ///</summary>
    /// <returns>
    /// Returns an AcDbTextEditorParagraphIterator object for the TextEditor
    /// paragraphs.
    /// </returns>
    ACDBCORE2D_PORT AcDbTextEditorParagraphIterator* newParagraphsIterator();

    ///<summary> 
    /// Get current selection in the TextEditor. selection() and cursor() are 
    /// mutually exclusive, if selection != NULL then cursor()==NULL and vice versa.
    ///</summary>
    /// <returns>
    /// Returns a pointer to the current TextEditor selection.
    /// If there is no current selection then the return value is NULL.
    /// </returns>
    ACDBCORE2D_PORT virtual AcDbTextEditorSelection* selection();

    ///<summary> 
    /// Get current TextEditor cursor. selection() and cursor() are mutually exclusive,
    /// if selection != NULL then cursor()==NULL and vice versa.
    ///</summary>
    /// <returns>
    /// Returns a pointer to the current TextEditor cursor.
    /// If there is no cursor then the return value is NULL.
    /// </returns>
    ACDBCORE2D_PORT virtual AcDbTextEditorCursor*    cursor();

    ///<summary> 
    /// Clear current selection in the TextEditor. After call the function, the 
    /// selection() function will return NULL. There is no selection object in text
    /// editor after call the function. At this point you can get a current cursor
    /// object from text editor. The current cursor is placed at the end location of
    /// the cleared selection.
    ///</summary>
    /// <returns>
    /// Returns Acad::eOk if the operation succeeds.
    /// Returns Acad::eInvalidInput if the operation fails.
    /// </returns>
    ACDBCORE2D_PORT Acad::ErrorStatus clearSelection();

    ///<summary> 
    /// Makes a selection of text in the TextEditor. After call the function, the
    /// cursor() function will return NULL. There is no current cursor object in 
    /// text editor after call the function. At this point you can get the current
    /// selection object from text editor.
    /// Note that the location in text editor is volatile object. If you saved one location,
    /// then call some some functions who will make text editor re-wrap itself. The saved
    /// location is in invalid state.
    ///</summary>
    /// <param name="pStart">Start location of selection.</param>
    /// <param name="pEnd">End location of selection.</param>
    /// <returns>
    /// Returns Acad::eOk if the operation succeeds.
    /// Returns Acad::eInvalidInput if the operation fails.
    /// </returns>
    ACDBCORE2D_PORT Acad::ErrorStatus makeSelection(const AcDbTextEditorLocation* pStart,
        const AcDbTextEditorLocation* pEnd);

    ///<summary> 
    /// Find first text match in a selection.
    /// Note that the location in text editor is volatile object. If you saved one location,
    /// then call some some functions who will make text editor re-wrap itself. The saved
    /// location is in invalid state.
    ///</summary>
    /// <param name="text">Search text.</param>
    /// <param name="flags">Find flags. It can be zero or the bit operation result
    /// from the values in the TextFindFlags enum. Note that the flag kFindWholeWords
    /// and kFindWildCards are mutually exclusive. If you set them at the same time, 
    /// we will ignore the kFindWholeWords flag.</param>
    /// <param name="pStart">Start of location to search. If "text" is found the var 
    /// will be updated with the found start location. If there is no match found, it 
    /// will be set to NULL.</param>
    /// <param name="pEnd">End of location to search. If "text" is found the var will 
    /// be updated with the found end location. If there is no match found, it will 
    /// be set to NULL.</param>
    /// <returns>
    /// Returns Acad::eOk if the operation succeeds.
    /// Returns Acad::eInvalidInput if the operation fails.
    /// </returns>
    ACDBCORE2D_PORT Acad::ErrorStatus findText(const ACHAR* text, int flags,
        AcDbTextEditorLocation*& pStart,
        AcDbTextEditorLocation*& pEnd);

    ///<summary> 
    /// Set Attachment point for TextEditor object.
    ///</summary>
    /// <param name="attachment">Attachment point type.</param>
    /// <returns>
    /// Returns Acad::eOk if the operation succeeds.
    /// Returns Acad::eInvalidInput if the operation fails.
    /// </returns>
    ACDBCORE2D_PORT Acad::ErrorStatus setAttachment(AcDbMText::AttachmentPoint attachment);

    ///<summary> 
    /// Returns a value describing the attachment point.
    ///</summary>
    /// <returns>
    /// Returns AcDbMText::AttachmentPoint for describing the text editor Attachment point.
    /// </returns>
    ACDBCORE2D_PORT AcDbMText::AttachmentPoint attachment() const;

    ///<summary> 
    /// Set text Style from style index. The index should be between 0 and the 
    /// value returned by getStyleCount() function.
    ///</summary>
    /// <param name="index">Style index.</param>
    /// <returns>
    /// Returns Acad::eOk if the operation succeeds.
    /// Returns Acad::eInvalidInput if the operation fails.
    /// </returns>
    ACDBCORE2D_PORT Acad::ErrorStatus setStyle(int index);

    ///<summary> 
    /// Set text Style from style object id.
    ///</summary>
    /// <param name="indstyleIdex">Style object id.</param>
    /// <returns>
    /// Returns Acad::eOk if the operation succeeds.
    /// Returns Acad::eInvalidInput if the operation fails.
    /// </returns>
    ACDBCORE2D_PORT Acad::ErrorStatus setStyle(AcDbObjectId styleId);
    ///<summary> 
    /// Get TextEditor Textstyle index from textstyle name.
    ///</summary>
    /// <param name="styleName">Textstyle Name.</param>
    /// <returns>
    /// Returns TextEditor Textstyle index.
    /// </returns>
    ACDBCORE2D_PORT int               getIndexFromStyleName(const AcString& styleName);

    ///<summary> 
    /// Get Text style count in current Text editor.
    ///</summary>
    /// <returns>
    /// Returns TextEditor Textstyle count.
    /// </returns>
    ACDBCORE2D_PORT int               getStyleCount() const;

    ///<summary> 
    /// Get Textstyle name from textstyle index. The index should be between 0 
    /// and the value returned by getStyleCount() function.
    ///</summary>
    /// <param name="index">Textstyle index.</param>
    /// <returns>
    /// Returns TextEditor Textstyle name.
    /// </returns>
    ACDBCORE2D_PORT AcString           getStyleName(int index) const;

    ///<summary> 
    /// Get TextEditor Textstyle object id from textstyle index. The index should
    /// be between 0 and the value returned by getStyleCount() function.
    ///</summary>
    /// <param name="index">Textstyle index.</param>
    /// <returns>
    /// Returns Textstyle object id.
    /// </returns>
    ACDBCORE2D_PORT AcDbObjectId      style(int index) const;

    ///<summary> 
    /// Get current Textstyle index.
    ///</summary>
    /// <returns>
    /// Returns current Textstyle index.
    /// </returns>
    ACDBCORE2D_PORT int               currentStyleIndex() const;

    ///<summary> 
    /// Check if TextStyle is annotative.
    ///</summary>
    /// <param name="index">Textstyle index of textstyle to check.</param>
    /// <returns>
    /// Returns true if textstyle is annotative.
    /// </returns>
    ACDBCORE2D_PORT bool              isAnnotativeStyle(int index) const;

    ///<summary> 
    /// Check if the text style is vertical and its font is SHX.
    ///</summary>
    /// <returns>
    /// True if the text style is vertical and its font is SHX. Otherwise it returns
    /// false.
    /// </returns>
    ACDBCORE2D_PORT bool             isVerticalSHX() const;

    ///<summary> 
    /// Check if the text style is vertical and its font is True Type.
    ///</summary>
    /// <returns>
    /// True if the text style is vertical and its font is True Type. Otherwise
    /// it returns false.
    /// </returns>
    ACDBCORE2D_PORT bool             isVerticalTTF() const;

    ///<summary> 
    /// Set Defined Width of MText being edited.
    ///</summary>
    /// <param name="width">New MText width. It must be zero or positive value.</param>
    /// <returns>
    /// Returns Acad::ErrorStatus return code.
    /// </returns>
    ACDBCORE2D_PORT Acad::ErrorStatus setDefinedWidth(double width);

    ///<summary> 
    /// Get Defined Width of MText being edited.
    ///</summary>
    /// <returns>
    /// Returns Defined Width of MText being edited.
    /// </returns>
    ACDBCORE2D_PORT double            definedWidth() const;

    ///<summary> 
    /// Set Defined Height of MText being edited.
    ///</summary>
    /// <param name="height">New MText height. It must be zero or positive value.</param>
    /// <returns>
    /// Returns Acad::ErrorStatus return code.
    /// </returns>
    ACDBCORE2D_PORT Acad::ErrorStatus setDefinedHeight(double height);

    ///<summary> 
    /// Get Defined Height of MText being edited.
    ///</summary>
    /// <returns>
    /// Returns Defined Height of MText being edited.
    /// </returns>
    ACDBCORE2D_PORT double            definedHeight() const;

    ///<summary> 
    /// Get the nominal text height of the MText object. This value is the initial
    /// char height from AcDbMText::textHeight() method.
    ///</summary>
    /// <returns>
    /// Returns Text Height of MText being edited.
    /// </returns>
    ACDBCORE2D_PORT double            textHeight() const;
    ///<summary> 
    /// Set Text Height of MText being edited.
    ///</summary>
    /// <param name="textHeight">New text height. It must be positive value. </param>
    /// <returns>
    /// Returns Acad::ErrorStatus return code.
    /// </returns>
    ACDBCORE2D_PORT Acad::ErrorStatus setTextHeight(double textHeight);

    ///<summary>
    /// Get actualWidth of MText being edited.
    ///</summary>
    /// <returns>
    /// Returns actualWidth of MText being edited.
    /// </returns>
    ACDBCORE2D_PORT double            actualWidth() const;

    ///<summary> 
    /// Get actualHeight of MText being edited.
    ///</summary>
    /// <returns>
    /// Returns actualHeight of MText being edited.
    /// </returns>
    ACDBCORE2D_PORT double            actualHeight() const;

    ///<summary> 
    /// Select all the TextEditor text.
    ///</summary>
    /// <returns>
    /// Returns Acad::ErrorStatus return code.
    /// </returns>
    ACDBCORE2D_PORT Acad::ErrorStatus selectAll(); 

    ///<summary> 
    /// Set auto CAPS on or off.
    ///</summary>
    /// <param name="autoCAPS">Flag to set/unset the auto CAPS.</param>
    /// <returns>
    /// Returns Acad::eOk if the operation succeeded.
    /// Returns Acad::eInvalidInput if the operation fails.
    /// </returns>
    ACDBCORE2D_PORT Acad::ErrorStatus setAutoCAPS(bool autoCAPS);

    ///<summary> 
    /// Get auto CAPS state.
    ///</summary>
    /// <returns>
    /// Returns true if the auto CAPS flag is on, otherwise returns false.
    /// </returns>
    ACDBCORE2D_PORT bool              autoCAPS();

    ///<summary>
    /// Enable Numbering for all the paragraphs of the whole text editor. 
    ///</summary>
    /// <param name="bEnable">enable or disable the numbering flag</param>
    /// <returns>
    /// Returns Acad::eOk if the operation succeeds.
    /// Returns Acad::eInvalidInput if the operation fails.
    /// </returns>
    ACDBCORE2D_PORT Acad::ErrorStatus setEnableNumbering(bool bEnable);
    ///<summary> 
    /// get numbering enabled state for paragraphs. 
    ///</summary>
    /// <returns>
    /// Returns true if numbering is enabled.
    /// </returns>
    ACDBCORE2D_PORT bool              numberingEnabled() const;

    ///<summary> 
    /// Set auto list enabled for paragraphs. You can only call the function when
    /// the numbering is enabled, otherwise it will return Acad::eInvalidInput.
    ///</summary>
    /// <param name="enabled">bool value to set</param>
    /// <returns>
    /// Returns Acad::eOk if the operation succeeds.
    /// Returns Acad::eInvalidInput if the operation fails.
    /// </returns>
    ACDBCORE2D_PORT Acad::ErrorStatus setAutolistEnabled(bool enabled);
    ///<summary> 
    /// get auto list enabled for paragraphs. If the numbering is not enabled, it
    /// will return false.
    ///</summary>
    /// <returns>
    /// Returns true if auto list is enabled for paragraph.
    /// </returns>
    ACDBCORE2D_PORT bool              autolistEnabled() const;

    ///<summary> 
    /// Set tab only delimiter for paragraphs. You can only call the function when
    /// the numbering is enabled, otherwise it will return Acad::eInvalidInput.
    ///</summary>
    /// <param name="tabOnlyDelimiter">bool value to set</param>
    /// <returns>
    /// Returns Acad::eOk if the operation succeeds.
    /// Returns Acad::eInvalidInput if the operation fails.
    /// </returns>
    ACDBCORE2D_PORT Acad::ErrorStatus setTabOnlyDelimiter(bool tabOnlyDelimiter);
    ///<summary> 
    /// get tab only delimiter for paragraphs. If the numbering is not enabled, it
    /// will return false.
    ///</summary>
    /// <returns>
    /// Returns true if tab only delimiter is set for paragraph.
    /// </returns>
    ACDBCORE2D_PORT bool              tabOnlyDelimiter() const;

    ///<summary> 
    /// Get the fonts number in the whole text editor.
    ///</summary>
    /// <returns>
    /// Return the fonts number.
    /// </returns>
    ACDBCORE2D_PORT int               getFontCount() const;
    ///<summary> 
    /// Get TextEditor font name from the specified font index. 
    ///</summary>
    /// <param name="index">Font index.</param>
    /// <returns>
    /// Returns TextEditor font name.
    /// </returns>
    ACDBCORE2D_PORT AcString          getFontName(int index) const;
    ///<summary> 
    ///Check if the specified text editor font is True Type.
    ///</summary>
    /// <param name="index">Font index.</param>
    /// <returns>
    /// Returns true if the font is True Type.
    /// </returns>
    ACDBCORE2D_PORT bool              isTrueTypeFont(int index) const;

    ///<summary> 
    /// Get the count of stack objects in the whole text editor.
    ///</summary>
    /// <returns>
    /// Return the stack num.
    /// </returns>
    ACDBCORE2D_PORT int               stackCount() const;

    ///<summary> 
    /// Get the default value of stack scale.
    ///</summary>
    /// <returns>
    /// Returns default stack scale.
    /// </returns>
    ACDBCORE2D_PORT double             defaultStackScale() const;
    ///<summary> 
    /// Set the default value of stack scale.
    ///</summary>
    /// <param name="scale">Stack scale value. It must be between AcDbTextEditorStack::minStackScale()
    /// and AcDbTextEditorStack::maxStackScale().</param>
    /// <returns>
    /// Returns Acad::eOk if the operation succeeded.
    /// Returns Acad::eInvalidInput if the operation fails.
    /// </returns>
    ACDBCORE2D_PORT Acad::ErrorStatus    setDefaultStackScale(double scale);

    ///<summary> 
    /// Get the default value of stack alignment.
    ///</summary>
    /// <returns>
    /// Returns default stack alignment.
    /// </returns>
    ACDBCORE2D_PORT AcDbTextEditorSelectionBase::FlowAlign defaultStackAlignment() const;
    ///<summary> 
    /// Set the default value of stack alignment.
    ///</summary>
    /// <param name="alignment">Flow align value.</param>
    /// <returns>
    /// Returns Acad::eOk if the operation succeeded.
    /// Returns Acad::eInvalidInput if the operation fails.
    /// </returns>
    ACDBCORE2D_PORT Acad::ErrorStatus    setDefaultStackAlignment(AcDbTextEditorSelectionBase::FlowAlign alignment);

    ///<summary> 
    /// Gets the start location for the whole text editor
    ///</summary>
    /// <returns>
    /// Returns an AcDbTextEditorLocation object for the start of the text editor.
    /// </returns>
    ACDBCORE2D_PORT virtual AcDbTextEditorLocation* startOfText() ADESK_OVERRIDE;

    ///<summary> 
    /// Gets the end location for the whole text editor.
    ///</summary>
    /// <returns>
    /// Returns an AcDbTextEditorLocation object for the end of the text editor.
    /// </returns>
    ACDBCORE2D_PORT virtual AcDbTextEditorLocation* endOfText() ADESK_OVERRIDE;

protected:
    ACDBCORE2D_PORT AcDbTextEditor():m_pImp(NULL) {};
    ACDBCORE2D_PORT virtual ~AcDbTextEditor();

    friend class AcDbTextEditorLocation;
    friend class AcDbTextEditorParagraphIterator;
    TextEditor* m_pImp;

private:
    AcDbTextEditor(const AcDbTextEditor& editor);
    AcDbTextEditor& operator=(const AcDbTextEditor& editor);
};
