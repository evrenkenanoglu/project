/***************************************************************
 * Name:      projectApp.h
 * Purpose:   Defines Application Class
 * Author:    Evren Kenanoglu ()
 * Created:   2021-07-15
 * Copyright: Evren Kenanoglu ()
 * License:
 **************************************************************/

#ifndef PROJECTAPP_H
#define PROJECTAPP_H

#include <wx/app.h>

class projectApp : public wxApp
{
    public:
        virtual bool OnInit();
};

#endif // PROJECTAPP_H
