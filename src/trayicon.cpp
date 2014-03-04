#include "wintypes.h"
#include <windows.h>
#include<vector>
#include <string>
#include "menu.h"
#include "trayicon.h"

namespace WinWidgets{
    TrayIcon::_Set::_Set( TrayIcon *p ){

    }

    void TrayIcon::_Set::Icon( WinWidgets::Icon ico ){

    }

    void TrayIcon::_Set::Menu( WinWidgets::Menu menu ){

    }

    TrayIcon::_Clear::_Clear( TrayIcon *p ){

    }

    void TrayIcon::_Clear::Icon(){

    }

    void TrayIcon::_Clear::Menu(){

    }

    TrayIcon::TrayIcon(): Set(this), Clear(this){

    }

    TrayIcon::~TrayIcon(){

    }

    void TrayIcon::Hide(){

    }

    void TrayIcon::Show(){

    }

    void TrayIcon::Remove(){

    }

}

