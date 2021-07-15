/***************************************************************
 * Name:      projectMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    Evren Kenanoglu ()
 * Created:   2021-07-15
 * Copyright: Evren Kenanoglu ()
 * License:
 **************************************************************/

#ifdef WX_PRECOMP
#include "wx_pch.h"
#endif

#ifdef __BORLANDC__
#pragma hdrstop
#endif //__BORLANDC__

#include "projectMain.h"

#include "include/RaspPiCLK.h"
#include "include/RaspPiGPIO.h"
#include "include/RaspPiI2C.h"
#include "include/RaspPiPWM.h"

//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__WXMAC__)
        wxbuild << _T("-Mac");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}

// BEGIN_EVENT_TABLE(MyFirstAppFrame, wxFrame)
// EVT_CLOSE(MyFirstAppFrame::OnClose)
// EVT_MENU(idMenuQuit, MyFirstAppFrame::OnQuit)
// EVT_MENU(idMenuAbout, MyFirstAppFrame::OnAbout)
// EVT_BUTTON(idButton0, MyFirstAppFrame::LED0)
// EVT_BUTTON(idButton1, MyFirstAppFrame::LED1)
// /* begin ************* 2021-06-15 */
// EVT_TIMER(idTimer0, MyFirstAppFrame::Timer0)
// EVT_TIMER(idTimer1, MyFirstAppFrame::Timer1)
// /* end   ************* 2021-06-15 */
// EVT_COMMAND_SCROLL_CHANGED(idSlider0, MyFirstAppFrame::Slider0)

// END_EVENT_TABLE()

projectFrame::projectFrame(wxFrame* frame, const wxString& title) : wxFrame(frame, -1, title, wxPoint(100, 100), wxSize(600, 800))
    : GUIFrame(frame)
{
#if wxUSE_MENUS
    // create a menu bar
    wxMenuBar* mbar     = new wxMenuBar();
    wxMenu*    fileMenu = new wxMenu(_T(""));
    fileMenu->Append(idMenuQuit, _("&Quit\tAlt-F4"), _("Quit the application"));
    mbar->Append(fileMenu, _("&File"));

    wxMenu* helpMenu = new wxMenu(_T(""));
    helpMenu->Append(idMenuAbout, _("&About\tF1"), _("Show info about this application"));
    mbar->Append(helpMenu, _("&Help"));

    SetMenuBar(mbar);
#endif // wxUSE_MENUS

#if wxUSE_STATUSBAR
    // create a status bar with some information about the used wxWidgets version
    CreateStatusBar(2);
    SetStatusText(_("Hello Code::Blocks user!"), 0);
    SetStatusText(wxbuildinfo(short_f), 1);
#endif // wxUSE_STATUSBAR


}



projectFrame::~projectFrame()
{
}

void projectFrame::OnClose(wxCloseEvent &event)
{
    Destroy();
}

void projectFrame::OnQuit(wxCommandEvent &event)
{
    Destroy();
}

void projectFrame::OnAbout(wxCommandEvent &event)
{
    wxString msg = wxbuildinfo(long_f);
    wxMessageBox(msg, _("Welcome to..."));
}
