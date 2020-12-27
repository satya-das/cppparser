///////////////////////////////////////////////////////////////////////////////
// Name:        wx/msw/regconf.h
// Purpose:     Registry based implementation of wxConfigBase
// Author:      Vadim Zeitlin
// Modified by:
// Created:     27.04.98
// Copyright:   (c) 1998 Vadim Zeitlin <zeitlin@dptmaths.ens-cachan.fr>
// Licence:     wxWindows licence
///////////////////////////////////////////////////////////////////////////////
#ifndef _WX_MSW_REGCONF_H_
#  define _WX_MSW_REGCONF_H_
#  include "wx/defs.h"
#  if  wxUSE_CONFIG && wxUSE_REGKEY
#    include "wx/msw/registry.h"
#    include "wx/object.h"
#    include "wx/confbase.h"
#    include "wx/buffer.h"
// ----------------------------------------------------------------------------
// wxRegConfig
// ----------------------------------------------------------------------------
class WXDLLIMPEXP_BASE wxRegConfig : public wxConfigBase
{
public:
  // ctor & dtor
    // will store data in HKLM\appName and HKCU\appName
  wxRegConfig(const wxString& appName = wxEmptyString, const wxString& vendorName = wxEmptyString, const wxString& localFilename = wxEmptyString, const wxString& globalFilename = wxEmptyString, long style = wxCONFIG_USE_GLOBAL_FILE);
    // dtor will save unsaved data
  virtual ~wxRegConfig()
  {
  }
  // implement inherited pure virtual functions
  // ------------------------------------------

  // path management
  void SetPath(const wxString& strPath) override;
  const wxString& GetPath() const override
  { return m_strPath; }
  // entry/subgroup info
    // enumerate all of them
  bool GetFirstGroup(wxString& str, long& lIndex) const override;
  bool GetNextGroup(wxString& str, long& lIndex) const override;
  bool GetFirstEntry(wxString& str, long& lIndex) const override;
  bool GetNextEntry(wxString& str, long& lIndex) const override;
    // tests for existence
  bool HasGroup(const wxString& strName) const override;
  bool HasEntry(const wxString& strName) const override;
  EntryType GetEntryType(const wxString& name) const override;
    // get number of entries/subgroups in the current group, with or without
    // it's subgroups
  size_t GetNumberOfEntries(bool bRecursive = false) const override;
  size_t GetNumberOfGroups(bool bRecursive = false) const override;
  bool Flush(bool = false) override
  { return true; }
  // rename
  bool RenameEntry(const wxString& oldName, const wxString& newName) override;
  bool RenameGroup(const wxString& oldName, const wxString& newName) override;
  // delete
  bool DeleteEntry(const wxString& key, bool bGroupIfEmptyAlso = true) override;
  bool DeleteGroup(const wxString& key) override;
  bool DeleteAll() override;
protected:
  // opens the local key creating it if necessary and returns it
  wxRegKey& LocalKey() const
  {
    wxRegConfig* self = wxConstCast(this, wxRegConfig);
    if (!m_keyLocal.IsOpened())
    {

          // create on demand
          self->m_keyLocal.Create();
          }
    return self->m_keyLocal;
  }
  // implement read/write methods
  bool DoReadString(const wxString& key, wxString* pStr) const override;
  bool DoReadLong(const wxString& key, long* plResult) const override;
#    if  wxUSE_BASE64
  bool DoReadBinary(const wxString& key, wxMemoryBuffer* buf) const override;
#    endif
  bool DoWriteString(const wxString& key, const wxString& szValue) override;
  bool DoWriteLong(const wxString& key, long lValue) override;
#    if  wxUSE_BASE64
  bool DoWriteBinary(const wxString& key, const wxMemoryBuffer& buf) override;
#    endif
private:
  // these keys are opened during all lifetime of wxRegConfig object
  wxRegKey m_keyLocalRoot, m_keyLocal, m_keyGlobalRoot, m_keyGlobal;
  // current path (not '/' terminated)
  wxString m_strPath;
  wxDECLARE_NO_COPY_CLASS(wxRegConfig);
  wxDECLARE_ABSTRACT_CLASS(wxRegConfig);
};
#  endif
#endif
