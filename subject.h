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
    void setState(StateType newS);

public:
    void attach(Observer<InfoType, StateType> *o);
    void detach(Observer<InfoType, StateType> *o);
    void notifyObservers();
    virtual InfoType getInfo() const noexcept = 0;
    StateType getState() const noexcept;
};

template <typename InfoType, typename StateType>
void Subject<InfoType, StateType>::attach(Observer<InfoType, StateType> *o) {
    if(std::find(observers.begin(), observers.end(), o) != observers.end()) return;
    observers.emplace_back(o);
}

template <typename InfoType, typename StateType>
void Subject<InfoType, StateType>::notifyObservers() {
    for (auto &ob : observers)
        ob->notify(*this);
}

template <typename InfoType, typename StateType>
void Subject<InfoType, StateType>::setState(StateType newS) {
    state = newS;
}

template <typename InfoType, typename StateType>
void Subject<InfoType, StateType>::detach( Observer<InfoType, StateType> *o ) {
  for ( auto it = observers.begin(); it != observers.end(); ++it ) {
    if ( *it == o ) {
      observers.erase(it);
      break;
    }
  }
}

template <typename InfoType, typename StateType>
StateType Subject<InfoType, StateType>::getState() const noexcept {
    return state;
}

#endif
