#define _WIN32_WINNT 0x0500
#include "window.h"
#define CS_DROPSHADOW 0x00020000
#include <windows.h>
#include<vector>
#include <string>
#include "globals.h"

namespace WinWidgets{
    std::vector<std::string> Window::RegisteredClasses;
    std::vector<Window*> Window::RegisteredWindows;
    int Window::running;

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
        return Window(FindWindowEx( NULL, NULL, NULL, title.c_str() ));
    }

    Window Window::Find::ByClass( std::string winClass ){
        return Window(FindWindowEx( NULL, NULL, winClass.c_str(), NULL ));
    }

    void Window::Refresh(){
        UpdateWindow( TheWindow );
    }

    void Window::Show(){
        if( !HasSpawned )
            Spawn();
        ShowWindow( TheWindow, SW_SHOW );
        UpdateWindow( TheWindow );
    }

    void Window::Hide(){
        ShowWindow( TheWindow, SW_HIDE );
        UpdateWindow( TheWindow );
    }

    void Window::ProcessMessages(){
        running = 1;
        MSG msg;
        while ( running ) {
            if ( !GetMessage( &msg, NULL, 0, 0 ) ) {
                break;
            }
            TranslateMessage( &msg );
            DispatchMessage( &msg );
        }
    }

    LRESULT CALLBACK Window::windowprocedure( HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam ) {
        Window* tgt = NULL;
        for( unsigned int i = 0; i < RegisteredWindows.size(); ++i ){
            if( hwnd == RegisteredWindows[i]->TheWindow ){
                tgt = RegisteredWindows[i];
                break;
            }
        }
        if( tgt == NULL ){
            return DefWindowProc( hwnd, msg, wparam, lparam );
        }
        return DefWindowProc( hwnd, msg, wparam, lparam );

    }

    void Window::Spawn(){
        int flags = SpawnFlags;
        int WinExFlags = WS_EX_LAYERED/* | WS_EX_OVERLAPPEDWINDOW*/;
        int WinStyleFlags = 0;
        AlwaysOnTop = false;
        if( flags & Window::WindowFlags::BORDERLESS )
            WinStyleFlags |= WS_POPUP;
        if( flags & Window::WindowFlags::ALWAYS_ON_TOP )
            AlwaysOnTop = true;
        //if( !(flags & Window::WindowFlags::MAXIMIZEABLE || Window::WindowFlags::__Unnamed::MINIMIZEABLE ) )
        //    WinExFlags |= WS_EX_TOOLWINDOW;

        if( flags & Window::WindowFlags::NO_TASKBAR )
            WinExFlags |= WS_EX_TOOLWINDOW;
        //if( flags & Window::WindowFlags::RESIZEABLE )

        TheWindow = CreateWindowEx( WinExFlags, WinClass.c_str(), WinTitle.c_str(), WinStyleFlags,
                           SpawnPosition.x==-1?CW_USEDEFAULT:SpawnPosition.x,
                           SpawnPosition.y==-1?CW_USEDEFAULT:SpawnPosition.y,
                           SpawnPosition.w==-1?640:SpawnPosition.w,
                           SpawnPosition.h==-1?480:SpawnPosition.h,
                           MyParent?MyParent->TheWindow:HWND_DESKTOP, NULL,
                           Global::hInstance, NULL );

        SetLayeredWindowAttributes( TheWindow, RGB( 255, 255, 255 ), 255, LWA_ALPHA );
        RegisteredWindows.push_back( this );
        HasSpawned = 1;
    }

    Window::Window( int x, int y, int w, int h, std::string title, std::string winclass, Window* Parent, int flags ) : Set(this), Get(this), Draw(this), Event(this){
        HasSpawned = 0;
        int registered = 0;
        TheWindow = 0;
        for( unsigned int i = 0; i < RegisteredClasses.size(); ++i ){
            if( winclass == RegisteredClasses[i] ){
                registered = 1;
                break;
            }
        }
        if( !registered ){
            const Window* t = this;
            WNDCLASSEX  windowclass;
            windowclass.hInstance = Global::hInstance;
            windowclass.lpszClassName = winclass.c_str();
            windowclass.lpfnWndProc = windowprocedure;
            windowclass.style = CS_DBLCLKS | CS_DROPSHADOW;
            windowclass.cbSize = sizeof( WNDCLASSEX );
            windowclass.hIcon = LoadIcon( NULL, IDI_APPLICATION );
            windowclass.hIconSm = LoadIcon( NULL, IDI_APPLICATION );
            windowclass.hCursor  = LoadCursor( NULL, IDC_ARROW );
            windowclass.lpszMenuName = NULL;
            windowclass.cbClsExtra = 0;
            windowclass.cbWndExtra = 0;
            windowclass.hbrBackground = (HBRUSH)COLOR_BACKGROUND;
            if ( !( RegisterClassEx( &windowclass ) ) ) {
                return;
            }
            RegisteredClasses.push_back( winclass );
        }
        SpawnFlags = flags;
        MyParent = Parent;
        SpawnPosition.x = x;
        SpawnPosition.y = y;
        SpawnPosition.w = w;
        SpawnPosition.h = h;
        WinTitle = title;
        WinClass = winclass;
    }

    Window::Window( std::string title, std::string winclass, Window* Parent, int flags ) : Window( -1, -1, -1, -1, title, winclass, Parent, flags ){ }
    Window::Window( int x, int y, Rect r, std::string title, std::string winclass, Window* Parent, int flags ) : Window( x, y, r.w, r.h, title, winclass, Parent, flags ){ }
    Window::Window( Rect r, std::string title, std::string winclass, Window* Parent, int flags ) : Window( r.x, r.y, r.w, r.h, title, winclass, Parent, flags ){ }
    Window::Window( Point p, std::string title, std::string winclass, Rect r, Window* Parent, int flags ) : Window( -1, -1, p.x, p.y, title, winclass, Parent, flags ){ }

    Window::Window( HWND other ) : Set(this), Get(this), Draw(this), Event(this){
        TheWindow = other;
        HasSpawned = 1;
    }

    Window::~Window(){

    }

}
