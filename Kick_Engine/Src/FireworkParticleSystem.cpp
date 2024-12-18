#include "Precompiled.h"
#include "FireworkParticleSystem.h"
#include "EventManager.h"

using namespace Kick_Engine;
using namespace Kick_Engine::Graphics;
using namespace Kick_Engine::Kick_Math;


void Kick_Engine::FireworkParticle::SetparentId(uint32_t id)
{
    mParentId = id;
}

void FireworkParticle::Update(float deltaTime)
{
    if (mLifeTime > 0.0f)
    {
        Particle::Update(deltaTime);
        if (mLifeTime < 0.0f)
        {
            OnDeath();
        }
    }
}

void FireworkParticle::OnDeath()
{
    FireworkExplodeEvent feEvent;
    feEvent.fireworkId = mParentId;
    feEvent.position = mTransform.position;
    EventManager::Broadcast(&feEvent);
}

static uint32_t gFireworkId = 0;
FireworkParticleSystem::FireworkParticleSystem()
    : mUniqueId(++gFireworkId)
{
}

void FireworkParticleSystem::Terminate()
{
    ParticleSystem::Terminate();
    for (auto& ps : mExplosionEffects)
    {
        ps->Terminate();
    }
}

void FireworkParticleSystem::Update(float deltaTime)
{
    ParticleSystem::Update(deltaTime);
    for (auto& ps : mExplosionEffects)
    {
        ps->Update(deltaTime);
    }
}

void FireworkParticleSystem::SetCamera(const Graphics::Camera& camera)
{
    ParticleSystem::SetCamera(camera);
    for (auto& ep : mExplosionEffects)
    {
        ep->SetCamera(camera);
    }
}

void FireworkParticleSystem::InitializeParticles(uint32_t count)
{
    mParticleIndexes.resize(count);
    mParticles.resize(count);
    for (uint32_t i = 0; i < count; ++i)
    {
        mParticleIndexes[i] = i;
        mParticles[i] = std::make_unique<FireworkParticle>(mUniqueId);
        mParticles[i]->Initialize();
    }

    ParticleSystemInfo info;
    info.spawnDelay = 0.0f;
    info.systemLifeTime = 0.0f;
    info.minParticlePerEmit = 20;
    info.maxParticlePerEmit = 30;
    info.minSpawnAngle = -180.0f * 3.141592 / 180.0f;
    info.maxSpawnAngle = 180.0f * 3.141592 / 180.0f;
    info.minSpeed = 5.0f;
    info.maxSpeed = 10.0f;
    info.minLifeTime = 0.5f;
    info.maxLifeTime = 1.0f;
    info.minStartColor = Colors::MediumVioletRed;
    info.maxStartColor = Colors::Yellow;
    info.minEndColor = Colors::White;
    info.maxEndColor = Colors::LightYellow;
    info.minStartScale = Kick_Math::Vector3::One;
    info.maxStartScale = Kick_Math::Vector3::One;
    info.minEndScale = Kick_Math::Vector3::Zero;
    info.maxEndScale = Kick_Math::Vector3::Zero;
    info.maxParticles = 50;
    info.particleTextureId = TextureManager::Get()->LoadTexture("Images/bullet2.png");

    const uint32_t maxExplosionEffects = 10;
    mExplosionEffects.resize(maxExplosionEffects);
    for (uint32_t i = 0; i < maxExplosionEffects; ++i)
    {
        mExplosionEffects[i] = std::make_unique<ParticleSystem>();
        mExplosionEffects[i]->Initialize(info);
    }

    EventManager::Get()->AddListener(EventType::FireworkExplode, std::bind(&FireworkParticleSystem::OnExplosionEvent, this, std::placeholders::_1));
}

void FireworkParticleSystem::OnExplosionEvent(const Event* event)
{
    FireworkExplodeEvent* feEvent = (FireworkExplodeEvent*)event;
    if (feEvent->fireworkId == mUniqueId)
    {
        auto& nextPS = mExplosionEffects[mNextAvailableEffect];
        mNextAvailableEffect = (mNextAvailableEffect + 1) % mExplosionEffects.size();

        nextPS->SetPosition(feEvent->position);
        nextPS->SpawnParticles();
    }
}
