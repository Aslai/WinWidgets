#include "src/window.h"
using namespace WinWidgets;

int main(){
    for( int i = 0; i < 10; ++i ){
        (new Window( "Windows!", "WINBLOWS" ))->Show();
    }
    Window::ProcessMessages();
}
