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


    wxString TmpStrg;

    ColourButtonOFF = new wxColour(0, 150, 0);
    ColourButtonON  = new wxColour(255, 0, 0);

    ColourRGB_OFF = new wxColour(150 << 8);

    wxPanel* myPanel = new wxPanel(this, wxID_ANY);

    myButton0 = new wxButton(myPanel, idButton0, wxT("LED0"), wxPoint(20, 20), wxSize(80, 40));
    myButton1 = new wxButton(myPanel, idButton1, wxT("LED1"), wxPoint(20, 70), wxSize(80, 40));

    // // first to low level then to output -> avoid spikes
    // myFirstGPIO->GPIO_Clr(12);
    // myButton0->SetBackgroundColour(ColourButtonOFF->GetAsString());
    // myFirstGPIO->GPIO_SetStdOutput(12);

    // myFirstGPIO->GPIO_Clr(14);
    // myButton1->SetBackgroundColour(ColourButtonOFF->GetAsString());
    // myFirstGPIO->GPIO_SetStdOutput(14);

    // // PWM0_0
    // myFirstGPIO->GPIO_Clr(18);
    // myFirstGPIO->GPIO_SetAltOutput(18, 5);

    // // I2C
    // myFirstGPIO->GPIO_SetAltOutput(0, 0);
    // myFirstGPIO->GPIO_SetResistor(0, NORESISTOR);

    // myFirstGPIO->GPIO_SetAltOutput(1, 0);
    // myFirstGPIO->GPIO_SetResistor(1, NORESISTOR);

    // myFirstI2C->I2C_Enable();

    myPanel0 = new wxPanel(myPanel, idPanel0, wxPoint(120, 20), wxSize(80, 40));
    myPanel0->SetBackgroundColour(ColourButtonOFF->GetAsString());

    myPanel1 = new wxPanel(myPanel, idPanel1, wxPoint(120, 70), wxSize(80, 40));
    myPanel1->SetBackgroundColour(ColourButtonOFF->GetAsString());

    // timer_create_start();

    mySlider0 = new wxSlider(myPanel, idSlider0, 127, 0, 255, wxPoint(20, 140), wxSize(200, 80), wxSL_HORIZONTAL | wxSL_VALUE_LABEL | wxSL_AUTOTICKS | wxSL_MIN_MAX_LABELS);

    myStaticText0 = new wxStaticText(myPanel, idStaticText0, wxT(""), wxPoint(20, 350), wxSize(250, 30));
    myStaticText1 = new wxStaticText(myPanel, idStaticText1, wxT(""), wxPoint(20, 400), wxSize(250, 30));
    myStaticText2 = new wxStaticText(myPanel, idStaticText2, wxT(""), wxPoint(20, 450), wxSize(250, 30));
    myStaticText3 = new wxStaticText(myPanel, idStaticText3, wxT(""), wxPoint(20, 500), wxSize(250, 30));
    myStaticText4 = new wxStaticText(myPanel, idStaticText4, wxT(""), wxPoint(20, 550), wxSize(250, 30));
    myStaticText5 = new wxStaticText(myPanel, idStaticText5, wxT(""), wxPoint(20, 600), wxSize(250, 30));

    myTextCtrl0 = new wxTextCtrl(myPanel, idTextCtrl0, wxT(""), wxPoint(300, 20), wxSize(250, 30), wxTE_READONLY);

    // myFirstCLK->PWMCLK_Stop();
    // myFirstCLK->PWMCLK_SetDivisor(52);

    // myFirstPWM->PWM_SetMode(0, PWMMODE, MSTRANS);
    // myFirstPWM->PWM_SetRng(0, 1024);
    // myFirstPWM->PWM_SetData(0, 512);
    // myFirstPWM->PWM_Enable_Channel(0);

    // myFirstCLK->PWMCLK_Start();

    // PWM_Start(5000, 33.3, 10, MSTRANS);

    myStaticText0->SetLabel(wxString::Format("TEST %08X", (uint) * (myFirstCLK->clkio + PWMCLK_CNTL)));
    myStaticText1->SetLabel(wxString::Format("TEST %08X", (uint) * (myFirstCLK->clkio + PWMCLK_DIV)));
    myStaticText2->SetLabel(wxString::Format("TEST %08X", (uint) * (myFirstPWM->pwmio + PWM_CTL)));
    myStaticText3->SetLabel(wxString::Format("TEST %08X", (uint) * (myFirstPWM->pwmio + PWM_RNG1)));
    myStaticText4->SetLabel(wxString::Format("TEST %08X", (uint) * (myFirstPWM->pwmio + PWM_DAT1)));
    myStaticText5->SetLabel(wxString::Format("TEST %08X", (uint) * (myFirstGPIO->gpio + GPFSEL1)));

    
}

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
