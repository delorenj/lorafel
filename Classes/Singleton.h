//
// Created by Jarad DeLorenzo on 12/22/15.
//

#ifndef LORAFEL_SINGLETON_H
#define LORAFEL_SINGLETON_H


namespace lorafel {

    template<class T>
    class Singleton {
        static T* _instance;

    public:
        static T* getInstance() {
            if(_instance == nullptr) {
                _instance = new T;
            }
            return _instance;
        }
    };
}


#endif //LORAFEL_SINGLETON_H
