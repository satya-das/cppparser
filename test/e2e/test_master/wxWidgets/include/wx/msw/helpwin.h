/////////////////////////////////////////////////////////////////////////////
// Name:        wx/msw/helpwin.h
// Purpose:     Help system: WinHelp implementation
// Author:      Julian Smart
// Modified by:
// Created:     04/01/98
// Copyright:   (c) Julian Smart
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////
#ifndef _WX_HELPWIN_H_
#  define _WX_HELPWIN_H_
#  include "wx/wx.h"
#  if  wxUSE_HELP
#    include "wx/helpbase.h"
class WXDLLIMPEXP_CORE wxWinHelpController : public wxHelpControllerBase
{
  wxDECLARE_DYNAMIC_CLASS(wxWinHelpController);
public:
  wxWinHelpController(wxWindow* parentWindow = NULL)
    : wxHelpControllerBase(parentWindow)
  {
  }
  virtual ~wxWinHelpController()
  {
  }
    // Must call this to set the filename
  bool Initialize(const wxString& file) override;
  bool Initialize(const wxString& file, int) override
  {
    return Initialize(file);
  }
    // If file is "", reloads file given in Initialize
  bool LoadFile(const wxString& file = wxEmptyString) override;
  bool DisplayContents() override;
  bool DisplaySection(int sectionNo) override;
  bool DisplaySection(const wxString& section) override
  {
    return KeywordSearch(section);
  }
  bool DisplayBlock(long blockNo) override;
  bool DisplayContextPopup(int contextId) override;
  bool KeywordSearch(const wxString& k, wxHelpSearchMode mode = wxHELP_SEARCH_ALL) override;
  bool Quit() override;
  inline wxString GetHelpFile() const
  {
    return m_helpFile;
  }
protected:
    // Append extension if necessary.
  wxString GetValidFilename(const wxString& file) const;
private:
  wxString m_helpFile;
};
#  endif
#endif
// _WX_HELPWIN_H_
