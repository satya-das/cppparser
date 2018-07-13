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
// DESCRIPTION:
// Public interface to the AutoCAD independent file navigation dialog.
/////////////////////////////////////////////////////////////////////////////

#ifndef _ANavDialog_h
#define _ANavDialog_h

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Find File Dialog Help Message
#define WM_FILEDLG_FINDFILEHELP (WM_USER + 37)

// The following enum defines error codes used by OK handler functions.
enum OkHandlerErr
{
    NAV_OKHANDLER_SUCCESS = 0,      // All went well. Continue preocessing.
    NAV_OKHANDLER_NONFILESYSTEM,    // Trying to save or open a nonfilesystem location.
    NAV_OKHANDLER_FAILURE,          // General failure.
    NAV_OKHANDLER_TOOLONG           // Detail failure: name plus path is too long.
};

// Tools menu items.
enum NavToolsMenuItem
{
    NAV_TOOLS_ITEM_FIND = 0x1,
    NAV_TOOLS_ITEM_LOCATE = 0x2,
    NAV_TOOLS_ITEM_FTPMODIFY = 0x4,
    NAV_TOOLS_ITEM_SIMPLESTORAGE = 0x8,
    NAV_TOOLS_ITEM_ADDCURRENT = 0x10,
    NAV_TOOLS_ITEM_ADDFAVORITES = 0x20
};

// Action code bits for remote file transfer.
enum NavInetTransferActions
{	
   NAV_INET_IGNORE_CACHE = 0x1,         // Always doenload file from remote location.
   NAV_INET_STOP_ON_ERROR = 0x2,        // Stop downloading files on the first error.
   NAV_INET_KEEP_CACHE 	= 0x4           // Do not remove a downloaded file from the cache on exit.
};

/////////////////////////////////////////////////////////////////////////////
// File Navigation dialog

class ANAV_PORT CNavDialog : public CAdUiDialog {
    friend class CNavDialogImp;
    DECLARE_DYNAMIC(CNavDialog)

public:

    // The constructor for the dialog. 'dataArray' is used for return information. 'filterArray' holds
    // the files of type information that the dialog uses for initialization of the files of type combobox.
    // Note that if the template ID, 'idd', is 0 then a default resource template is used. If a template ID
    // is supplied it must be found in 'hDialogResource'.
    CNavDialog(
        CNavDataArray& dataArray,
        CNavFilterArray& filterArray,
        UINT idd=0,
        CWnd *pParent=NULL,
        HINSTANCE hDialogResource=NULL
    );
    virtual ~CNavDialog();
    
    // Default dialog resource id.
    enum { IDD = 0 };

    // Get the data array supplied in construction.
    CNavDataArray& GetDataArray();

    // Get the filter array supplied in construction.
    CNavFilterArray& GetFilterArray();

    // Get/set the dialog caption. Set this at dialog initialization.    
    LPCTSTR GetDialogCaption();
    void    SetDialogCaption(LPCTSTR caption);

    // Get/set the default file extension.
    // This is used when an initial filename is set without an extension.    
    LPCTSTR GetDefaultFileExtension();
    void    SetDefaultFileExtension(LPCTSTR ext);

    // Get/set the 0 based filter index.
    int     GetFilterIndex();
    void    SetFilterIndex(int index);

    // Get/set the 0 based default filter index. This is used if no index is found
    // in dialog persistent data.
    int     GetDefaultFilterIndex();
    void    SetDefaultFilterIndex(int index);

    // Get the initial filter index that will be used in the dialog. If it has been forced to a
    // value then that value is returned. If not then the value in persistent dialog data is
    // retrieved, if none found then the default filter index is returned.
    DWORD   GetInitialFilterIndex();

    // Get/set the 0 based filter index whose use will be forced during dialog initialization.
    // This index will override all others including any index stored in persistent dialog
    // data in the registry.
    int     GetForceFilterIndex();        
    void    SetForceFilterIndex(int index);

    // Get/set the initial folder name whose use will be forced during dialog initialization.
    // This folder will override any other including any folder stored in persistent
    // dialog data. However, the folder must exist.
    LPCTSTR GetForceInitialFolder();        
    void    SetForceInitialFolder(LPCTSTR folder);

    // Set the default initial folder.
    void    SetDefaultInitialFolder(LPCTSTR folder);
    LPCTSTR GetDefaultInitialFolder();

    // Get/set the initial file name. This is used to initialize the filename combobox.
    // If it is set without an extension the default filename extension, if set, is appended.
    // If there is no default filename extension the first extension in the current file filter
    // is used.
    LPCTSTR GetInitialFileName();
    void    SetInitialFileName(LPCTSTR name);

    // Get/set the flag to use to check registry overrides for extensions. Some applications
    // can turn on and off file navigation extensions by setting certain registry settings.
    // These functions determine if these registry settings are examined during dialog
    // initialization.
    BOOL    GetUseRegExtensionFlags();               
    void    SetUseRegExtensionFlags(BOOL bUse);

    // Get/set the confirm replace flag. This flag is used to determine whether to
    // warn the user, when creating(saving) a file, that an existing file will be replaced.
    BOOL    GetConfirmReplace();
    void    SetConfirmReplace(BOOL confirm);

    // Get/set the accept any extension flag. THis flag is used when the user enters
    // a filename with an extension that is not in the filename filter list.
    BOOL    GetAcceptAnyFileExtension();
    void    SetAcceptAnyFileExtension(BOOL any);

    // Get/set the no URL transfer flag. If this flag is TRUE no remote files are downloaded
    // and the URL is returned.
    BOOL    GetNoURLFileTransfer();
    void    SetNoURLFileTransfer(BOOL noTransfer);

    // Get/set the no URLs allowed at all flag. If TRUE no URL based extensions, including the FTP extension,
    // are visible in the folders combobox or the places list.
    BOOL    GetNoURLsAllowed();
    void    SetNoURLsAllowed(BOOL noURLs);

    // Get/set the view mode for the list control.
    UINT    GetViewMode();
    void    SetViewMode(UINT viewMode);

    // Get/set multiple selection allowed in the list control.
    BOOL    GetMultiSelectAllowed();
    void    SetMultiSelectAllowed(BOOL allow);

    // Get/set enabling the read-only ok button menu item.
    BOOL    GetReadOnlyAllowed();
    void    SetReadOnlyAllowed(BOOL allow);

    // Get/set the read-only ok button menu item is hidden flag.
    BOOL    GetReadOnlyHidden();
    void    SetReadOnlyHidden(BOOL hidden);

    // Get/set the read-only is specified flag. Called after the dialog is dismissed
    // to determine if the user chose read only commit.
    BOOL    GetReadOnlySpecified();
    void    SetReadOnlySpecified(BOOL readOnly);

    // Get/set the creating file flag. This is set on a save operation.
    BOOL    GetCreatingFile();
    void    SetCreatingFile(BOOL create);

    // Get/set whether a standard tools menu item is present. It used the
    // NavToolsMenuItem enum.
    UINT    GetToolsMenuItemsPresent();
    void    SetToolsMenuItemsPresent(UINT flag);

    // Get/set whether any FTP items are present or not in the folder combo and
    // the places list.
    BOOL    GetNoFTP();
    void    SetNoFTP(BOOL noFTP);

    // Get/set whether extra extensions are present or not in the dialog.
    // Extra extensions are those other than FTP.
    BOOL    GetNoExtraExtensions();
    void    SetNoExtraExtensions(BOOL noExtraExtensions);

    // Get/set whether extra extensions are present in the places list.
    // Extra extensions are those other than FTP.    
    BOOL    GetNoExtraExtensionsInPlaces();
    void    SetNoExtraExtensionsInPlaces(BOOL noExtraExtensions);

    // Get/set the folders only mode flag for the dialog. In folders only mode
    // only folders are displayed in the list control and only a folders are returned.
    BOOL    GetFoldersOnly();
    void    SetFoldersOnly(BOOL foldersOnly);

    // Get the no places list flag. If TRUE no places list is visible. THis may be set
    // to TRUE by the OS.
    BOOL    GetNoPlacesList();

    // Get the flag that tells us that the user has customized the places list.
    BOOL    IsPlacesListCustomized();

    // Use the following to subclass the list control.
    void    SetFolderListCtrl(CNavListCtrl* folderListCtrl);

    // Return the list control.
    CNavListCtrl* GetFolderListCtrl();

    // Move an existing item from one location in the list to the next
    int     MovePlacesItem(int fromLocation, int toLocation);
    
    // Return the resource id for this dialog.
    UINT    GetIDD();

    // Set/Get text for commit(ok) button (ie &Save, OK). For the Get
    // the argument determines whether the '&' is stripped before
    // returning the string.
    void    SetOkButtonText(LPCTSTR text);
    void    GetOkButtonText(CString& strOk, BOOL bIncludeAccel = TRUE);

    // Determines if the commit(ok) button has an associated menu. If creating(saving) a
    // file the dialog initialization calls this with FALSE. If a menu is desired
    // when creating a file this function must be called AFTER base class initialization.
    void    SetOkButtonMenuExists(BOOL bExists);
    
    // Add obtained data to history shortcuts.
    void    AddDataToHistory();

    // Get the current filter and find the first file extension string (ie. "*.dwg").
    CNavFilter* GetCurrentFileExtension(CString& strExt);

    // Set the current folder combo selection by index.
    void SetFolderComboCurSel(int i);

    // Return the 0 based position of a tools menu item.
    int GetToolsMenuItemPosition(NavToolsMenuItem itemFlag);

    // Return in the argument the full path to the CSIDL_PERSONAL folder.
    BOOL GetPersonalFolderPath(CString& strPersonal);

    // Browse a folder in the dialog.
    BOOL NavigateToFolder(LPCTSTR sFolder);

    // Get the name of the current folder for use in the next invocation of this dialog.
    void GetCurrentFolderForPersistence(CString& strFolder);

    // If a single CNavData is in the data array, deteremine the full path that would
    // be returned on an OK and put it in the argument. If one single data object is
    // not in the array then return an empty string in the argument.
    void GetSingleDataFullPath(CString& strFullPath);

    // Trim leading and trailing white space from the string. Trim only LEADING
    // space off any file basename unless 'bAll' is TRUE.
    void TrimWhiteSpace(CString& strName, BOOL bAll);
    
    // Refresh the file and folder list control for the current item being browsed
    // by refilling the list control.
    void BrowseCurrentObject();

    // Insert a user item in the places list if not there already.
    int InsertUserItemInPlaces(int index, LPCTSTR sFullPath, LPCTSTR sText);
    
    // Return the implementation object.
    void* GetImpObject() const;
    
    // For Set/get of persistent data for ALL file navigation dialogs.
    virtual BOOL SetAllDialogsData(const CString& cValueName, CString& cValue);
    virtual BOOL SetAllDialogsData(const CString& cValueName, DWORD dwValue);
    virtual BOOL GetAllDialogsData(const CString& cValueName, CString& cValue);
    virtual BOOL GetAllDialogsData(const CString& cValueName, DWORD& data);

    // Perform a locate on the file name in the file name conbobox. If the file is found in
    // the locate search path the folder being browsed changes to the folder where the file was found.
    virtual void LocateFile();

    // Return the product name to be used when registering extensions.
    virtual BOOL GetProductName(CString& strProduct);

    // Called at the start of a remote file download operation.        
    virtual BOOL BeginDownloadFiles(CStringArray& strURLs, CDWordArray& dwActionCodes);

    // Callback to get additional action code bits for a remote download right before the download takes place.    
    virtual DWORD GetDownloadActionCodes(CString& strURL);

    // Called when a help button is selected or F1 is entered. Override this function to
    // supply your own help file.
    virtual void OnDialogHelp();
    virtual void OnDialogHelp(LPCTSTR pHelpTag);    

protected:

    // Dialog initialization.
    virtual BOOL OnInitDialog();

    // Pretranslate message.
    virtual BOOL PreTranslateMessage(MSG* pMsg);

    // DDX/DDV support    
    virtual void DoDataExchange(CDataExchange* pDX);

    // Possibly alter the base ok menu before it is displayed.
    virtual void PrepareOkMenu(CMenu* pMenu);

    // Possibly alter the base tools menu before it is displayed.
    virtual void PrepareToolsMenu(CMenu* pMenu);

    // Possibly alter the base views menu before it is displayed.
    virtual void PrepareViewsMenu(CMenu* pMenu);

    // Cancel handler.
    virtual void OnCancel();
    
    // Start of the OK hanler.
    virtual void OnOK();

    // Called as part of the OK handler.    
    virtual OkHandlerErr PreprocessData(CNavDataArray& array);

    // Called as part of the OK handler.    
    virtual OkHandlerErr CombineDataTextWithFolderName(CNavData* data, CString& strResult);

    // During ok handling add or correct any file extension.    
    virtual BOOL UpdateFileExtension(CString& strName, BOOL bCanUseCurrentExtension);

    // Called as part of the OK handler.
    virtual BOOL OnFileNameOK();

    // During ok handling for a URL based file, if we're in file creation mode(saving)
    // and the file exists on the site, notify the user.
    virtual BOOL    VerifyURLSave();
    
    // Called as part of the OK handler.
    // Called when the commit button is clicked and a URL is detected.
    // Return TRUE to continue the dialog OK procedure, FALSE to leave the dialog up.
    virtual BOOL OnUrlOK();

    // Report errors on downloading remote files.
    virtual BOOL ReportURLTransferStatus(CDWordArray& dwErrorArray, CStringArray& strURLs, CStringArray& strLocals);
    
    // Get the "Recent" directory under the "Application Data"
    // directory of the OS. Typically this would be something like
    // "c:\Winnt\Profiles\jackl\Application Data\Autodesk\AutoCAD\Recent"
    // The path down to Application Data is supplied by the OS. 
    // Meant to be overridden in a descendant.
    virtual BOOL GetRecentDirectory(CString& strRecent);

    // Locate a file in a search path.
    virtual BOOL FindInSearchPath(LPCTSTR sBase, CString* pFullPath);

    // Display an error in trying to locate a file in the search path.
    virtual void DisplaySearchError(LPCTSTR sBase);

    // Get the default URL to use in the web button's web browser.
    virtual void GetDefaultBrowserStartURL(CString& strStartPage);

    // Launch a browser and get a URL.
    virtual BOOL LaunchBrowserDialog(CString& strSelectedURL, LPCTSTR strDialogCaption,
                                     LPCTSTR strOk, LPCTSTR strStartPage);

    // Called when checking for errors after downloading files.
    virtual void OnURLDownloadSuccess(CString& strURL);
    
    // Called when a Locate is requested.
    virtual void OnDoLocate();

    // Called when a Find is requested.    
    virtual void OnDoFind();

    // Called when AddItem(s)to Favorites is requested.    
    virtual void OnDoAddToFavorites(BOOL bOneItem);

    // Refresh the list control by calling the Refresh function of the
    // IShellView interface for the file and folder list.
    virtual void Refresh();

    // Called when the file name changes.
    virtual void OnFileNameChange();

    // Called when the selection changes in the filename combo.    
    virtual void OnFileNameSelectionChange();

    // Called when the filter (files of type) changes.
    virtual void OnFilterChange();

    // Called when the selection changes in the list control.
    virtual void OnFolderItemChange();

    // Called when the folder being browsed changes.
    virtual void OnFolderChange();

    // Called to possibly update the state of dialog controls.
    virtual void UpdateUIState();

    // Called to possibly update based on the selection change
    virtual void OnPlacesChanged();

    // AdUi message handlers
    virtual ADUI_REPLY OnNotifyControlChange(UINT controlId, LPARAM lParam);
    virtual ADUI_REPLY OnNotifyGeneric(UINT controlId, LPARAM lParam);

    // Called on command messages.
    virtual BOOL OnCmdMsg( UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo );

    //{{AFX_MSG(CNavDialog)
    // These methods may be called directly from classes derived from CNavDialog
    afx_msg void OnDestroy();
    afx_msg void OnContextMenu(CWnd*, CPoint);
    afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
    afx_msg void OnKickIdle();
    afx_msg void OnSysColorChange();    

private:
    afx_msg LRESULT OnWmGetIShellBrowser (WPARAM wp, LPARAM lp);
    afx_msg LRESULT OnWmDeviceChange     (WPARAM wp, LPARAM lp);
    //}}AFX_MSG

    DECLARE_MESSAGE_MAP()

    // The implementation object.            
    void* m_navImp;            
};
#endif
