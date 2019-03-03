#include "Game.h"

#include <Urho3D/Graphics/Octree.h>
#include <Urho3D/Resource/ResourceCache.h>
#include <Urho3D/Graphics/Camera.h>
#include <Urho3D/Graphics/Renderer.h>
#include <Urho3D/Graphics/Viewport.h>
#include <Urho3D/Graphics/RenderPath.h>
#include <Urho3D/Resource/XMLFile.h>

using namespace Urho3D;

Game::Game(Context* context):
    Application(context)
{

}

void Game::Setup()
{
    engineParameters_["FullScreen"] = false;
}

void Game::Start()
{
    CreateScene();
    SubscribeToEvent(E_KEYDOWN, URHO3D_HANDLER(Game, HandleKeyDown));
}

void Game::Stop()
{

}

void Game::HandleKeyDown(StringHash eventType, VariantMap& eventData)
{
    using namespace KeyDown;

    // Check for pressing ESC. Note the engine_ member variable for convenience access to the Engine object
    int key = eventData[P_KEY].GetInt();

    if (key == KEY_ESCAPE)
        {
            engine_->Exit();
        }

}

void Game::CreateScene()
{
    scene_ = new Scene(context_);

    //Create the Octree
    scene_->CreateComponent<Octree>();

    //Get the Resource Cache subsystem
    ResourceCache* cache = GetSubsystem<ResourceCache>();

    //Create Camera
    Node* cameraNode = scene_->CreateChild("Camera");
    Camera* camera = cameraNode->CreateComponent<Camera>();

    camera->SetFarClip(100.0f); 
    cameraNode->Translate(Vector3(0,0,-2));

    //Create and Setup Viewport
    SharedPtr<Viewport> viewport(new Viewport(context_, scene_, camera));
	
    Renderer* renderer = GetSubsystem<Renderer>();
    renderer->SetViewport(0, viewport);

    SharedPtr<RenderPath> effectRenderPath = viewport->GetRenderPath()->Clone();
    effectRenderPath->Append(cache->GetResource<XMLFile>("PostProcess/BasicPP.xml"));
    viewport->SetRenderPath(effectRenderPath);
}

URHO3D_DEFINE_APPLICATION_MAIN(Game)
