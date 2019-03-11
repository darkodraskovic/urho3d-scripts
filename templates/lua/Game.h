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

    virtual void Setup() override;
    virtual void Start() override;
    virtual void Stop() override;
};

#endif // #ifndef __GAME_H_
