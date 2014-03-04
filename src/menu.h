#ifndef __WINWIDGETS_MENU_H__
#define __WINWIDGETS_MENU_H__

#include "wintypes.h"
#include <windows.h>
#include<vector>
#include <string>

namespace WinWidgets{
    class Menu{
        class MenuItem{
            class Callback{
            protected:
                MenuItem *mymenu;
            public:
                virtual void call( std::vector<void*> args ) = 0;
            };
            template<class T> class _Callback : public Callback{
                void (*cb)(MenuItem&, T, std::vector<void*> args);
                T data;
            public:
                _Callback( MenuItem* m, void (*mcb)(MenuItem&, T, std::vector<void*> args), T d):cb(mcb),data(d){mymenu=m;}
                void call( std::vector<void*> args ){cb(*mymenu, data, args );}
            };
            class _CallbackNoUser : public Callback{
                void (*cb)(MenuItem&, std::vector<void*> args);
            public:
                _CallbackNoUser(MenuItem* m, void (*mcb)(MenuItem&,std::vector<void*> args));
                void call( std::vector<void*> args );
            };
        public:
            std::string text;
            Menu* submenu;
            Callback* cb;
            MenuItem(std::string Text, Menu *Submenu = 0);
            void SetSubmenu( Menu *sub );
            template<class T> void SetCallback( void (*mcb)(MenuItem&, T, std::vector<void*> args), T d ){
                cb = new _Callback<T>(mcb, d);
            }
            template<class T> void SetCallback( void (*mcb)(MenuItem&, T&, std::vector<void*> args), T& d ){
                cb = new _Callback<T&>(mcb, d);
            }
            void SetCallback( void (*mcb)(MenuItem&, std::vector<void*> args) );
        };
        std::vector<MenuItem> MenuItems;
        class _Items{
            friend Menu;
            Menu* parent;
        public:
            _Items( Menu*p );
            template<class T> void Add( std::string text, T userdata, void (*mcb)(MenuItem&, T, std::vector<void*> args) ){
                parent->MenuItems.push_back( Menu::MenuItem( text, 0 ) );
                parent->MenuItems[parent->MenuItems.size()-1].SetCallback(mcb, userdata);
            }
            template<class T> void Add( std::string text, T& userdata, void (*mcb)(MenuItem&, T&, std::vector<void*> args) ){
                parent->MenuItems.push_back( Menu::MenuItem( text, 0 ) );
                parent->MenuItems[parent->MenuItems.size()-1].SetCallback(mcb, userdata);
            }
            void Add( std::string text, void (*mcb)(MenuItem&, std::vector<void*> args) = 0 );


        };
    public:
        _Items Items;
        Menu();
        ~Menu();
        operator HMENU();
    };
}

#endif
