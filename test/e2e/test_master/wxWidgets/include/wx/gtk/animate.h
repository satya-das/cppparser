/////////////////////////////////////////////////////////////////////////////
// Name:        wx/gtk/animate.h
// Purpose:     Animation classes
// Author:      Julian Smart and Guillermo Rodriguez Garcia
// Modified by: Francesco Montorsi
// Created:     13/8/99
// Copyright:   (c) Julian Smart and Guillermo Rodriguez Garcia
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////
#ifndef _WX_GTKANIMATEH__
#  define _WX_GTKANIMATEH__
typedef struct _GdkPixbufAnimation GdkPixbufAnimation;
typedef struct _GdkPixbufAnimationIter GdkPixbufAnimationIter;
// ----------------------------------------------------------------------------
// wxAnimationCtrl
// ----------------------------------------------------------------------------

// Resize to animation size if this is set
#  define wxAN_FIT_ANIMATION	0x0010
class WXDLLIMPEXP_ADV wxAnimationCtrl : public wxAnimationCtrlBase
{
public:
  wxAnimationCtrl()
  {
    Init();
  }
  wxAnimationCtrl(wxWindow* parent, wxWindowID id, const wxAnimation& anim = wxNullAnimation, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxAC_DEFAULT_STYLE, const wxString& name = wxASCII_STR(wxAnimationCtrlNameStr))
  {
    Init();
    Create(parent, id, anim, pos, size, style, name);
  }
  bool Create(wxWindow* parent, wxWindowID id, const wxAnimation& anim = wxNullAnimation, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxAC_DEFAULT_STYLE, const wxString& name = wxASCII_STR(wxAnimationCtrlNameStr));
  ~wxAnimationCtrl();
  void OnTimer(wxTimerEvent&);
  bool LoadFile(const wxString& filename, wxAnimationType type = wxANIMATION_TYPE_ANY) override;
  bool Load(wxInputStream& stream, wxAnimationType type = wxANIMATION_TYPE_ANY) override;
  void SetAnimation(const wxAnimation& anim) override;
  bool Play() override;
  void Stop() override;
  bool IsPlaying() const override;
  bool SetBackgroundColour(const wxColour& colour) override;
  static wxAnimation CreateCompatibleAnimation();
protected:
  wxAnimationImpl* DoCreateAnimationImpl() const override;
  void DisplayStaticImage() override;
  wxSize DoGetBestSize() const override;
  void FitToAnimation();
  void ClearToBackgroundColour();
  void ResetAnim();
  void ResetIter();
    // Helpers to safely access methods in the wxAnimationGTKImpl that are
    // specific to the gtk implementation
  GdkPixbufAnimation* AnimationImplGetPixbuf() const;
  void AnimationImplSetPixbuf(GdkPixbufAnimation* p);
  GdkPixbufAnimation* m_anim;
  GdkPixbufAnimationIter* m_iter;
  wxTimer m_timer;
  bool m_bPlaying;
private:
  typedef wxAnimationCtrlBase base_type;
  void Init();
  wxDECLARE_DYNAMIC_CLASS(wxAnimationCtrl);
  wxDECLARE_EVENT_TABLE();
};
#endif
