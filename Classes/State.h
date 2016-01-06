//
// Created by Jarad DeLorenzo on 12/28/15.
//

#ifndef LORAFEL_STATE_H
#define LORAFEL_STATE_H

namespace lorafel {

    class StateMachine;
    class State {
    public:
        /**
         *  Called when entering state
         *
         *  @param previousState previous state or null if this is the first state
         */
        virtual void didEnterWithPreviousState(State* previousState) {};
        /**
         *  Called every frame by state machine
         *
         *  @param delta time
         */
        virtual void updateWithDeltaTime(float delta) {};
        /**
         *  Checks if next state is valid for transition
         *
         *  @param state next state
         *
         *  @return true if valid, false otherwise
         */
        virtual bool isValidNextState(State* state) {return false;};
        /**
         *  Called when exiting current state
         *
         *  @param nextState next state
         */
        virtual void willExitWithNextState(State* nextState) {};

        /**
         *  Get state machine
         *
         *  @return state machine
         */
        StateMachine* getStateMachine()
        {
            return _stateMachine;
        }

        /**
         *  Set State machine, this will be set when state has been added to state machine
         *
         *  @param stateMachine parent state machine
         */
        void setStateMachine(StateMachine* stateMachine)
        {
            _stateMachine = stateMachine;
        }

        virtual ~State(){};

        virtual const std::string getName() const = 0;
        

    protected:
        StateMachine* _stateMachine;
    };
}

#endif //LORAFEL_STATE_H
