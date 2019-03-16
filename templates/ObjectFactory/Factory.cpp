#include <Urho3D/Scene/Scene.h>
#include <Urho3D/DebugNew.h>

#include "Factory.h"

static const StringHash VAR_ROTATESPEED("RotateSpeed");

Factory::Factory(Context* context) :
    LogicComponent(context),
    rotationSpeed_(0.0)
{
    // Only the scene update event is needed: unsubscribe from the rest for optimization
    SetUpdateEventMask(USE_UPDATE);
}

void Factory::Start()
{
    
}

void Factory::SetRotationSpeed(const float speed)
{
    rotationSpeed_ = speed;
}

void Factory::Update(float timeStep)
{
    node_->Roll(rotationSpeed_ * timeStep);
}
