///////////////////////////////////////////////////////////////////////////////
// Name:        wx/gtk/private/gtk3-compat.h
// Purpose:     Compatibility code for older GTK+ 3 versions
// Author:      Paul Cornett
// Created:     2015-10-10
// Copyright:   (c) 2015 Paul Cornett
// Licence:     wxWindows licence
///////////////////////////////////////////////////////////////////////////////
#ifndef _WX_GTK_PRIVATE_COMPAT3_H_
#  define _WX_GTK_PRIVATE_COMPAT3_H_
#  ifndef __WXGTK4__
// ----------------------------------------------------------------------------
// the following were introduced in GTK+ 3.20
static gboolean wx_gtk_text_iter_starts_tag(const GtkTextIter* iter, GtkTextTag* tag)
{
  return gtk_text_iter_begins_tag(iter, tag);
}
#    define gtk_text_iter_starts_tag	wx_gtk_text_iter_starts_tag
#    ifdef __WXGTK3__
// ----------------------------------------------------------------------------
// the following were introduced in GTK+ 3.12
static void wx_gtk_widget_set_margin_start(GtkWidget* widget, gint margin)
{
  gtk_widget_set_margin_left(widget, margin);
}
#      define gtk_widget_set_margin_start	wx_gtk_widget_set_margin_start
static void wx_gtk_widget_set_margin_end(GtkWidget* widget, gint margin)
{
  gtk_widget_set_margin_right(widget, margin);
}
#      define gtk_widget_set_margin_end	wx_gtk_widget_set_margin_end
#    endif
#  endif
#  if  defined(__WXGTK4__) || !defined(__WXGTK3__)
static bool wx_is_at_least_gtk3(int)
{
#    ifdef __WXGTK4__
  return true;
#    else 
  return false;
#    endif
}
#  else 
static bool wx_is_at_least_gtk3(int minor)
{
  return gtk_check_version(3, minor, 0) == NULL;
}
#  endif
#endif
