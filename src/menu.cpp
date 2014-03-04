#include "wintypes.h"
#include <windows.h>
#include<vector>
#include <string>
#include "menu.h"

namespace WinWidgets{
    Menu::MenuItem::_CallbackNoUser::_CallbackNoUser(MenuItem* m, void (*mcb)(MenuItem&,std::vector<void*> args)){

    }

    void Menu::MenuItem::_CallbackNoUser::call( std::vector<void*> args ){

    }

    Menu::MenuItem::MenuItem(std::string Text, Menu *Submenu ){

    }

    void Menu::MenuItem::SetSubmenu( Menu *sub ){

    }

    void Menu::MenuItem::SetCallback( void (*mcb)(MenuItem&, std::vector<void*> args) ){

    }

    Menu::_Items::_Items( Menu*p ){

    }

    void Menu::_Items::Add( std::string text, void (*mcb)(MenuItem&, std::vector<void*> args) ){

    }

    Menu::Menu() : Items(this){

    }

    Menu::~Menu(){

    }

    Menu::operator HMENU(){

    }
}
