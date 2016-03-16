//
// Created by Jarad DeLorenzo on 12/28/15.
//

#include "StateMachine.h"

using namespace lorafel;

template<class T>
T *StateMachine::findState() {
    const std::string name = typeid(T).name();
    if (_states.count(name) != 0)
    {
        return static_cast<T*>(_states[name]);
    }
    return nullptr;
}

template<typename T, class... Args>
void StateMachine::addState(Args&&... args) {
    auto typeId = typeid(T).name();

    auto state = new T(std::forward<Args>(args)...);
    state->setStateMachine(this);
    _states.insert({typeId, state});
}

template<typename T>
bool StateMachine::canEnterState() {
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
bool StateMachine::enterState() {
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
bool StateMachine::setState() {
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

void StateMachine::updateWithDeltaTime(float delta) {
    if (_state != nullptr)
    {
        _state->updateWithDeltaTime(delta);
    }
}

State *StateMachine::getState() {
    return _state;
}

StateMachine::~StateMachine() {
    _state = nullptr;
}

StateMachine::StateMachine() : _state(nullptr) {

}
