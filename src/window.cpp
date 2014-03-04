#include "window.h"
#include <windows.h>
#include<vector>
#include <string>

namespace WinWidgets{
    Window::_Set::_Set( Window* w ){

    }

    void Window::_Set::Position( Point p, int flags ){

    }

    void Window::_Set::Position( int x, int y, int flags ){

    }

    void Window::_Set::Color(WinWidgets::Color color){

    }

    void Window::_Set::Color( ClampByte red, ClampByte green, ClampByte blue, ClampByte alpha ){

    }

    void Window::_Set::Color( ClampFloat red, ClampFloat green, ClampFloat blue, ClampFloat alpha ){

    }

    void Window::_Set::Size( unsigned int w, unsigned int h ){

    }

    void Window::_Set::Size( Rect r ){

    }

    void Window::_Set::Title( std::string value ){

    }

    void Window::_Set::Icon( WinWidgets::Icon ico ){

    }

    Window::_Get::_Get( Window* w ){

    }

    Point Window::_Get::Position( Point p, int flags ){

    }

    WinWidgets::Color Window::_Get::Color(){

    }

    WinWidgets::Icon Window::_Get::Icon(){

    }

    std::string Window::_Get::Title(){

    }

    std::string Window::_Get::Class(){

    }

    Window::_Draw::_Set::_Set( Window::_Draw* p ) : parent(p){

    }

    void Window::_Draw::_Set::Brush( WinWidgets::Brush brush ){

    }

    void Window::_Draw::_Set::Brush( WinWidgets::Color, int size, bool filled ){

    }

    void Window::_Draw::_Set::Brush( ClampByte red, ClampByte green, ClampByte blue, int size, bool filled ){

    }

    void Window::_Draw::_Set::Brush( ClampByte red, ClampByte green, ClampByte blue, ClampByte alpha, int size, bool filled ){

    }

    Window::_Draw::_Draw( Window* w ) : Set(this){

    }

    void Window::_Draw::Rectangle( int x, int y, int w, int h ){

    }

    void Window::_Draw::Rectangle( Point pos, int w, int h ){

    }

    void Window::_Draw::Rectangle( Point pos1, Point pos2 ){

    }

    void Window::_Draw::Text( int x, int y, std::string text ){

    }

    void Window::_Draw::Text( Point pos, std::string text ){

    }

    Window::_Event::_EventDataNoUser::_EventDataNoUser( int eventnam, void (*cb)(Window&, int messagename, std::vector<void*> args)){

    }

    void Window::_Event::_EventDataNoUser::call( Window* p, int msgname, std::vector<void*> args ){

    }

    Window::_Event::_Event( Window* p ){

    }

    Window::_Event::~_Event(){

    }

    void Window::_Event::Register( int eventname, void (*ev)(Window&, std::vector<void*> args)){

    }

    void Window::_Event::Unregister( int eventname ){

    }

    Window Window::Find::ByTitle( std::string title ){

    }

    Window Window::Find::ByClass( std::string winClass ){

    }

    void Window::Refresh(){

    }

    void Window::Show(){

    }

    void Window::Hide(){

    }

    Window::Window( int flags ) : Set(this), Get(this), Draw(this), Event(this){

    }

    Window::Window( int x, int y, int w, int h, std::string title, std::string winclass, int flags ) : Set(this), Get(this), Draw(this), Event(this){

    }

    Window::Window( int x, int y, Rect r, std::string title, std::string winclass, int flags ) : Set(this), Get(this), Draw(this), Event(this){

    }

    Window::Window( Rect r, std::string title, std::string winclass, int flags ) : Set(this), Get(this), Draw(this), Event(this){

    }

    Window::Window( Point p, std::string title, std::string winclass, Rect r, int flags ) : Set(this), Get(this), Draw(this), Event(this){

    }

    Window::~Window(){

    }

}
