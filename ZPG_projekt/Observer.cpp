#include "Observer.h"

void Subject::registerObserver(Observer& obs)
{
    observers.push_back(&obs);
}

void Subject::notifyObservers(EventType type, void* obj)
{
    for (Observer* obs : observers)
        obs->notified(type, obj);
}
