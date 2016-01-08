//
// Created by Jarad DeLorenzo on 1/6/16.
//

#ifndef LORAFEL_MATCHRESULT_H
#define LORAFEL_MATCHRESULT_H

namespace lorafel {
    template <typename T>
    class MatchResult {
    public:
        MatchResult<T>(T val) : m_val(val) { };
        virtual ~MatchResult() { };

        virtual void apply() = 0;

    public:
        T getVal() const {
            return m_val;
        }

        void setVal(T val) {
            m_val = val;
        }

    protected:
        T m_val;

    };
}

#endif //LORAFEL_MATCHRESULT_H
