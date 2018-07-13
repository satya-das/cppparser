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
// AcEdInplaceTextEditor - provides application level services in accore.dll

#ifndef AcEdInplaceTextEditor_H
#define AcEdInplaceTextEditor_H

#include "dbtexteditor.h"
#include "AcCoreDefs.h"

class IPE_Editor;
class AcEdInplaceTextEditor;
class IAcEdInplaceTextEditorHost;
class AcEdInplaceTextEditorSettingsImp;
class AcEdInplaceTextEditorImp;

///<summary> 
/// The AcEdInplaceTextEditorSettings class is to set the input options when invoking
/// the inplace editor. If you set the different settings, the invoked inplace editor
/// have the different UI or properties.
///</summary>
class AcEdInplaceTextEditorSettings
{
public:
    ///<summary> 
    /// Constructor. It will create a AcEdInplaceTextEditorSettings object with 
    /// default settings for the common MTEXT object.
    ///</summary>
    ACCORE_PORT AcEdInplaceTextEditorSettings();
    ///<summary> 
    /// Destructor.
    ///</summary>
    ACCORE_PORT ~AcEdInplaceTextEditorSettings();

    ///<summary> 
    /// The enum type is for the source entity type. You can create a memory MTEXT
    /// object for the complex entity like table cell or multi-attribute to invoke
    /// the text editor.
    ///</summary>
    enum EntityType
    {
        /// <summary>
        /// This is common MTEXT object.
        /// </summary>
        kDefault,
        /// <summary>
        /// This is a table cell. The current MTEXT is the content copy of the table
        /// cell.
        /// </summary>
        kTableCell,
        /// <summary>
        /// This is multi-attribute. The current MTEXT is the content copy of the 
        /// multi-attribute.
        /// </summary>
        kMultiAttribute
    };

    ///<summary> 
    /// The enum type is to specify the editing flags when invoking the text editor.
    /// You can set one or several flags for the text editor.
    ///</summary>
    enum EditFlags
    {
        ///<summary> 
        /// After invoked the text editor, it has opaque back ground.
        ///</summary>
        kForceOpaqueBackground = 1 << 0,
        ///<summary> 
        /// After invoked the text editor, it will select all the characters in 
        /// the text editor. This flag and kCursorAtEnd are mutually exclusive,
        /// if user set the kSelectAll and kCursorAtEnd, it will ignore the kCursorAtEnd.
        ///</summary>
        kSelectAll = 1 << 1,
        ///<summary> 
        /// After invoked the text editor, the current cursor is placed at the end
        /// of the text editor. This flag and kSelectAll are mutually exclusive,
        /// if user set the kSelectAll and kCursorAtEnd, it will ignore the kCursorAtEnd.
        ///</summary>
        kCursorAtEnd = 1 << 2,
    };

public:
    ///<summary> 
    /// Get the editing flags you specified.
    ///</summary>
    ///<returns>
    /// Return the editing flags from current setting.
    ///</returns>
    ACCORE_PORT int               editFlags() const;
    ///<summary> 
    /// Set the editing flags.
    ///</summary>
    /// <param name="flags">The input editing flags.</param>
    /// <returns>
    /// Returns Acad::eOk if the operation succeeded.
    /// Returns Acad::eInvalidInput if the operation fails.
    /// </returns>
    ACCORE_PORT Acad::ErrorStatus setEditFlags(int flags);

    ///<summary> 
    /// Get the source entity type for current editing MTEXT object. You can create
    /// a memory copy of MTEXT for the complex entity like table cell or multi-attribute.
    ///</summary>
    ///<returns>
    /// Return the entity type you set.
    ///</returns>
    ACCORE_PORT EntityType        sourceEntityType() const;
    ///<summary> 
    /// Set the source entity type flag for the current editing MTEXT.
    ///</summary>
    /// <param name="type">The current source entity type.</param>
    /// <returns>
    /// Returns Acad::eOk if the operation succeeded.
    /// Returns Acad::eInvalidInput if the operation fails.
    /// </returns>
    ACCORE_PORT Acad::ErrorStatus setSourceEntityType(EntityType type);

    ///<summary> 
    /// Check if the text editor supports the paragraph.
    ///</summary>
    /// <returns>
    /// Returns true if it supports the paragraph. Otherwise it will return false.
    /// </returns>
    ACCORE_PORT bool              tabSupported() const;
    ///<summary> 
    /// Set if the text editor supports the paragraph. Note that if the current input
    /// type is table cell or simple MTEXT, it will ignore the setting and they don't
    /// support the paragraph.
    ///</summary>
    /// <param name="bTab">Flag to set if it supports the editor paragraph.</param>
    /// <returns>
    /// Returns Acad::eOk if the operation succeeded.
    /// Returns Acad::eInvalidInput if the operation fails.
    /// </returns>
    ACCORE_PORT Acad::ErrorStatus setSupportTab(bool bTab);

    ///<summary> 
    /// Check to see if the input entity is a simple MTEXT object. For the simple
    /// MTEXT it has no columns, no paragraphs and so on. It has only basic MTEXT
    /// functionalities.
    ///</summary>
    /// <returns>
    /// Returns true if it specified the input entity is a simple MTEXT object. 
    /// Otherwise it will return false.
    /// </returns>
    ACCORE_PORT bool              simpleMText() const;
    ///<summary> 
    /// Specify that the input entity is a simple MTEXT object.
    ///</summary>
    /// <param name="bSimpleMText">Flag to specify if it is a simple MTEXT.</param>
    /// <returns>
    /// Returns Acad::eOk if the operation succeeded.
    /// Returns Acad::eInvalidInput if the operation fails.
    /// </returns>
    ACCORE_PORT Acad::ErrorStatus setSimpleMText(bool bSimpleMText);

    ///<summary> 
    /// Get the defined height setting in the text editor. This setting will work if
    /// the input entity is not a database resident object. Otherwise the defined height
    /// is the height of the MTEXT or TEXT object self.
    ///</summary>
    /// <returns>
    /// Returns the defined height value in the setting.
    /// </returns>
    ACCORE_PORT double            definedHeight() const;
    ///<summary> 
    /// Set the defined height for the non-database resident input entity.
    ///</summary>
    /// <param name="height">The defined height to set.</param>
    /// <returns>
    /// Returns Acad::eOk if the operation succeeded.
    /// Returns Acad::eInvalidInput if the operation fails.
    /// </returns>
    ACCORE_PORT Acad::ErrorStatus setDefinedHeight(double height);
protected:
    AcEdInplaceTextEditorSettingsImp* m_pImp;
private:
    AcEdInplaceTextEditorSettings(const AcEdInplaceTextEditorSettings& editor);
    AcEdInplaceTextEditorSettings& operator=(const AcEdInplaceTextEditorSettings& editor);
};

///<summary> 
/// This classs represents the in-place text editor in ACAD. It inherits from the 
/// AcDbTextEditor class. And from the object you can also access the functions 
/// in db editor like columns, paragraph and so on.
/// User can invoke the ACAD in-place text editor by a MTEXT or TEXT objects. Also
/// you can create a non-database resident MTEXT object for complex object and invoke
/// the in-place text editor.
/// For one ACAD session at the same time there is only one in-place text editor. 
/// And if you want to quit the in place text editor, please call the close() function
/// to specify if it needs to save the changes back to input entity.
///</summary>
class AcEdInplaceTextEditor : public AcDbTextEditor
{
public:
    ///<summary> 
    /// Get the current active in-place text editor object.
    ///</summary>
    /// <returns>
    /// Current text editor object pointer; return NULL if there is no
    /// active in place text editor.
    /// </returns>
    ACCORE_PORT static AcEdInplaceTextEditor* current();

    /// <summary>
    /// For internal use only.
    /// </summary>
    ACCORE_PORT void setHost(IAcEdInplaceTextEditorHost* pHost);

    ///<summary> 
    ///Invoke the in-place text editor for the MTEXT object. If there is a active 
    ///in-place text editor, it will close the current in-place text editor and invoke
    ///editor for the input MTEXT object.
    ///</summary>
    /// <param name="pMtext">The in-place text editor will edit the MTEXT.</param>
    /// <param name="pSettings">The in-place text editor invoking settings. If it 
    /// is NULL, it will invoke the in-place text editor by the default settings.</param>
    /// <returns>
    /// Returns Acad::eOk if it invoke the in-place text editor successfully. Otherwise
    /// it returns the Acad::eInvalidInput.
    /// </returns>
    ACCORE_PORT static Acad::ErrorStatus invoke(AcDbMText* pMtext, const AcEdInplaceTextEditorSettings* pSettings);
    ///<summary> 
    ///Invoke the in-place text editor for the TEXT object. If there is a active 
    ///in-place text editor, it will close the current in-place text editor and invoke
    ///editor for the input TEXT object.
    ///</summary>
    /// <param name="pText">The in-place text editor will edit the text.</param>
    /// <param name="appendedEntities">If the current TEXT object is a new entity
    /// (not in database), user can left click and start another TEXT object input session.
    /// When closing the editor, it will post the new TEXT objects to current database.
    /// This parameter will return the appended entities. </param>
    /// <returns>
    /// Returns Acad::eOk if it invoke the in-place text editor successfully. Otherwise
    /// it returns the Acad::eInvalidInput.
    /// </returns>
    ACCORE_PORT static Acad::ErrorStatus invoke(AcDbText* pText, AcDbObjectIdArray* appendedEntities);

public:
    // Enums for text editor operation undo type.
    /// <summary>
    /// Describes the undo type for each kind of operation.
    /// </summary>
    enum TextUndoType {
        /// <summary>
        /// Undo type for typing operation in text editor.
        /// </summary>
        kUndoTyping = 1,
        /// <summary>
        /// Undo type for the operation to toggle bold on.
        /// </summary>
        kUndoBoldOn,
        /// <summary>
        /// Undo type for the operation to toggle bold off.
        /// </summary>
        kUndoBoldOff,
        /// <summary>
        /// Undo type for the operation to toggle italic on.
        /// </summary>
        kUndoItalicOn,
        /// <summary>
        /// Undo type for the operation to toggle italic off.
        /// </summary>
        kUndoItalicOff,
        /// <summary>
        /// Undo type for the operation to toggle underline on.
        /// </summary>
        kUndoUnderlineOn,
        /// <summary>
        /// Undo type for the operation to toggle underline off.
        /// </summary>
        kUndoUnderlineOff,
        /// <summary>
        /// Undo type for the operation to toggle overline on.
        /// </summary>
        kUndoOverlineOn,
        /// <summary>
        /// Undo type for the operation to toggle overline off.
        /// </summary>
        kUndoOverlineOff,
        /// <summary>
        /// Undo type for the operation to set font.
        /// </summary>
        kUndoFont,
        /// <summary>
        /// Undo type for the operation to set height.
        /// </summary>
        kUndoHeight,
        /// <summary>
        /// Undo type for the operation to set color.
        /// </summary>
        kUndoColor,
        /// <summary>
        /// Undo type for the operation to set oblique angle.
        /// </summary>
        kUndoObliqueAngle,
        /// <summary>
        /// Undo type for the operation to set width scale.
        /// </summary>
        kUndoWidthScale,
        /// <summary>
        /// Undo type for the operation to set tracking factor.
        /// </summary>
        kUndoTrackingFactor,
        /// <summary>
        /// Undo type for the operation to set language.
        /// </summary>
        kUndoLanguage,
        /// <summary>
        /// Undo type for the operation to input a back space.
        /// </summary>
        kUndoBackspace,
        /// <summary>
        /// Undo type for the operation to delete.
        /// </summary>
        kUndoDelete,
        /// <summary>
        /// Undo type for the operation to paste.
        /// </summary>
        kUndoPaste,
        /// <summary>
        /// Undo type for the operation to cut.
        /// </summary>
        kUndoCut,
        /// <summary>
        /// Undo type for the operation to create stack.
        /// </summary>
        kUndoStack,
        /// <summary>
        /// Undo type for the operation to remove stack.
        /// </summary>
        kUndoUnstack,
        /// <summary>
        /// Undo type for the operation to set stack properties.
        /// </summary>
        kUndoStackProperties,
        /// <summary>
        /// Undo type for the operation to insert field.
        /// </summary>
        kUndoFieldInsert,
        /// <summary>
        /// Undo type for the operation to convert the field.
        /// </summary>
        kUndoFieldConvert,
        /// <summary>
        /// Undo type for the operation to update the field.
        /// </summary>
        kUndoFieldUpdate,
        /// <summary>
        /// Undo type for the operation to insert symbol.
        /// </summary>
        kUndoSymbolInsert,
        /// <summary>
        /// For internal use only.
        /// </summary>
        kUndoAutoField,
        /// <summary>
        /// For internal use only.
        /// </summary>
        kUndoAutoStack,
        /// <summary>
        /// For internal use only.
        /// </summary>
        kUndoAutoSymbol,
        /// <summary>
        /// For internal use only.
        /// </summary>
        kUndoAutoDTextEscape,
        /// <summary>
        /// For internal use only.
        /// </summary>
        kUndoAutoMifOrCif,
        /// <summary>
        /// For internal use only.
        /// </summary>
        kUndoAutoDimension,
        /// <summary>
        /// For internal use only..
        /// </summary>
        kUndoAutoDimBreak,
        /// <summary>
        /// Undo type for the operation to check spelling automatically.
        /// </summary>
        kUndoAutoSpell,
        /// <summary>
        /// Undo type for the operation to set text style.
        /// </summary>
        kUndoStyle,
        /// <summary>
        /// Undo type for the operation to set the attachment automatically.
        /// </summary>
        kUndoAttachment,
        /// <summary>
        /// Undo type for the operation to change the case.
        /// </summary>
        kUndoChangeCase,
        /// <summary>
        /// Undo type for the operation to import text.
        /// </summary>
        kUndoImportText,
        /// <summary>
        /// Undo type for the operation to combine paragraphs.
        /// </summary>
        kUndoCombineParagraphs,
        /// <summary>
        /// Undo type for the operation to remove character formatting.
        /// </summary>
        kUndoRemoveCharFormatting,
        /// <summary>
        /// Undo type for the operation to remove paragraph formatting.
        /// </summary>
        kUndoRemoveParaFormatting,
        /// <summary>
        /// Undo type for the operation to remove all kind of formatting.
        /// </summary>
        kUndoRemoveAllFormatting,
        /// <summary>
        /// Undo type for the operation to replace all matched text.
        /// </summary>
        kUndoReplaceAll,
        /// <summary>
        /// Undo type for the operation to replace matched text.
        /// </summary>
        kUndoReplace,
        /// <summary>
        /// Undo type for the operation to set paragraph attributes.
        /// </summary>
        kUndoParagraphAttributes,
        /// <summary>
        /// Undo type for the operation to set defined width.
        /// </summary>
        kUndoSetDefinedWidth,
        /// <summary>
        /// Undo type for the operation to set defined height.
        /// </summary>
        kUndoSetDefinedHeight,
        /// <summary>
        /// Undo type for the operation to set character attributes.
        /// </summary>
        kUndoCharAttributes,
        /// <summary>
        /// Undo type for wipeout operation.
        /// </summary>
        kUndoWipeout,
        /// <summary>
        /// For internal use only.
        /// </summary>
        kUndoDimensionInsert,
        /// <summary>
        /// For internal use only.
        /// </summary>
        kUndoDimBreakInsert,
        /// <summary>
        /// For internal use only.
        /// </summary>
        kUndoCustomConvert,
        /// <summary>
        /// Undo type for the operation to delete and move selection.
        /// </summary>
        kUndoDeleteAndMoveSelection,
        /// <summary>
        /// Undo type for the operation to number the paragraph.
        /// </summary>
        kUndoParagraphNumbering,
        /// <summary>
        /// Undo type for the operation to set cursor attributes.
        /// </summary>
        kUndoCursorAttributes,
        /// <summary>
        /// Undo type for the operation to columns operation.
        /// </summary>
        kUndoColumns,
        /// <summary>
        /// Undo type for the operation to set annotation scaling state.
        /// </summary>
        kUndoAnnoState,
        /// <summary>
        /// For internal use only.
        /// </summary>
        kUndoDimensionTweak,
        /// <summary>
        /// For internal use only.
        /// </summary>
        kUndoDimensionSymbol,
        /// <summary>
        /// For internal use only.
        /// </summary>
        kUndoDimensionTemplate,
    };

    ///<summary> 
    /// Check that there is something to undo.
    ///</summary>
    /// <returns>
    /// Returns true if there is something to undo.
    /// </returns>
    ACCORE_PORT bool canUndo() const;

    ///<summary> 
    /// Undo last operation. If it can't undo (the canUndo() returns false), it 
    /// will return Acad::eInvalidInput for you.
    ///</summary>
    /// <returns>
    /// Returns Acad::eOk if the undo succeeded.
    /// Returns Acad::eInvalidInput if the operation fails.
    /// </returns>
    ACCORE_PORT Acad::ErrorStatus undo();

    ///<summary> 
    /// Check that there is something to redo.
    ///</summary>
    /// <returns>
    /// Returns true if there is something to redo.
    /// </returns>
    ACCORE_PORT bool canRedo() const;

    ///<summary> 
    /// Redo last operation. If it can't redo (the canRedo() returns false), it 
    /// will return Acad::eInvalidInput for you.
    ///</summary>
    /// <returns>
    /// Returns Acad::eOk if the redo succeeded.
    /// Returns Acad::eInvalidInput if the operation fails.
    /// </returns>
    ACCORE_PORT Acad::ErrorStatus redo();

    ///<summary> 
    /// Add undo marker in the TextEditor undo queue.
    ///</summary>
    /// <param name="type">Undo type, it is the enum type for TextUndoType.</param>
    /// <returns>
    /// Returns Acad::ErrorStatus return code.
    /// </returns>
    ACCORE_PORT Acad::ErrorStatus  addUndoMarker(TextUndoType type);

    ///<summary> 
    /// Check that it can cut the text.
    ///</summary>
    /// <returns>
    /// Returns true if it can cut the text, otherwise returns false.
    /// </returns>
    ACCORE_PORT bool              canCut() const;
    ///<summary> 
    /// Check that it can copy the text.
    ///</summary>
    /// <returns>
    /// Returns true if it can copy the text, otherwise returns false.
    /// </returns>
    ACCORE_PORT bool              canCopy() const;
    ///<summary> 
    /// Check that it can paste the text.
    ///</summary>
    /// <returns>
    /// Returns true if it can paste the text, otherwise returns false.
    /// </returns>
    ACCORE_PORT bool              canPaste() const;

    ///<summary> 
    /// It will cut the current selected text in editor and save the text in clipboard.
    /// Note that it will delete current selection and there is no selection after called
    /// the function. If the canCut() return false, it will return Acad::eInvalidInput for
    /// you.
    ///</summary>
    /// <returns>
    /// Returns Acad::eOk if the operation succeeds.
    /// Returns Acad::eInvalidInput if the operation fails.
    /// </returns>
    ACCORE_PORT Acad::ErrorStatus cut();
    ///<summary> 
    /// It will copy the current selected text in editor and save the text in clipboard.
    /// This function will not affect the selection object in text editor. If the canCopy()
    /// return false, it will return Acad::eInvalidInput for you.
    ///</summary>
    /// <returns>
    /// Returns Acad::eOk if the operation succeeds.
    /// Returns Acad::eInvalidInput if the operation fails.
    /// </returns>
    ACCORE_PORT Acad::ErrorStatus copy();
    ///<summary> 
    /// It will paste the text in clipboard to text editor at the current text editor
    /// selectable object (cursor or selection). If it selected some text, after called
    /// the function, it will delete current selection. If the canPaste() return false, 
    /// it will return Acad::eInvalidInput for you.
    ///</summary>
    /// <returns>
    /// Returns Acad::eOk if the operation succeeds.
    /// Returns Acad::eInvalidInput if the operation fails.
    /// </returns>
    ACCORE_PORT Acad::ErrorStatus paste();
    ///<summary> 
    /// In the function it will paste the text with the following text editor default 
    /// char formats and without paragraph formats.
    /// If it selected some text, after called the function, it will delete current 
    /// selection. If the canPaste() return false, it will return Acad::eInvalidInput
    /// for you.
    /// The text editor default char formats are from input entity's properties and its
    /// text style.
    /// For char formats it includes the following character formatting properties: 
    /// font, bold, italic, overline, text height, color, underline, language, 
    /// oblique angle, width scale and so on; for paragraph formats it includes 
    /// the following properties: first indent, left indent, right indent, before space, 
    /// after space, line space factor, line space style, paragraph alignment, paragraph tabs,
    /// numbering and so on.
    ///</summary>
    /// <returns>
    /// Returns Acad::eOk if the operation succeeds.
    /// Returns Acad::eInvalidInput if the operation fails.
    /// </returns>
    ACCORE_PORT Acad::ErrorStatus pasteWithoutFormats();

    ///<summary> 
    /// Check if the in place text editor undo recording is disabled.
    ///</summary>
    /// <returns>
    /// Returns true if the undo recording is disabled, otherwise returns false.
    /// </returns>
    ACCORE_PORT bool              undoRecordingDisabled();
    ///<summary> 
    /// It will stop/start the in place text editor undo recording. Note that after 
    /// stopped the undo recording, text editor will not record any changes from
    /// that point even you call the addUndoMarker() function.
    ///</summary>
    /// <param name="disabled">The flag to start/stop the in place text editor undo recording.</param>
    /// <returns>
    /// Returns Acad::eOk if the operation succeeds.
    /// Returns Acad::eInvalidInput if the operation fails.
    /// </returns>
    ACCORE_PORT Acad::ErrorStatus setUndoRecordingDisable(bool disabled);

    ///<summary> 
    /// Set Annotative. It can only set the annotative property when the input 
    /// entity is MTEXT object. 
    ///</summary>
    /// <param name="bSet">Annotative state.</param>
    /// <returns>
    /// Returns Acad::eOk if the operation succeeded.
    /// Returns Acad::eInvalidInput if the operation fails.
    /// </returns>
    ACCORE_PORT Acad::ErrorStatus setAnnotative(bool bSet);

    ///<summary> 
    /// Get annotative state.
    ///</summary>
    /// <returns>
    /// Returns true if TextEditor is in annotative state.
    /// </returns>
    ACCORE_PORT bool              annotative() const;

    ///<summary> 
    /// Check if the current entity for in place text editor is tale cell.
    ///</summary>
    /// <returns>
    /// True if the entity is table cell.
    /// </returns>
    ACCORE_PORT bool   isTableCell() const;
    ///<summary> 
    /// Check if the current entity for in place text editor is simple MTEXT object.
    ///</summary>
    /// <returns>
    /// True if the entity is simple MTEXT.
    /// </returns>
    ACCORE_PORT bool   isSimpleMtext() const;
    ///<summary> 
    /// Check if the current entity for in place text editor is text object.
    ///</summary>
    /// <returns>
    /// True if the entity is text object.
    /// </returns>
    ACCORE_PORT bool   isText() const;

    ///<summary> 
    /// Check if the current entity for in place text editor is multi-line attribute.
    ///</summary>
    /// <returns>
    /// True if the entity is multi-line attribute.
    /// </returns>
    ACCORE_PORT bool   isMultiAttribute() const;

    ///<summary> 
    /// Check if the current in place text editor supports paragraph.
    ///</summary>
    /// <returns>
    /// True if the current in place text editor supports paragraph.
    /// </returns>
    ACCORE_PORT bool   isParagraphSupported() const;

    ///<summary> 
    /// Replace all the matched strings in current Text Editor. And it will pop out
    /// a message box to prompt that it has completed.
    ///</summary>
    /// <param name="findFlags">Find flags, for example the whole word flag, 
    /// the upper case and so on.</param>
    /// <param name="findStr">Find string.</param>
    /// <param name="replaceStr">Replace string.</param>
    /// <returns>
    /// void
    /// </returns>
    ACCORE_PORT void   replaceAllMatchItems(int findFlags, const AcString& findStr, const AcString& replaceStr) const;
    ///<summary> 
    /// Replace the current selected matched string in Text Editor. It will clear 
    /// the current selection and the cursor will be placed at the end of the replaced text. 
    /// If there is no item found it will pop out a message box to prompt that it 
    /// has completed.
    ///</summary>
    /// <param name="findFlags">Find flags, for example the whole word flag, 
    /// the upper case and so on.</param>
    /// <param name="findStr">Find string.</param>
    /// <param name="replaceStr">Replace string.</param>
    /// <returns>
    /// void
    /// </returns>
    ACCORE_PORT void   replaceCurrentMatchItem(int findFlags, const AcString& findStr, const AcString& replaceStr) const;
    ///<summary> 
    /// Find the matched string in Text Editor from the current cursor or the end 
    /// location of the current selection. It will select and highlight the matched 
    /// item. If there is no item found it will pop out a message box.
    ///</summary>
    /// <param name="findFlags">Find flags, for example the whole word flag, the 
    /// upper case and so on.</param>
    /// <param name="findStr">Find string.</param>
    /// <returns>
    /// void
    /// </returns>
    ACCORE_PORT void   findMatchItem(int findFlags, const AcString& findStr) const;
    
    ///<summary> 
    /// Set if the current text editor can exit.
    ///</summary>
    /// <param name="bCanExit">Can/can't exit current text editor.</param>
    /// <returns>
    /// void
    /// </returns>
    ACCORE_PORT void   setCanExitInplaceEditor(bool bCanExit);
    ///<summary> 
    /// Check if the current text editor can exit.
    ///</summary>
    /// <returns>
    /// bool
    /// </returns>
    ACCORE_PORT bool   canExitInplaceEditor();

    ///<summary> 
    /// Remove Text editor highlight.
    ///</summary>
    /// <returns>
    /// void
    /// </returns>
    ACCORE_PORT void   removeHightlight();
    ///<summary> 
    /// Draw text editor highlight.
    ///</summary>
    /// <returns>
    /// void
    /// </returns>
    ACCORE_PORT void   drawHighlight();

    ///<summary> 
    /// Get Text editor alignment from its attachment point.
    ///</summary>
    /// <returns>
    /// Return the Text editor alignment.
    /// </returns>
    ACCORE_PORT AcDbTextEditorParagraph::AlignmentType getAlignmentFromAttachment() const;

    ///<summary> 
    /// Get Text editor entity's layer color.
    ///</summary>
    /// <returns>
    /// Return the color of text editor entity.
    /// </returns>
    ACCORE_PORT COLORREF layerColor() const;

    ///<summary> 
    /// Check if the text editor speller enabled.
    ///</summary>
    /// <returns>
    /// True if the speller is enabled.
    /// </returns>
    ACCORE_PORT bool     spellerEnabled() const;
    ///<summary> 
    /// Toggles on and off as-you-type-spelling. .
    ///</summary>
    /// <returns>
    /// void
    /// </returns>
    ACCORE_PORT void     toggleSpelling();

    ///<summary> 
    /// Insert the context in the file name file to the text editor.
    ///</summary>
    /// <param name="fileName">Insert file name.</param>
    /// <returns>
    /// void
    /// </returns>
    ACCORE_PORT void     insertFile(const AcString& fileName);

    ///<summary> 
    /// Check if the current text editor supports ruler.
    ///</summary>
    /// <returns>
    /// True if the ruler is supported.
    /// </returns>
    ACCORE_PORT bool     rulerSupported() const;
    ///<summary> 
    /// Sets or unsets the display of the ruler.
    ///</summary>
    /// <param name="hidRuler">Flag to hide/show ruler.</param>
    /// <returns>
    /// void
    /// </returns>
    ACCORE_PORT void   setRulerHidden(bool hideRuler);
    ///<summary> 
    /// Check if the Ruler is hidden.
    ///</summary>
    /// <returns>
    /// True if the ruler is hidden.
    /// </returns>
    ACCORE_PORT bool   rulerHidden() const;

    ///<summary> 
    /// Sets or unsets the In-place Editor Background. If the background is
    /// opaque then underlying geometry will be occluded. Note that if the forcedOpaqueBackground()
    /// is true, there is no effect to call setOpaqueBackground() function. The 
    /// inplace text editor will always has opaque background.
    ///</summary>
     /// <param name="opaqueBackground">Flag to set/unset opaque background.</param>
    /// <returns>
    /// void
    /// </returns>
    ACCORE_PORT void   setOpaqueBackground(bool opaqueBackground);

    ///<summary> 
    /// Check if the In-place Editor Background is opaque. If the background is
    /// opaque then underlying geometry will be occluded.
    ///</summary>
    /// <returns>
    /// True if the background is opaque.
    /// </returns>
    ACCORE_PORT bool   opaqueBackground();

    ///<summary> 
    /// Check if the In-place Editor Background is forced opaque. If the current input
    /// entity type is kTableCell, the wysiwyg setting is off or the invoking setting
    /// (AcEdInplaceTextEditorSettings::editFlags()) has kForceOpaqueBackground bit, 
    /// the function return true.
    ///</summary>
    /// <returns>
    /// True if the background is forced opaque.
    /// </returns>
    ACCORE_PORT bool   forcedOpaqueBackground();

    ///<summary> 
    /// Check if the In-place Editor wysiwyg is on.
    ///</summary>
    /// <returns>
    /// True if the wysiwyg setting is on, otherwise returns false.
    /// </returns>
    ACCORE_PORT bool   wysiwyg();
    ///<summary> 
    /// Set the In-place Editor to be wysiwyg. If this is toggled on then the 
    /// In-place Editor is always show the text as it appears in the view
    /// even if the zoom is such that the text is very small.
    ///</summary>
    ACCORE_PORT void   enableWysiwyg();

    /// <summary> 
    /// This function is used to exit the InPlace Editor.
    /// </summary>
    /// <param name="stat">Exit flag to specify if save the text editor changes back to entity.</param>
    /// <returns>
    /// void
    /// </returns>
    ACCORE_PORT virtual void  close(ExitStatus stat);

    /// <summary> 
    /// This function is used to invoke the other symbol dialog.
    /// </summary>
    /// <returns>
    /// void
    /// </returns>
    ACCORE_PORT void   otherSymbol();

    /// <summary> 
    /// Sets or unsets the display of the tool bar.
    /// </summary>
    /// <param name="bHideToolbar">Flag to hide/show tool bar.</param>
    /// <returns>
    /// void
    /// </returns>
    ACCORE_PORT void   setToolbarHidden(bool bHideToolbar);
    /// <summary> 
    /// Check if the toolbar is hidden.
    /// </summary>
    /// <returns>
    /// True if the toolbar is hidden.
    /// </returns>
    ACCORE_PORT bool   toolbarHidden() const;

    /// <summary> 
    /// Sets or unsets the display of the tool bar option.
    /// </summary>
    /// <param name="bHideOption">Flag to hide/show toolbar option.</param>
    /// <returns>
    /// void
    /// </returns>
    ACCORE_PORT void   setToolbarOptionHidden(bool bHideOption);
    ///<summary> 
    /// Check if the toolbar option is hidden.
    ///</summary>
    /// <returns>
    /// True if the toolbar option is hidden.
    /// </returns>
    ACCORE_PORT bool   toolbarOptionHidden() const;

    /// <summary> 
    /// Invoke the text editor columns menu.
    /// </summary>
    /// <param name="menuPt">The menu will display at this point. This point is in 
    /// screen coordinates. </param>
    /// <param name="parentHandle">The menu's parent window handle.</param>
    /// <returns>
    /// Returns Acad::eOk if the operation succeeds.
    /// Returns Acad::eInvalidInput if the operation fails
    /// </returns>
    ACCORE_PORT Acad::ErrorStatus columnMenusInput(AcGePoint2d* menuPt, HWND parentHandle);
    /// <summary> 
    /// Invoke the text editor attachment menu.
    /// </summary>
    /// <param name="menuPt">The menu will display at this point.This point is in 
    /// screen coordinates. </param>
    /// <param name="parentHandle">The menu's parent window handle.</param>
    /// <returns>
    /// Returns Acad::eOk if the operation succeeds.
    /// Returns Acad::eInvalidInput if the operation fails
    /// </returns>
    ACCORE_PORT Acad::ErrorStatus attachmentMenusInput(AcGePoint2d* menuPt, HWND parentHandle);
    ///<summary> 
    /// Invoke the text editor line space menu.
    ///</summary>
    /// <param name="menuPt">The menu will display at this point.This point is in 
    /// screen coordinates. </param>
    /// <param name="parentHandle">The menu's parent window handle.</param>
    /// <returns>
    /// Returns Acad::eOk if the operation succeeds.
    /// Returns Acad::eInvalidInput if the operation fails
    /// </returns>
    ACCORE_PORT Acad::ErrorStatus lineSpaceMenusInput(AcGePoint2d* menuPt, HWND parentHandle);
    /// <summary> 
    /// Invoke the text editor paragraph numbering menu.
    /// </summary>
    /// <param name="menuPt">The menu will display at this point. This point is in 
    /// screen coordinates. </param>
    /// <param name="parentHandle">The menu's parent window handle.</param>
    /// <returns>
    /// Returns Acad::eOk if the operation succeeds.
    /// Returns Acad::eInvalidInput if the operation fails
    /// </returns>
    ACCORE_PORT Acad::ErrorStatus numberingMenusInput(AcGePoint2d* menuPt, HWND parentHandle);
    /// <summary> 
    /// Invoke the text editor symbol menu.
    /// </summary>
    /// <param name="menuPt">The menu will display at this point. This point is in 
    /// screen coordinates. </param>
    /// <param name="parentHandle">The menu's parent window handle.</param>
    /// <returns>
    ///Returns Acad::eOk if the operation succeeds.
    ///Returns Acad::eInvalidInput if the operation fails
    /// </returns>
    ACCORE_PORT Acad::ErrorStatus symbolMenusInput(AcGePoint2d* menuPt, HWND parentHandle);
    /// <summary> 
    /// Invoke all the text editor context menu.
    /// </summary>
    /// <param name="menuPt">The menu will display at this point. This point is in 
    /// screen coordinates. </param>
    /// <param name="parentHandle">The menu's parent window handle.</param>
    /// <returns>
    /// Returns Acad::eOk if the operation succeeds.
    /// Returns Acad::eInvalidInput if the operation fails
    /// </returns>
    ACCORE_PORT Acad::ErrorStatus contextMenusInput(AcGePoint2d* menuPt, HWND parentHandle);

    /// <summary> 
    /// Invoke the text editor paragraph dialog.
    /// </summary>
    /// <returns>
    /// Returns Acad::eOk if the operation succeeds.
    /// Returns Acad::eInvalidInput if the operation fails
    /// </returns>
    ACCORE_PORT Acad::ErrorStatus invokeParagraphDialog();
    /// <summary> 
    /// Invoke the text editor wipe out dialog.
    /// </summary>
    /// <returns>
    /// Returns Acad::eOk if the operation succeeds.
    /// Returns Acad::eInvalidInput if the operation fails
    /// </returns>
    ACCORE_PORT Acad::ErrorStatus invokeWipeoutDialog();
    ///<summary> 
    /// Invoke the text editor columns setting dialog.
    ///</summary>
    /// <param name="iStaticColumnCount">Static column count.</param>
    /// <returns>
    /// Returns Acad::eOk if the operation succeeds.
    /// Returns Acad::eInvalidInput if the operation fails
    /// </returns>
    ACCORE_PORT Acad::ErrorStatus invokeColumnsDialog(int iStaticColumnCount = 0);
    /// <summary> 
    /// Invoke the text editor find and replace dialog.
    /// </summary>
    /// <returns>
    /// Returns Acad::eOk if the operation succeeds.
    /// Returns Acad::eInvalidInput if the operation fails
    /// </returns>
    ACCORE_PORT Acad::ErrorStatus invokeFindReplaceDialog();
    /// <summary> 
    /// Invoke the text editor import text dialog.
    /// </summary>
    /// <returns>
    /// Returns Acad::eOk if the operation succeeds.
    /// Returns Acad::eInvalidInput if the operation fails
    /// </returns>
    ACCORE_PORT Acad::ErrorStatus invokeImportTextDialog();
    /// <summary> 
    /// Invoke the text editor field dialog.
    /// </summary>
    /// <param name="pField">The field object you want to edit. If it is NULL, 
    /// it will invoke the insert field dialog.</param>
    /// <returns>
    /// Returns Acad::eOk if the operation succeeds.
    /// Returns Acad::eInvalidInput if the operation fails
    /// </returns>
    ACCORE_PORT Acad::ErrorStatus invokeFieldDialog(AcDbField* pField = NULL);
    /// <summary> 
    /// Invoke the text editor speller setting dialog.
    /// </summary>
    /// <returns>
    /// Returns Acad::eOk if the operation succeeds.
    /// Returns Acad::eInvalidInput if the operation fails
    /// </returns>
    ACCORE_PORT Acad::ErrorStatus invokeSpellSettingDialog();
    /// <summary> 
    /// Invoke the text editor speller dictionary dialog.
    /// </summary>
    /// <returns>
    /// Returns Acad::eOk if the operation succeeds.
    /// Returns Acad::eInvalidInput if the operation fails
    /// </returns>
    ACCORE_PORT Acad::ErrorStatus invokeSpellerDictionaryDialog();
    /// <summary> 
    /// Invoke the text editor text hight light color dialog.
    /// </summary>
    /// <returns>
    /// Returns Acad::eOk if the operation succeeds.
    /// Returns Acad::eInvalidInput if the operation fails
    /// </returns>
    ACCORE_PORT Acad::ErrorStatus invokeHightlightColorDialog();
    /// <summary> 
    /// Invoke the text editor help dialog.
    /// </summary>
    /// <returns>
    /// Returns Acad::eOk if the operation succeeds.
    /// Returns Acad::eInvalidInput if the operation fails
    /// </returns>
    ACCORE_PORT Acad::ErrorStatus invokeHelpDialog();
    /// <summary> 
    /// Invoke the text editor new feature work shop dialog.
    /// </summary>
    /// <returns>
    /// Returns Acad::eOk if the operation succeeds.
    /// Returns Acad::eInvalidInput if the operation fails
    /// </returns>
    ADESK_DEPRECATED ACCORE_PORT Acad::ErrorStatus invokeNewFeatureWorkshop();
    /// <summary> 
    /// Invoke the text editor stack properties dialog.
    /// </summary>
    /// <returns>
    /// Returns Acad::eOk if the operation succeeds.
    /// Returns Acad::eInvalidInput if the operation fails
    /// </returns>
    ACCORE_PORT Acad::ErrorStatus invokeStackPropertyDialog();
    /// <summary> 
    /// Change the text editor to static column type and set column count.
    /// Different with set column type and count directly to AcDbTextEditorColumns which is got from the editor,
    /// use this API will cause the text editor adjust the column width and gutter according to the defined width.
    /// </summary>
    /// <param name="columnCount">The new column count.</param>
    /// <returns>
    /// Returns Acad::eOk if the operation succeeds.
    /// Returns Acad::eInvalidInput if the operation fails
    /// </returns>
    ACCORE_PORT Acad::ErrorStatus setStaticColumnsWithCount(int columnCount);
protected:
    AcEdInplaceTextEditor();
    ~AcEdInplaceTextEditor();
    AcEdInplaceTextEditor(const AcEdInplaceTextEditor&);
    AcEdInplaceTextEditor& operator=(const AcEdInplaceTextEditor&);

protected:
   friend class AcEdInplaceTextEditorImp;
   AcEdInplaceTextEditorImp* m_pEditorImp;
   IPE_Editor*               m_pIPEEditorImp;
};

#endif //AcEdInplaceTextEditor_H
