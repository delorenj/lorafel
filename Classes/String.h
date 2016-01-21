//
// Created by Jarad DeLorenzo on 1/19/16.
//

#ifndef LORAFEL_STRING_H
#define LORAFEL_STRING_H

namespace lorafel {
    class String {
    public:
        template < typename T >
        static std::string to_string( T& n ) {
            std::ostringstream stm;
            stm << n;
            return stm.str();
        }
    };
}

#endif //LORAFEL_STRING_H
