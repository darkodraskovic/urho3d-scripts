#ifndef __FACTORY_H_
#define __FACTORY_H_

#pragma once

#include <Urho3D/Core/Object.h>
#include <Urho3D/Core/Context.h>

using namespace Urho3D;

class Factory : public Object
{
    URHO3D_OBJECT(Factory, Object);

public:
    Factory (Context* context);
};

#endif // #ifndef __FACTORY_H_
