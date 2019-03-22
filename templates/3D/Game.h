#ifndef __GAME_H_
#define __GAME_H_

#include <Urho3D/Core/CoreEvents.h>
#include <Urho3D/Engine/Application.h>
#include <Urho3D/Engine/Engine.h>
#include <Urho3D/Input/Input.h>
#include <Urho3D/Scene/Scene.h>

using namespace Urho3D;

class Game : public Application
{

    URHO3D_OBJECT(Game, Application)

public:
    Game(Context* context);

    virtual void Setup() override;
    virtual void Start() override;
    virtual void Stop() override;

    void CreateScene();
    void CreateCamera();
    void SetupViewport();
    void MoveCamera(float timeStep);
    void CreateStaticModel();
        
    /// Scene.
    SharedPtr<Scene> scene_;
    /// Camera scene node.
    SharedPtr<Node> cameraNode_;
    /// Camera yaw angle.
    float yaw_;
    /// Camera pitch angle.
    float pitch_;
    /// Flag to indicate whether touch input has been enabled.

    /// Box node.
    SharedPtr<Node> boxNode_;
    /// Rotation speed.
    Vector3 rotationSpeed_ = Vector3(10.0f, 10.0f, 10.0f);
    
private:
    void HandleKeyDown(StringHash eventType, VariantMap& eventData);    
    void HandleUpdate(StringHash eventType, VariantMap& eventData);
    void HandlePostRenderUpdate(StringHash eventType, VariantMap& eventData);

    /// Flag for drawing debug geometry.
    bool drawDebug_;
};

#endif // #ifndef __GAME_H_
