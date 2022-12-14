#pragma once

#include <vector>

enum EventType
{
    MouseMoved,
    MouseClicked,
    MouseScrolled,
    KeyboardPressed,
    CameraMoved,
    LightMoved,
    LightChangedState,
    WindowSizeChanged
};

struct Observer
{
    virtual void onSubjectNotification(EventType eventType, void* object) = 0;
};

class Subject
{
private:
    std::vector<Observer*> observers;
public:
    void registerObserver(Observer& obs);
    void notifyObservers(EventType type, void* obj);
};
