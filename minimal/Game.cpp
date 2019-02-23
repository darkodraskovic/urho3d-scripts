#include "Game.h"

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
    SubscribeToEvent(E_KEYDOWN, URHO3D_HANDLER(Game, HandleKeyDown));
    SubscribeToEvent(E_UPDATE, URHO3D_HANDLER(Game, HandleUpdate));
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

void Game::HandleUpdate(StringHash eventType, VariantMap& eventData)
{
    using namespace Update;

    // Take the frame time step, which is stored as a float
    float timeStep = eventData[P_TIMESTEP].GetFloat();
}

URHO3D_DEFINE_APPLICATION_MAIN(Game)
