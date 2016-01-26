//
// Created by Jarad DeLorenzo on 1/19/16.
//

#ifndef LORAFEL_STRING_H
#define LORAFEL_STRING_H

#include <sstream>
#include <string>

namespace lorafel {
    template < typename T > std::string to_string( const T& n )
    {
        std::ostringstream stm ;
        stm << n ;
        return stm.str() ;
    }
}

#endif //LORAFEL_STRING_H
