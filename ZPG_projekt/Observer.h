#pragma once

#include <vector>

enum class EventType
{
    MouseMoved,
    CameraMoved,
    WindowSizeChanged
};

struct Observer
{
    virtual void notified(EventType eventType, void* object) = 0;
};

class Subject
{
private:
    std::vector<Observer*> observers;
public:
    void registerObserver(Observer& obs);
    void notifyObservers(EventType type, void* obj);
};
