#include "Precompiled.h"
#include "SoundBankComponent.h"

#include "GameObject.h"

using namespace Kick_Engine;
using namespace Kick_Engine::Audio;

void SoundBankComponent::Initialize()
{
    SoundEffectManager* sm = SoundEffectManager::Get();
    for (auto& data : mSoundEffects)
    {
        data.second.soundId = sm->Load(data.second.fileName);
    }
}

void SoundBankComponent::Terminate()
{
    
}

void SoundBankComponent::Deserialize(const rapidjson::Value& value)
{
    if (value.HasMember("SoundEffects"))
    {
        auto soundEffects = value["SoundEffects"].GetObj();
        for (auto& effect : soundEffects)
        {
            SoundEffectData& data = mSoundEffects[effect.name.GetString()];
            if (effect.value.HasMember("FileName"))
            {
                data.fileName = effect.value["FileName"].GetString();
            }
            if (effect.value.HasMember("Looping"))
            {
                data.isLooping = effect.value["Looping"].GetBool();
            }
        }
    }
}

void SoundBankComponent::DebugUI()
{
    std::string playButtonTag = "PlaySound##" + GetOwner().GetName();
    std::string stopButtonTag = "StopSound##" + GetOwner().GetName();
    std::string soundEffectsHeader = "SoundEffects##" + GetOwner().GetName();
    ImGui::Indent();
    if (ImGui::CollapsingHeader(soundEffectsHeader.c_str()))
    {
        for (auto& data : mSoundEffects)
        {
            std::string buttonName = data.first + playButtonTag;
            if (ImGui::Button(buttonName.c_str()))
            {
                Play(data.first);
            }
            ImGui::SameLine();
            buttonName = data.first + stopButtonTag;
            if (ImGui::Button(buttonName.c_str()))
            {
                Stop(data.first);
            }
        }
    }
    ImGui::Unindent();
}

void SoundBankComponent::Play(const std::string& key)
{
    auto data = mSoundEffects.find(key);
    if (data != mSoundEffects.end())
    {
        SoundEffectManager::Get()->Stop(data->second.soundId);
        SoundEffectManager::Get()->Play(data->second.soundId);
    }
}

void SoundBankComponent::Stop(const std::string& key)
{
    auto data = mSoundEffects.find(key);
    if (data != mSoundEffects.end())
    {
        SoundEffectManager::Get()->Stop(data->second.soundId);
    }
}

void SoundBankComponent::StopAll()
{
    SoundEffectManager* sm = SoundEffectManager::Get();
    for (auto data : mSoundEffects)
    {
        sm->Stop(data.second.soundId);
    }
}