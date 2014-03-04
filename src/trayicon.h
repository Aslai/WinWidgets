#ifndef __WINWIDGETS_TRAYICON_H__
#define __WINWIDGETS_TRAYICON_H__

#include "wintypes.h"
#include <windows.h>
#include<vector>
#include <string>
#include "menu.h"
#include "window.h"

namespace WinWidgets{
    class TrayIcon{
        NOTIFYICONDATA trayiconhandle;
        Window* mywindow;
        Menu mymenu;
        class _Set{
            friend TrayIcon;
            TrayIcon* parent;
        public:
            _Set( TrayIcon *p );
            void Icon( WinWidgets::Icon ico );
            void Menu( WinWidgets::Menu menu );
        };
        class _Clear{
            friend TrayIcon;
            TrayIcon* parent;
        public:
            _Clear( TrayIcon *p );
            void Icon();
            void Menu();
        };

    public:
        TrayIcon();
        ~TrayIcon();
        _Set Set;
        _Clear Clear;
        void Hide();
        void Show();
        void Remove();

    };
}

#endif
