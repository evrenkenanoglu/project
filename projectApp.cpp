/***************************************************************
 * Name:      projectApp.cpp
 * Purpose:   Code for Application Class
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

#include "projectApp.h"
#include "projectMain.h"

IMPLEMENT_APP(projectApp);

bool projectApp::OnInit()
{
    projectFrame* frame = new projectFrame(0L);
    
    frame->Show();
    
    return true;
}
