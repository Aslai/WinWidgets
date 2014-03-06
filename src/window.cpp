#define _WIN32_WINNT 0x0500
#include "window.h"
#define CS_DROPSHADOW 0x00020000
#include <windows.h>
#include<vector>
#include <string>
#include "globals.h"
#include "exception.h"
#include <stdio.h>

namespace WinWidgets{
    std::vector<Window::WindowClass*> Window::RegisteredClasses;
    std::vector<Window*> Window::RegisteredWindows;
    int Window::running;

    Window::_Set::_Set( Window* w ){

    }

    void Window::_Set::Position( Point p, Window::PositionFlags flags ){

    }

    void Window::_Set::Position( int x, int y, Window::PositionFlags flags ){

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

    Window::_Class::_Set::_Set( _Class* p ):parent(p){}

    void Window::_Class::_Set::Cursor( WinWidgets::Cursor cur ){

    }

    void Window::_Class::_Set::Color( WinWidgets::Color col ){
        Color( col.r, col.g, col.b, col.a );
    }

    void Window::_Class::_Set::Color( ClampByte r, ClampByte g, ClampByte b, ClampByte a ){
        parent->parent->MyClass->color.r = r;
        parent->parent->MyClass->color.g = g;
        parent->parent->MyClass->color.b = b;
        parent->parent->MyClass->color.a = a;
        parent->parent->MyClass->color.IsSet = 1;
    }

    Window::_Class::_EnableDisable::_EnableDisable( _Class* p, int type ):parent(p), t(type) {}

    void Window::_Class::_EnableDisable::DropShadow( ){
        if( t )
            parent->parent->MyClass->classflags |= Window::WindowFlags::DROP_SHADOW;
        else
            parent->parent->MyClass->classflags &= ~Window::WindowFlags::DROP_SHADOW;
    }

    void Window::_Class::_EnableDisable::Border( ){
        if( !t )
            parent->parent->MyClass->classflags |= Window::WindowFlags::BORDERLESS;
        else
            parent->parent->MyClass->classflags &= ~Window::WindowFlags::BORDERLESS;
    }

    void Window::_Class::_EnableDisable::CloseButton( ){
        if( t )
            parent->parent->MyClass->classflags |= Window::WindowFlags::HAS_CLOSE_BUTTON;
        else
            parent->parent->MyClass->classflags &= ~Window::WindowFlags::HAS_CLOSE_BUTTON;
    }

    void Window::_Class::_EnableDisable::Minimize( ){
        if( t )
            parent->parent->MyClass->classflags |= Window::WindowFlags::MINIMIZEABLE;
        else
            parent->parent->MyClass->classflags &= ~Window::WindowFlags::MINIMIZEABLE;
    }

    void Window::_Class::_EnableDisable::Maximize( ){
        if( t )
            parent->parent->MyClass->classflags |= Window::WindowFlags::MAXIMIZEABLE;
        else
            parent->parent->MyClass->classflags &= ~Window::WindowFlags::MAXIMIZEABLE;
    }

    void Window::_Class::_EnableDisable::Resizing( ){
        if( t )
            parent->parent->MyClass->classflags |= Window::WindowFlags::RESIZEABLE;
        else
            parent->parent->MyClass->classflags &= ~Window::WindowFlags::RESIZEABLE;
    }

    void Window::_Class::_EnableDisable::AlwaysOnTop( ){
        if( t )
            parent->parent->MyClass->classflags |= Window::WindowFlags::ALWAYS_ON_TOP;
        else
            parent->parent->MyClass->classflags &= ~Window::WindowFlags::ALWAYS_ON_TOP;
    }

    Window::_Class::_Class( Window* p ): parent(p), Set(this), Enable(this, 1), Disable(this, 0){}

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


        int registered = 0;
        for( unsigned int i = 0; i < RegisteredClasses.size(); ++i ){
            if( WinClass == RegisteredClasses[i]->classname ){
                MyClass = RegisteredClasses[i];
                registered = 1;
                if( MyClass->RegisteredWithWindows )
                    registered = 2;
                break;
            }
        }


        if( !registered ){
            WindowClass a;
            a.classname = WinClass;
            a.classflags = SpawnFlags;
            a.RegisteredWithWindows = 0;
            a.color.IsSet = false;
            a.cur.cur = LoadCursor( NULL, IDC_ARROW );
            a.ico.ico = LoadIcon( NULL, IDI_APPLICATION );
            a.smallico.ico = LoadIcon( NULL, IDI_APPLICATION );
            MyClass = new WindowClass(a);
            RegisteredClasses.push_back( MyClass );
        }


        if( registered != 2 ){
            const Window* t = this;


            int style = CS_DBLCLKS;
            if( MyClass->classflags & Window::WindowFlags::DROP_SHADOW )
                style |= CS_DROPSHADOW;

            WNDCLASSEX  windowclass;
            windowclass.hInstance = Global::hInstance;
            windowclass.lpszClassName = WinClass.c_str();
            windowclass.lpfnWndProc = windowprocedure;
            windowclass.style = style;
            windowclass.cbSize = sizeof( WNDCLASSEX );
            windowclass.hIcon = MyClass->ico.ico;
            windowclass.hIconSm = MyClass->smallico.ico;
            windowclass.hCursor  = MyClass->cur.cur;
            windowclass.lpszMenuName = NULL;
            windowclass.cbClsExtra = 0;
            windowclass.cbWndExtra = 0;
            if( MyClass->color.IsSet == false )
                windowclass.hbrBackground = (HBRUSH)COLOR_BACKGROUND;
            else
                windowclass.hbrBackground =  CreateSolidBrush( RGB( MyClass->color.r, MyClass->color.g, MyClass->color.b ) );
            if ( !( RegisterClassEx( &windowclass ) ) ) {
                Throw(RegistrationFailure);
                //If you're seeing this error, you are trying to re-register an existing class.
            }
            MyClass->RegisteredWithWindows = 1;
        }


        long long flags = MyClass->classflags;
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

    Window::Window( int x, int y, int w, int h, std::string title, std::string winclass, Window* Parent, Window::WindowFlags flags ) : Set(this), Get(this), Draw(this), Event(this), Class(this){
        HasSpawned = 0;
        MyClass = NULL;
        TheWindow = 0;

        SpawnFlags = flags;
        MyParent = Parent;
        SpawnPosition.x = x;
        SpawnPosition.y = y;
        SpawnPosition.w = w;
        SpawnPosition.h = h;
        WinTitle = title;
        WinClass = winclass;
        int registered = 0;
        for( unsigned int i = 0; i < RegisteredClasses.size(); ++i ){
            if( winclass == RegisteredClasses[i]->classname ){
                registered = 1;

                MyClass = RegisteredClasses[i];
                break;
            }
        }
        if( !registered ){

            WindowClass a;
            a.classname = WinClass;
            a.classflags = SpawnFlags;
            a.RegisteredWithWindows = 0;
            a.color.IsSet = false;
            a.cur.cur = LoadCursor( NULL, IDC_ARROW );
            a.ico.ico = LoadIcon( NULL, IDI_APPLICATION );
            a.smallico.ico = LoadIcon( NULL, IDI_APPLICATION );
            MyClass = new WindowClass(a);
            RegisteredClasses.push_back( MyClass );
        }
    }

    Window::Window( std::string title, std::string winclass, Window* Parent, Window::WindowFlags flags ) : Window( -1, -1, -1, -1, title, winclass, Parent, flags ){ }
    Window::Window( int x, int y, Rect r, std::string title, std::string winclass, Window* Parent, Window::WindowFlags flags ) : Window( x, y, r.w, r.h, title, winclass, Parent, flags ){ }
    Window::Window( Rect r, std::string title, std::string winclass, Window* Parent, Window::WindowFlags flags ) : Window( r.x, r.y, r.w, r.h, title, winclass, Parent, flags ){ }
    Window::Window( Point p, std::string title, std::string winclass, Rect r, Window* Parent, Window::WindowFlags flags ) : Window( -1, -1, p.x, p.y, title, winclass, Parent, flags ){ }

    Window::Window( HWND other ) : Set(this), Get(this), Draw(this), Event(this), Class(this){
        TheWindow = other;
        HasSpawned = 1;
        MyClass = 0;
    }

    Window::~Window(){

    }

}
