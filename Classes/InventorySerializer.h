//
// Created by Jarad DeLorenzo on 8/3/16.
//

#ifndef LORAFEL_INVENTORYSERIALIZER_H
#define LORAFEL_INVENTORYSERIALIZER_H


#include "sqlite3.h"
#include "Serializer.h"
#include "StringPatch.h"

namespace lorafel {
    class InventorySerializer : public Serializer<std::string, int> {
    public:
        virtual int unserialize(std::string key) override {

        }

        virtual void serialize(std::string key, int value) override {
            try
            {
//                sqlite3 ass();
//                sqlite3_open("charles.db", &&ass);
//
//                db.exec("DROP TABLE IF EXISTS test");
//
//                // Begin transaction
//                SQLite::Transaction transaction(db);
//
//                db.exec("CREATE TABLE test (id INTEGER PRIMARY KEY, value TEXT)");
//
//                int nb = db.exec("INSERT INTO test VALUES (NULL, \"test\")");
//                CCLOG("INSERT INTO test VALUES (NULL, \"test\")\", returned ");
//
//                // Commit transaction
//                transaction.commit();
            }
            catch (std::exception& e)
            {
//                CCLOG("exception: ");
            }
        }
    };
}

#endif //LORAFEL_INVENTORYSERIALIZER_H
