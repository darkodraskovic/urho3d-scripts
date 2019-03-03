#ifndef __GAME_H_
#define __GAME_H_

#include <Urho3D/Core/CoreEvents.h>
#include <Urho3D/Engine/Application.h>
#include <Urho3D/Engine/Engine.h>
#include <Urho3D/Input/InputEvents.h>
#include <Urho3D/Scene/Scene.h>
#include <Urho3D/Graphics/Camera.h>

using namespace Urho3D;

namespace Urho3D
{
    class Node;
    class Scene;
}

class Game : public Application
{

    URHO3D_OBJECT(Game, Application)

public:
    Game(Context* context);

    virtual void Setup();
    virtual void Start();
    virtual void Stop();

protected:
    /// Scene.
    SharedPtr<Scene> scene_;
    /// Camera scene node.
    SharedPtr<Node> cameraNode_;
    
private:
    void CreateScene();
    void CreateGround();
    
    void SetupCamera();
    void SetupViewport();
    
    void MoveCamera(float timeStep);
    
    void HandleKeyDown(StringHash eventType, VariantMap& eventData);
    void HandleUpdate(StringHash eventType, VariantMap& eventData);
};

#endif // #ifndef __GAME_H_
