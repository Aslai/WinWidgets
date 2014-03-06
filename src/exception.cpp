#include "exception.h"

namespace WinWidgets{
    namespace Exception{
            Exception::Exception( std::string name, std::string func, std::string file, int line )
                : Name(name), Function( func ), File(file), Line(line) { }
            RegistrationFailure::RegistrationFailure( std::string func, std::string file, int line )
                : Exception( "Registration Failure", func, file, line ){ }
    }
}

