/////////////////////////////////////////////////////////////////////////////
// Name:        wx/osx/cocoa/stdpaths.h
// Purpose:     wxStandardPaths for Cocoa
// Author:      Tobias Taschner
// Created:     2015-09-09
// Copyright:   (c) 2015 wxWidgets development team
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////
#ifndef _WX_COCOA_STDPATHS_H_
#  define _WX_COCOA_STDPATHS_H_
// ----------------------------------------------------------------------------
// wxStandardPaths
// ----------------------------------------------------------------------------
class WXDLLIMPEXP_BASE wxStandardPaths : public wxStandardPathsBase
{
public:
  virtual ~wxStandardPaths();
    // implement base class pure virtuals
  wxString GetExecutablePath() const override;
  wxString GetConfigDir() const override;
  wxString GetUserConfigDir() const override;
  wxString GetDataDir() const override;
  wxString GetLocalDataDir() const override;
  wxString GetUserDataDir() const override;
  wxString GetPluginsDir() const override;
  wxString GetResourcesDir() const override;
  wxString GetLocalizedResourcesDir(const wxString& lang, ResourceCat category = ResourceCat_None) const override;
  wxString GetUserDir(Dir userDir) const override;
  wxString MakeConfigFileName(const wxString& basename, ConfigFileConv conv = ConfigFileConv_Ext) const override;
protected:
    // Ctor is protected, use wxStandardPaths::Get() instead of instantiating
    // objects of this class directly.
  wxStandardPaths();
};
#endif
