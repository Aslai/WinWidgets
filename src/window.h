#ifndef __WINWIDGETS_WINDOW_H__
#define __WINWIDGETS_WINDOW_H__

#include "wintypes.h"
#include <windows.h>
#include<vector>
#include <string>

namespace WinWidgets{

    class Window{
    public:
        struct WindowFlags{
            enum {
                NONE = 0,
                RESIZEABLE = 1,
                BORDERLESS = 2,
                MINIMIZEABLE = 4,
                MAXIMIZEABLE = 8,
                ALWAYS_ON_TOP = 16
            };
        };
        struct PositionFlags{
            enum{
                TOPMOST = 1,
                BOTTOMMOST = 2,
                NO_MOVE = 4
            };
        };
    private:
        HWND TheWindow;
        class _Set{
            Window* parent;
        public:
            _Set( Window* w );
            void Position( Point p, PositionFlags flags );
            void Position( int x, int y, PositionFlags flags );
            void Color(Color color);
            void Color( ClampValue<int, 0, 255> red, ClampValue<int, 0, 255> green, ClampValue<int, 0, 255> blue, ClampValue<int, 0, 255> alpha = 255);
            void Color( ClampValue<double, 0, 1> red, ClampValue<double, 0, 1> green, ClampValue<double, 0, 1> blue, ClampValue<double, 0, 1> alpha = 1);
            void Size( unsigned int w, unsigned int h );
            void Size( Rect r );
            void Title( std::string value );
            void Icon( WinWidgets::Icon ico );
        };
        class _Get{
            Window* parent;
        public:
            _Get( Window* w );
            Point Position( Point p, PositionFlags flags );
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
                void Brush( ClampValue<int, 0, 255> red, ClampValue<int, 0, 255> green, ClampValue<int, 0, 255> blue, int size, bool filled );
                void Brush( ClampValue<int, 0, 255> red, ClampValue<int, 0, 255> green, ClampValue<int, 0, 255> blue, ClampValue<int, 0, 255> alpha, int size, bool filled );
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
        void Refresh();
        void Show();
        void Hide();
        Window( int flags = WindowFlags::NONE );
        Window( int x, int y, int w, int h, std::string title, std::string winclass, int flags = WindowFlags::NONE );
        Window( int x, int y, Rect r, std::string title, std::string winclass, int flags = WindowFlags::NONE );
        Window( Rect r, std::string title, std::string winclass, int flags = WindowFlags::NONE );
        Window( Point p, std::string title, std::string winclass, Rect r, int flags = WindowFlags::NONE );
        ~Window();
    };
}

#endif
