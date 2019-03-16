#include "Game.h"

#include <Urho3D/Resource/ResourceCache.h>
#include <Urho3D/LuaScript/LuaFile.h>
#include <Urho3D/LuaScript/LuaFunction.h>
#include <Urho3D/LuaScript/LuaScript.h>

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
    // ResourceCache* cache = GetSubsystem<ResourceCache>();
    // cache->GetResource<LuaFile>("LuaScripts/01_HelloWorld.lua");

    LuaScript* script = new LuaScript(context_);
    context_->RegisterSubsystem(script);

    script->ExecuteFile("LuaScripts/01_HelloWorld.lua");
    LuaFunction* start = script->GetFunction("Start");
    start->BeginCall();
    start->EndCall();    
}

void Game::Stop()
{

}

URHO3D_DEFINE_APPLICATION_MAIN(Game)
