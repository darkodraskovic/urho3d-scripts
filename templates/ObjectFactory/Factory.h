#ifndef __FACTORY_H_
#define __FACTORY_H_

#pragma once

#include <Urho3D/Scene/LogicComponent.h>

// All Urho3D classes reside in namespace Urho3D
using namespace Urho3D;

/// Custom logic component
class Factory : public LogicComponent
{
    URHO3D_OBJECT(Factory, LogicComponent);

public:
    /// Construct.
    Factory (Context* context);

    // Called when the component is added to a scene node. Other components may not yet exist. 
    virtual void Start() override;
    
    /// Handle scene update. Called by LogicComponent base class.
    virtual void Update(float timeStep) override;

    void SetRotationSpeed(const float speed);

    //private:
    float rotationSpeed_;
};

#endif // #ifndef __FACTORY_H_
