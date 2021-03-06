#ifndef __WINWIDGETS_WINDOW_H__
#define __WINWIDGETS_WINDOW_H__

#include "wintypes.h"
#include <windows.h>
#include<vector>
#include <string>

namespace WinWidgets{

    class Window{
    public:
        enum State{
            ON = 0,
            OFF
        };
        enum WindowFlags{
            NONE = 0,
            RESIZEABLE = 1,
            BORDERLESS = 2,
            MINIMIZEABLE = 4,
            MAXIMIZEABLE = 8,
            ALWAYS_ON_TOP = 16,
            NO_TASKBAR = 32,
            DROP_SHADOW = 64,
            HAS_CLOSE_BUTTON = 128
        };
        enum PositionFlags{
            TOPMOST = 1,
            BOTTOMMOST = 2,
            NO_MOVE = 4
        };
    private:
        struct WindowClass{
            std::string classname;
            long long classflags;
            Cursor cur;
            Icon ico;
            Icon smallico;

            Color color;
            int RegisteredWithWindows;
        };
        static std::vector<WindowClass*> RegisteredClasses;
        static std::vector<Window*> RegisteredWindows;
        HWND TheWindow;
        std::string WinTitle, WinClass;
        WindowClass* MyClass;
        Window* MyParent;
        WindowFlags SpawnFlags;
        Rect SpawnPosition;
        static int running;

        bool AlwaysOnTop;
        bool HasSpawned;
        class _Set{
            Window* parent;
        public:
            _Set( Window* w );
            void Position( Point p, Window::PositionFlags flags );
            void Position( int x, int y, Window::PositionFlags flags );
            void Color(Color color);
            void Color( ClampByte red, ClampByte green, ClampByte blue, ClampByte alpha = 255);
            void Color( ClampFloat red, ClampFloat green, ClampFloat blue, ClampFloat alpha = 1);
            void Size( unsigned int w, unsigned int h );
            void Size( Rect r );
            void Title( std::string value );
            void Icon( WinWidgets::Icon ico );
        };
        class _Get{
            Window* parent;
        public:
            _Get( Window* w );
            Point Position( Point p, int flags );
            WinWidgets::Color Color();
            WinWidgets::Icon Icon();
            std::string Title();
            std::string Class();

        };
        class _Draw{
            Window* parent;
            class _Set{
                _Draw*parent;
            public:
                _Set( _Draw* p );
                void Brush( WinWidgets::Brush brush );
                void Brush( WinWidgets::Color, int size, bool filled );
                void Brush( ClampByte red, ClampByte green, ClampByte blue, int size, bool filled );
                void Brush( ClampByte red, ClampByte green, ClampByte blue, ClampByte alpha, int size, bool filled );
            };
        public:
            _Set Set;
            _Draw( Window* w );
            void Rectangle( int x, int y, int w, int h );
            void Rectangle( Point pos, int w, int h );
            void Rectangle( Point pos1, Point pos2 );
            void Text( int x, int y, std::string text );
            void Text( Point pos, std::string text );
        };
        class _Event{
            Window* parent;
            class EventData{
            protected:
                int eventname;
            public:
                virtual void call( Window* p, int msgname, std::vector<void*> args ) = 0;
            };
            class _EventDataNoUser : public EventData{
                void (*callback)(Window&, int messagename, std::vector<void*> args);
            public:
                _EventDataNoUser( int eventnam, void (*cb)(Window&, int messagename, std::vector<void*> args));
                void call( Window* p, int msgname, std::vector<void*> args );
            };

            template<class T> class _EventData : public EventData{
                void (*callback)(Window&, int messagename, std::vector<void*> args, T userdata);
                T userdat;
            public:
                _EventData( int eventnam, void (*cb)(Window&, int messagename, std::vector<void*> args, T userdata), T userdata ) : callback(cb), userdat(userdata){
                    eventname = eventnam;
                }
                void call( Window* p, int msgname, std::vector<void*> args ){
                    callback( *p, msgname, args, userdat );
                }
            };
            std::vector<EventData*> Events;
        public:
            _Event( Window* p );
            ~_Event(); //REMEMBER TO FREE EVERYTHING IN THE VECTOR
            template<class T> void Register( int eventname, void (*ev)(Window&, std::vector<void*> args,T userdata), T userdata ){
                Events.push_back(new _EventData<T>(eventname, ev, userdata ));
            }
            void Register( int eventname, void (*ev)(Window&, std::vector<void*> args));

            void Unregister( int eventname );
        };
        class _Class{
            Window* parent;
            class _Set{
                _Class* parent;
            public:
                _Set( _Class* p );
                void Cursor( WinWidgets::Cursor cur );
                void Color( WinWidgets::Color col );
                void Color( ClampByte r, ClampByte g, ClampByte b, ClampByte a = 255 );
            };
            class _EnableDisable{
                _Class* parent;
                int t;
            public:
                _EnableDisable( _Class* p, int type );
                void DropShadow( );
                void Border( );
                void CloseButton( );
                void Minimize( );
                void Maximize( );
                void Resizing( );
                void AlwaysOnTop( );
            };
        public:
            _Class( Window* p );
            _Set Set;
            _EnableDisable Enable;
            _EnableDisable Disable;
            friend _Set;
            friend _EnableDisable;
        };
        static LRESULT CALLBACK windowprocedure( HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam );
        void Spawn();
    public:
        class Find{
        public:
            static Window ByTitle( std::string title );
            static Window ByClass( std::string winClass );
        };

        _Set Set;
        _Get Get;
        _Draw Draw;
        _Event Event;
        _Class Class;

        void Refresh();
        void Show();
        void Hide();
        static void ProcessMessages();
        Window( std::string title, std::string winclass, Window* Parent = NULL, WindowFlags flags = WindowFlags::NONE );
        Window( int x, int y, int w, int h, std::string title, std::string winclass, Window* Parent = NULL, WindowFlags flags = WindowFlags::NONE );
        Window( int x, int y, Rect r, std::string title, std::string winclass, Window* Parent = NULL, WindowFlags flags = WindowFlags::NONE );
        Window( Rect r, std::string title, std::string winclass, Window* Parent = NULL, WindowFlags flags = WindowFlags::NONE );
        Window( Point p, std::string title, std::string winclass, Rect r, Window* Parent = NULL, WindowFlags flags = WindowFlags::NONE );
        Window( HWND other );
        ~Window();
    };
}

#endif
