//
// Created by Jarad DeLorenzo on 8/2/16.
//

#ifndef LORAFEL_SERIALIZER_H
#define LORAFEL_SERIALIZER_H

namespace lorafel {
    template<typename K,typename V>
    class Serializer {
    public:
        virtual void serialize(K key, V value) = 0;
        virtual V unserialize(K key) = 0;
    };
}

#endif //LORAFEL_SERIALIZER_H
