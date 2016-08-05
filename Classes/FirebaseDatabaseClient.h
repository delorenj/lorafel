//
// Created by Jarad DeLorenzo on 8/5/16.
//

#ifndef LORAFEL_FIREBASEDATABASECLIENT_H
#define LORAFEL_FIREBASEDATABASECLIENT_H

namespace lorafel {
    class FirebaseDatabaseClient {
    public:
        static FirebaseDatabaseClient *getInstance() {
            if (_instance == nullptr) {
                _instance = new FirebaseDatabaseClient();
            }
            return _instance;
        }

    protected:
        static FirebaseDatabaseClient *_instance;

    };
}

#endif //LORAFEL_FIREBASEDATABASECLIENT_H
