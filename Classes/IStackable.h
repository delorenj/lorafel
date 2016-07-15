//
// Created by Jarad DeLorenzo on 7/14/16.
//

#ifndef LORAFEL_ISTACKABLE_H
#define LORAFEL_ISTACKABLE_H


namespace lorafel {
    class IStackable {
    public:
        virtual int getMaxStack() const = 0;

        virtual int getNumStacks(int quantity) const {
            return (int)quantity/getMaxStack();
        }
    };
}

#endif //LORAFEL_ISTACKABLE_H
