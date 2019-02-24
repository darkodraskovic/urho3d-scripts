#include "Game.h"

#include <Urho3D/Core/CoreEvents.h>

#include <Urho3D/Input/Input.h>
#include <Urho3D/UI/UI.h>

#include <Urho3D/Graphics/Octree.h>
#include <Urho3D/Resource/ResourceCache.h>
#include <Urho3D/Graphics/StaticModel.h>
#include <Urho3D/Graphics/Light.h>
#include <Urho3D/Graphics/Zone.h>
#include <Urho3D/Graphics/Camera.h>
#include <Urho3D/Graphics/Renderer.h>
#include <Urho3D/Graphics/Viewport.h>
#include <Urho3D/Graphics/Material.h>
#include <Urho3D/Graphics/Model.h>
#include <Urho3D/Graphics/StaticModel.h>
#include <Urho3D/Graphics/VertexBuffer.h>
#include <Urho3D/Graphics/IndexBuffer.h>
#include <Urho3D/Graphics/Geometry.h>

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
    CreateCamera();
    CreateModelFromScratch();
    
    SubscribeToEvent(E_KEYDOWN, URHO3D_HANDLER(Game, HandleKeyDown));
    // Subscribe HandleUpdate() function for processing update events
    SubscribeToEvent(E_UPDATE, URHO3D_HANDLER(Game, HandleUpdate));
}

void Game::Stop()
{

}

void Game::CreateScene()
{
    auto* cache = GetSubsystem<ResourceCache>();

    scene_ = new Scene(context_);

    // Create the Octree component to the scene so that drawable objects can be rendered. Use default volume
    // (-1000, -1000, -1000) to (1000, 1000, 1000)
    scene_->CreateComponent<Octree>();
    
    // Create a Zone for ambient light & fog control
    Node* zoneNode = scene_->CreateChild("Zone");
    auto* zone = zoneNode->CreateComponent<Zone>();
    zone->SetBoundingBox(BoundingBox(-1000.0f, 1000.0f));
    zone->SetFogColor(Color(0.2f, 0.2f, 0.2f));
    zone->SetFogStart(200.0f);
    zone->SetFogEnd(300.0f);    
    
    // Create a directional light
    Node* lightNode = scene_->CreateChild("DirectionalLight");
    lightNode->SetDirection(Vector3(-0.6f, -1.0f, -0.8f)); // The direction vector does not need to be normalized
    auto* light = lightNode->CreateComponent<Light>();
    light->SetLightType(LIGHT_DIRECTIONAL);
    light->SetColor(Color(0.4f, 1.0f, 0.4f));
    light->SetSpecularIntensity(1.5f);
}

void Game::CreateCamera()
{
    // Create the camera
    cameraNode_ = new Node(context_);
    cameraNode_->SetPosition(Vector3(0.0f, 2.0f, -20.0f));
    auto* camera = cameraNode_->CreateComponent<Camera>();
    camera->SetFarClip(300.0f);

    auto* renderer = GetSubsystem<Renderer>();

    // Set up a viewport to the Renderer subsystem so that the 3D scene can be seen
    SharedPtr<Viewport> viewport(new Viewport(context_, scene_, cameraNode_->GetComponent<Camera>()));
    renderer->SetViewport(0, viewport);    
}

void Game::MoveCamera(float timeStep)
{
    // Do not move if the UI has a focused element (the console)
    if (GetSubsystem<UI>()->GetFocusElement())
        return;

    auto* input = GetSubsystem<Input>();

    // Movement speed as world units per second
    const float MOVE_SPEED = 20.0f;
    // Mouse sensitivity as degrees per pixel
    const float MOUSE_SENSITIVITY = 0.1f;

    // Use this frame's mouse motion to adjust camera node yaw and pitch. Clamp the pitch between -90 and 90 degrees
    IntVector2 mouseMove = input->GetMouseMove();
    yaw_ += MOUSE_SENSITIVITY * mouseMove.x_;
    pitch_ += MOUSE_SENSITIVITY * mouseMove.y_;
    pitch_ = Clamp(pitch_, -90.0f, 90.0f);

    // Construct new orientation for the camera scene node from yaw and pitch. Roll is fixed to zero
    cameraNode_->SetRotation(Quaternion(pitch_, yaw_, 0.0f));

    // Read WASD keys and move the camera scene node to the corresponding direction if they are pressed
    if (input->GetKeyDown(KEY_W))
        cameraNode_->Translate(Vector3::FORWARD * MOVE_SPEED * timeStep);
    if (input->GetKeyDown(KEY_S))
        cameraNode_->Translate(Vector3::BACK * MOVE_SPEED * timeStep);
    if (input->GetKeyDown(KEY_A))
        cameraNode_->Translate(Vector3::LEFT * MOVE_SPEED * timeStep);
    if (input->GetKeyDown(KEY_D))
        cameraNode_->Translate(Vector3::RIGHT * MOVE_SPEED * timeStep);
}

void Game::CreateModelFromScratch()
{
    // Finally create one model (pyramid shape) and a StaticModel to display it from scratch
    // Note: there are duplicated vertices to enable face normals. We will calculate normals programmatically
    const unsigned numVertices = 18;

    float vertexData[] = {
                          // Position             Normal
                          0.0f, 0.5f, 0.0f,       0.0f, 0.0f, 0.0f,
                          0.5f, -0.5f, 0.5f,      0.0f, 0.0f, 0.0f,
                          0.5f, -0.5f, -0.5f,     0.0f, 0.0f, 0.0f,

                          0.0f, 0.5f, 0.0f,       0.0f, 0.0f, 0.0f,
                          -0.5f, -0.5f, 0.5f,     0.0f, 0.0f, 0.0f,
                          0.5f, -0.5f, 0.5f,      0.0f, 0.0f, 0.0f,

                          0.0f, 0.5f, 0.0f,       0.0f, 0.0f, 0.0f,
                          -0.5f, -0.5f, -0.5f,    0.0f, 0.0f, 0.0f,
                          -0.5f, -0.5f, 0.5f,     0.0f, 0.0f, 0.0f,

                          0.0f, 0.5f, 0.0f,       0.0f, 0.0f, 0.0f,
                          0.5f, -0.5f, -0.5f,     0.0f, 0.0f, 0.0f,
                          -0.5f, -0.5f, -0.5f,    0.0f, 0.0f, 0.0f,

                          0.5f, -0.5f, -0.5f,     0.0f, 0.0f, 0.0f,
                          0.5f, -0.5f, 0.5f,      0.0f, 0.0f, 0.0f,
                          -0.5f, -0.5f, 0.5f,     0.0f, 0.0f, 0.0f,

                          0.5f, -0.5f, -0.5f,     0.0f, 0.0f, 0.0f,
                          -0.5f, -0.5f, 0.5f,     0.0f, 0.0f, 0.0f,
                          -0.5f, -0.5f, -0.5f,    0.0f, 0.0f, 0.0f
    };

    const unsigned short indexData[] = 
    {
                                        0, 1, 2,
                                        3, 4, 5,
                                        6, 7, 8,
                                        9, 10, 11,
                                        12, 13, 14,
                                        15, 16, 17
    };

    // Calculate face normals now
    for (unsigned i = 0; i < numVertices; i += 3)
        {
            Vector3& v1 = *(reinterpret_cast<Vector3*>(&vertexData[6 * i]));
            Vector3& v2 = *(reinterpret_cast<Vector3*>(&vertexData[6 * (i + 1)]));
            Vector3& v3 = *(reinterpret_cast<Vector3*>(&vertexData[6 * (i + 2)]));
            Vector3& n1 = *(reinterpret_cast<Vector3*>(&vertexData[6 * i + 3]));
            Vector3& n2 = *(reinterpret_cast<Vector3*>(&vertexData[6 * (i + 1) + 3]));
            Vector3& n3 = *(reinterpret_cast<Vector3*>(&vertexData[6 * (i + 2) + 3]));

            Vector3 edge1 = v1 - v2;
            Vector3 edge2 = v1 - v3;
            n1 = n2 = n3 = edge1.CrossProduct(edge2).Normalized();
        }

    SharedPtr<Model> fromScratchModel(new Model(context_));
    SharedPtr<VertexBuffer> vb(new VertexBuffer(context_));
    SharedPtr<IndexBuffer> ib(new IndexBuffer(context_));
    SharedPtr<Geometry> geom(new Geometry(context_));

    // Shadowed buffer needed for raycasts to work, and so that data can be automatically restored on device loss
    vb->SetShadowed(true);
    // We could use the "legacy" element bitmask to define elements for more compact code, but let's demonstrate
    // defining the vertex elements explicitly to allow any element types and order
    PODVector<VertexElement> elements;
    elements.Push(VertexElement(TYPE_VECTOR3, SEM_POSITION));
    elements.Push(VertexElement(TYPE_VECTOR3, SEM_NORMAL));
    vb->SetSize(numVertices, elements);
    vb->SetData(vertexData);

    ib->SetShadowed(true);
    ib->SetSize(numVertices, false);
    ib->SetData(indexData);

    geom->SetVertexBuffer(0, vb);
    geom->SetIndexBuffer(ib);
    geom->SetDrawRange(TRIANGLE_LIST, 0, numVertices);

    fromScratchModel->SetNumGeometries(1);
    fromScratchModel->SetGeometry(0, 0, geom);
    fromScratchModel->SetBoundingBox(BoundingBox(Vector3(-0.5f, -0.5f, -0.5f), Vector3(0.5f, 0.5f, 0.5f)));

    // Though not necessary to render, the vertex & index buffers must be listed in the model so that it can be saved properly
    Vector<SharedPtr<VertexBuffer> > vertexBuffers;
    Vector<SharedPtr<IndexBuffer> > indexBuffers;
    vertexBuffers.Push(vb);
    indexBuffers.Push(ib);
    // Morph ranges could also be not defined. Here we simply define a zero range (no morphing) for the vertex buffer
    PODVector<unsigned> morphRangeStarts;
    PODVector<unsigned> morphRangeCounts;
    morphRangeStarts.Push(0);
    morphRangeCounts.Push(0);
    fromScratchModel->SetVertexBuffers(vertexBuffers, morphRangeStarts, morphRangeCounts);
    fromScratchModel->SetIndexBuffers(indexBuffers);

    Node* node = scene_->CreateChild("FromScratchObject");
    node->SetPosition(Vector3(0.0f, 3.0f, 0.0f));
    auto* object = node->CreateComponent<StaticModel>();
    object->SetModel(fromScratchModel);    
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

    // Move the camera, scale movement with time step
    MoveCamera(timeStep);
}

URHO3D_DEFINE_APPLICATION_MAIN(Game)
