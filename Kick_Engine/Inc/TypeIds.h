#pragma once

namespace Kick_Engine
{
    enum class ComponentId
    {
        Invalid,             // Invalid component id
        Transform,           // Transform for component, contains positional data
        Camera,              // Stationary camera information
        FPSCamera,           // Functionality for a camera to move
        TPSCamera,           // A 3rd person camera to track player movement
        Mesh,                // Render a mesh built shape
        Model,               // Renders a Model
        Animator,            // Controls a Model's animation
        RigidBody,           // Adds a rigidbody to a world
        SoundEffect,         // Add a single sound effect to an object
        SoundBank,           // Add an array of sound effects to an object that can be triggered
        UISprite,            // Adds a sprite to the UI
        UIButton,            // Adds a button to the UI
        UIText,              // Adds a text to the UI
        CharacterController, // Adds character movement

        Count
    };

    enum class ServiceId
    {
        Invalid,            // Invalid service id
        Camera,             // Registers and manages focus camera
        Update,             // Registers and updates any component that requires an update
        Render,             // Registers and renders any graphical components
        Physics,            // Registers and updates physics based objects
        UIRender,             // Registers and render UI components

        Count
    };
}

#define SET_TYPE_ID(id)\
    static uint32_t StaticGetTypeId() {return static_cast<uint32_t>(id);}\
    uint32_t GetTypeId() const override {return StaticGetTypeId(); }