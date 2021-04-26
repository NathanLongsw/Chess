#ifndef SUBJECT_H
#define SUBJECT_H
#include <vector>
#include <algorithm>

/* A note on InfoType and StateType:

   We have separated the collection of fields into two parts:  its Info
   and its State.

   Info is for the parts of the subject inherent to what it is:  its position
   and its colour.

   State is for the parts of the subject that, when changed, trigger
   notifications. This is the information that the Observer "gets" when it
   calls getState on the subject.  It comprises the type of state, rank, position,
   and a colour. For more details, see state.h.
*/

template <typename InfoType, typename StateType>
class Observer;

template <typename InfoType, typename StateType>
class Subject {
    std::vector<Observer<InfoType, StateType> *> observers;
    StateType state;

protected:
    // Sets the state to newS
    void setState(StateType newS);

public:
    // Appends an observer to observers
    void attach(Observer<InfoType, StateType> *o);

    // Removes an observer from observers
    void detach(Observer<InfoType, StateType> *o);

    // Notfies the observers
    void notifyObservers();

    // Pure virutal getter to retrieve the info
    virtual InfoType getInfo() const noexcept = 0;

    // Getter to retrieve the state
    StateType getState() const noexcept;
};

#endif
