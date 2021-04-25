#include "subject.h"
using namespace std;

template <typename InfoType, typename StateType>
void Subject<InfoType, StateType>::attach(Observer<InfoType, StateType> *o) {
    if (find(observers.begin(), observers.end(), o) != observers.end()) return;
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
void Subject<InfoType, StateType>::detach( Observer<InfoType, StateType> *o) {
  for (auto it = observers.begin(); it != observers.end(); ++it) {
    if (*it == o) {
      observers.erase(it);
      break;
    }
  }
}

template <typename InfoType, typename StateType>
StateType Subject<InfoType, StateType>::getState() const noexcept {
    return state;
}
