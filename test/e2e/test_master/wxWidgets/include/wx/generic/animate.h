/////////////////////////////////////////////////////////////////////////////
// Name:        wx/generic/animate.h
// Purpose:     wxGenericAnimationCtrl
// Author:      Julian Smart and Guillermo Rodriguez Garcia
// Modified by: Francesco Montorsi
// Created:     13/8/99
// Copyright:   (c) Julian Smart and Guillermo Rodriguez Garcia
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////
#ifndef _WX_GENERIC_ANIMATEH__
#  define _WX_GENERIC_ANIMATEH__
#  include "wx/bitmap.h"
// ----------------------------------------------------------------------------
// wxGenericAnimationCtrl
// ----------------------------------------------------------------------------
class WXDLLIMPEXP_ADV wxGenericAnimationCtrl : public wxAnimationCtrlBase
{
public:
  wxGenericAnimationCtrl()
  {
 Init();   }
  wxGenericAnimationCtrl(wxWindow* parent, wxWindowID id, const wxAnimation& anim = wxNullAnimation, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxAC_DEFAULT_STYLE, const wxString& name = wxASCII_STR(wxAnimationCtrlNameStr))
  {

        Init();

        Create(parent, id, anim, pos, size, style, name);
      }
  void Init();
  bool Create(wxWindow* parent, wxWindowID id, const wxAnimation& anim = wxNullAnimation, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxAC_DEFAULT_STYLE, const wxString& name = wxASCII_STR(wxAnimationCtrlNameStr));
  ~wxGenericAnimationCtrl();
  bool LoadFile(const wxString& filename, wxAnimationType type = wxANIMATION_TYPE_ANY) override;
  bool Load(wxInputStream& stream, wxAnimationType type = wxANIMATION_TYPE_ANY) override;
  void Stop() override;
  bool Play() override
  { return Play(true /* looped */); }
  bool IsPlaying() const override
  { return m_isPlaying; }
  void SetAnimation(const wxAnimation& animation) override;
  void SetInactiveBitmap(const wxBitmap& bmp) override;
    // override base class method
  bool SetBackgroundColour(const wxColour& col) override;
  static wxAnimation CreateCompatibleAnimation();
  void OnPaint(wxPaintEvent& event);
  void OnTimer(wxTimerEvent& event);
  void OnSize(wxSizeEvent& event);
    // Specify whether the animation's background colour is to be shown (the default),
    // or whether the window background should show through
  void SetUseWindowBackgroundColour(bool useWinBackground = true)
  { m_useWinBackgroundColour = useWinBackground; }
  bool IsUsingWindowBackgroundColour() const
  { return m_useWinBackgroundColour; }
    // This overload of Play() lets you specify if the animation must loop or not
  bool Play(bool looped);
    // Draw the current frame of the animation into given DC.
    // This is fast as current frame is always cached.
  void DrawCurrentFrame(wxDC& dc);
    // Returns a wxBitmap with the current frame drawn in it
  wxBitmap& GetBackingStore()
  { return m_backingStore; }
protected:
  wxAnimationImpl* DoCreateAnimationImpl() const override;
    // resize this control to fit m_animation
  void FitToAnimation();
    // Draw the background; use this when e.g. previous frame had wxANIM_TOBACKGROUND disposal.
  void DisposeToBackground();
  void DisposeToBackground(wxDC& dc);
  void DisposeToBackground(wxDC& dc, const wxPoint& pos, const wxSize& sz);
  void IncrementalUpdateBackingStore();
  bool RebuildBackingStoreUpToFrame(unsigned int);
  void DrawFrame(wxDC& dc, unsigned int);
  void DisplayStaticImage() override;
  wxSize DoGetBestSize() const override;
    // Helpers to safely access methods in the wxAnimationGenericImpl that are
    // specific to the generic implementation
  wxPoint AnimationImplGetFramePosition(unsigned int frame) const;
  wxSize AnimationImplGetFrameSize(unsigned int frame) const;
  wxAnimationDisposal AnimationImplGetDisposalMethod(unsigned int frame) const;
  wxColour AnimationImplGetTransparentColour(unsigned int frame) const;
  wxColour AnimationImplGetBackgroundColour() const;
  unsigned int m_currentFrame;
  bool m_looped;
  wxTimer m_timer;
  bool m_isPlaying;
  bool m_useWinBackgroundColour;
  wxBitmap m_backingStore;
                                      // on the screen
private:
  typedef wxAnimationCtrlBase base_type;
  wxDECLARE_DYNAMIC_CLASS(wxGenericAnimationCtrl);
  wxDECLARE_EVENT_TABLE();
};
#endif
