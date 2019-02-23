#ifndef __GAME_H_
#define __GAME_H_

#include <Urho3D/Core/CoreEvents.h>
#include <Urho3D/Engine/Application.h>
#include <Urho3D/Engine/Engine.h>
#include <Urho3D/Input/InputEvents.h>

using namespace Urho3D;

class Game : public Application
{

    URHO3D_OBJECT(Game, Application)

public:
    Game(Context* context);

    virtual void Setup();
    virtual void Start();
    virtual void Stop();

private:
    void HandleKeyDown(StringHash eventType, VariantMap& eventData);    
    void HandleUpdate(StringHash eventType, VariantMap& eventData);    
};

#endif // #ifndef __GAME_H_
