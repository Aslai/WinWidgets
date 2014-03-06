#include "src/window.h"
using namespace WinWidgets;
#include "src/exception.h"
#include <stdio.h>
int main(){

    Window win[4] = {
    Window(0, 0, 100, 100, "MyWindow", "Frogs142" ),
    Window(100, 0, 100, 100, "MyWindow", "Frogs242" ),
    Window(0, 100, 100, 100, "MyWindow", "Frogs34" ),
    Window(100, 100, 100, 100, "MyWindow", "Frogs44" )
    };

    win[0].Class.Set.Color( 255, 0, 0 );
    win[1].Class.Set.Color( 0, 255, 0 );
    win[2].Class.Set.Color( 255, 255, 0 );
    win[3].Class.Set.Color( 0, 0, 255 );

    win[0].Class.Disable.Border();
    win[1].Class.Disable.Border();
    win[2].Class.Disable.Border();
    win[3].Class.Disable.Border();

    win[0].Show();
    win[1].Show();
    win[2].Show();
    win[3].Show();

    Window::ProcessMessages();
}
