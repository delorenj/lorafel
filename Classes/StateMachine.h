//
// Created by Jarad DeLorenzo on 12/28/15.
//

#ifndef LORAFEL_STATEMACHINE_H
#define LORAFEL_STATEMACHINE_H

#include <unordered_map>
#include <typeinfo>
#include <stack>
#include "State.h"

namespace lorafel {

    class StateMachine {
    public:
        static StateMachine* create()
        {
            auto ref = new StateMachine();
            return ref;
        }

        template<class T>
        T* findState()
        {
            const std::string name = typeid(T).name();
            if (_states.count(name) != 0)
            {
                return static_cast<T*>(_states[name]);
            }
            return nullptr;
        }

        template<typename T, class... Args>
        void addState(Args&&... args)
        {
            auto typeId = typeid(T).name();

            auto state = new T(std::forward<Args>(args)...);
            state->setStateMachine(this);
            _states.insert({typeId, state});
        }

        template<typename T>
        bool canEnterState()
        {
            if (_state == nullptr)
            {
                return true;
            }
            else
            {
                auto state = findState<T>();
                if (state)
                {
                    return _state->isValidNextState(state);
                }
            }
            return false;
        }

        template<typename T>
        bool enterState()
        {
            auto state = findState<T>();
            if (state)
            {
                if (_state == nullptr)
                {
                    _state = state;
                    _state->didEnterWithPreviousState(nullptr);
                    return true;
                }
                else
                {
                    if (_state->isValidNextState(state))
                    {
                        _state->willExitWithNextState(state);
                        state->didEnterWithPreviousState(_state);
                        _state = state;
                        return true;
                    }
                }
            }
            return false;
        }

        template<typename T>
        bool setState()
        {
            auto state = findState<T>();
            if (state)
            {
                if (_state == nullptr)
                {
                    _state = state;
                    _state->didEnterWithPreviousState(nullptr);
                    return true;
                }
                else
                {
                    _state->willExitWithNextState(state);
                    state->didEnterWithPreviousState(_state);
                    _state = state;
                    return true;
                }
            }
            return false;
        }

        void updateWithDeltaTime(float delta)
        {
            if (_state != nullptr)
            {
                _state->updateWithDeltaTime(delta);
            }
        }

        State* getState()
        {
            return _state;
        }

        ~StateMachine()
        {
            _state = nullptr;
        }

        bool setState(float i);


        void pushState()
        {
            if(_state != nullptr) {
                _stack.push(_state);
            }
        }

        State* popState() {
            if(!_stack.empty()) {
                auto s = _stack.top();
                _stack.pop();
                _state = s;
            }
            return _state;
        }

        template<typename T>
        bool popState()
        {
            auto state = findState<T>();
            if (state)
            {
                if (_state == nullptr)
                {
                    _state = state;
                    _state->didEnterWithPreviousState(nullptr);
                    return true;
                }
                else
                {
                    _state->willExitWithNextState(state);
                    state->didEnterWithPreviousState(_state);
                    _state = state;
                    return true;
                }
            }
            return false;
        }

    private:
        std::unordered_map<std::string, State*> _states;
        std::stack<State*> _stack;
        State* _state;

        StateMachine():
                _state(nullptr)
        {

        }
    };

}

#endif //LORAFEL_STATEMACHINE_H
