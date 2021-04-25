#ifndef _OBSERVER_H_
#define _OBSERVER_H_

template <typename InfoType, typename StateType>
class Subject;

template <typename InfoType, typename StateType>
class Observer {
public:
    // Used to notify the observer of a change of state 
    virtual void notify(Subject<InfoType, StateType> &whoFrom) = 0; 
    
    virtual ~Observer() = default;
};
#endif
