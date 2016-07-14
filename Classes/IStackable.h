//
// Created by Jarad DeLorenzo on 7/14/16.
//

#ifndef LORAFEL_ISTACKABLE_H
#define LORAFEL_ISTACKABLE_H


namespace lorafel {
    class IStackable {
    public:
        virtual int getMaxStack() const { return m_maxStack; }
        virtual int getNumStacks(int quantity) const { return (int)quantity/getMaxStack(); }

    protected:
        int m_maxStack = 20;
    };
}

#endif //LORAFEL_ISTACKABLE_H
