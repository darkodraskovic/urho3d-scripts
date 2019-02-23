#include "Game.h"

#include <Urho3D/Graphics/Octree.h>
#include <Urho3D/Resource/ResourceCache.h>
#include <Urho3D/Graphics/StaticModel.h>
#include <Urho3D/Graphics/Light.h>
#include <Urho3D/Graphics/Camera.h>
#include <Urho3D/Graphics/Renderer.h>
#include <Urho3D/Graphics/Viewport.h>
#include <Urho3D/Graphics/Material.h>
#include <Urho3D/Graphics/Model.h>

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

    //Create Model
    Node* boxNode = scene_->CreateChild("Model Node");
    StaticModel* boxObject = boxNode->CreateComponent<StaticModel>();
    boxObject->SetModel(cache->GetResource<Model>("Models/Box.mdl"));
    boxObject->SetMaterial(cache->GetResource<Material>("Materials/Stone.xml"));

    //Create Light
    Node* lightNode = scene_->CreateChild("Light Node");
    Light* light = lightNode->CreateComponent<Light>();
    light->SetLightType(LIGHT_DIRECTIONAL); 
    lightNode->SetDirection( Vector3(0.6f, -1.0f, 0.8f));

    //Create Camera
    Node* cameraNode = scene_->CreateChild("Camera");
    Camera* camera = cameraNode->CreateComponent<Camera>();

    camera->SetFarClip(100.0f); 
    cameraNode->Translate(Vector3(0,0,-2));

    //Create and Setup Viewport
    SharedPtr<Viewport> viewport(new Viewport(context_, scene_, camera));
	
    Renderer* renderer = GetSubsystem<Renderer>();
    renderer->SetViewport(0, viewport);    
}

URHO3D_DEFINE_APPLICATION_MAIN(Game)
