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
#ifndef _ADUI_THEME_MANAGER_H_
#define _ADUI_THEME_MANAGER_H_


///<summary>Internal use only</summary>
class CAdUiThemeMgrReactor
{
public:
    CAdUiThemeMgrReactor();
    virtual void ThemeAdded(const CString & strThemeName) = 0;
    virtual void ThemeRemoved(const CString & strThemeName) = 0;
    virtual void SystemColorChanged() = 0;
    virtual ~CAdUiThemeMgrReactor();
};

/// <summary>
/// The theme manager manages all the UI themes used by the application.
/// The client code can query a theme using its name.
/// </summary>
/// <remarks>
/// Each CAdUiTheme instance maintains a reference count.  It must be correctly
/// adjusted using CAdUiThemeManager::ReleaseTheme() and CAdUiTheme::IncrementRefCount()
/// to ensure the theme has the desired lifetime.
/// </remarks>
class CAdUiThemeManager 
{
    friend class CAdUiThemeMgrReactor;

public:
    ///<summary>Internal use only</summary>
    CAdUiThemeManager();

    ///<summary>Internal use only</summary>
    ~CAdUiThemeManager();

    /// <summary>
    /// Gets a named theme 
    /// </summary>
    /// <param name="pThemeName">
    /// Name of a registered theme
    /// </param>
    /// <returns>
    /// Returns a pointer to the named theme. Retuns NULL if theme is not found.
    /// </returns>
    /// <remarks>
    /// A new theme can be created if the input name is unknown to the theme manager.
    ///
    /// The reference count of the returned theme is incremented by GetTheme().
    /// ReleaseTheme() should be called to decrement it when the theme is no 
    /// longer needed by the client code.
    /// </remarks>
    CAdUiTheme * GetTheme(const ACHAR *pThemeName);
    
    /// <summary>
    /// Releases a theme object by decreasing its reference count.
    /// The theme will be removed when its reference count reaches 0.
    /// </summary>
    /// <param name="pThemeName">
    /// Pointer to a CAdUiTheme instance
    /// </param>
    /// <returns>
    /// TRUE if the theme is successfully released or FALSE otherwise.
    /// </returns>
    /// <remarks>
    /// The reference count of the returned theme is incremented by GetTheme().
    /// ReleaseTheme() should be called to decrement it when the theme is no 
    /// longer needed by the client code.
    /// </remarks>
    BOOL ReleaseTheme(CAdUiTheme * pTheme);

    /// <summary>
    /// Indicates whether pThemeName is registerd with the Theme manager.
    /// </summary>
    /// <param name="pThemeName">
    //// Name of the theme to query
    /// </param>
    /// <returns>TRUE if pThemeName is registered, FALSE otherwise.</returns>
    BOOL HasTheme(const ACHAR *pThemeName) const;

    ///<summary>Internal use only</summary>
    void SystemColorChanged();

    ///<summary>Internal use only</summary>
    void ActiveThemeChanged();

private:
    int  RemoveTheme(const ACHAR *pThemeName);
    void Cleanup();
    int  GetThemeIndex(const ACHAR *pThemeName) const;
    int  GetThemeIndex(const CAdUiTheme *pTheme) const;
    BOOL RegisterThemeMgrReactor(CAdUiThemeMgrReactor * pReactor);
    BOOL UnregisterThemeMgrReactor(CAdUiThemeMgrReactor * pReactor);
    void NotifyThemeAddedReactors(const CString & strThemeName);
    void NotifySysColorReactors();
    CObArray        m_list;
    CTypedPtrArray<CPtrArray, CAdUiThemeMgrReactor*> m_arrayThemeMgrReactors;
};
#endif  // _ADUI_THEME_MANAGER_H_
