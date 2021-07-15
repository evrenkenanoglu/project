/***************************************************************
 * Name:      projectMain.h
 * Purpose:   Defines Application Frame
 * Author:    Evren Kenanoglu ()
 * Created:   2021-07-15
 * Copyright: Evren Kenanoglu ()
 * License:
 **************************************************************/

#ifndef PROJECTMAIN_H
#define PROJECTMAIN_H



#include "projectApp.h"


#include "GUIFrame.h"

class projectFrame: public GUIFrame
{
    public:
        projectFrame(wxFrame *frame);
        ~projectFrame();
    private:
        virtual void OnClose(wxCloseEvent& event);
        virtual void OnQuit(wxCommandEvent& event);
        virtual void OnAbout(wxCommandEvent& event);
};

#endif // PROJECTMAIN_H
