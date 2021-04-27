#ifndef _OBSERVER_H_
#define _OBSERVER_H_

template <typename InfoType, typename StateType>
class Subject;

/*  Abstract base class which enables the Observer design pattern. Observers
    in the context of this program are the Pieces of the chess board and the 
    displays.  */

template <typename InfoType, typename StateType>
class Observer {
public:
    // Used to notify the observer of a change of state 
    virtual void notify(Subject<InfoType, StateType> &whoFrom) = 0; 
    
    virtual ~Observer() = default;
};

#endif
