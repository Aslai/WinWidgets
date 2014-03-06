#ifndef __WINWIDGETS_EXCEPTION_H__
#define __WINWIDGETS_EXCEPTION_H__
#include <string>

namespace WinWidgets{
    namespace Exception{
        class Exception{
        public:
            std::string Name;
            std::string Function;
            std::string File;
            int Line;
            Exception( std::string name, std::string func, std::string file, int line );
        };
        class RegistrationFailure : public Exception{
        public:
            RegistrationFailure( std::string func, std::string file, int line );
        };
    }
}

#define Throw(a) throw WinWidgets::Exception::a(__FUNCTION__, __FILE__, __LINE__)

#endif
