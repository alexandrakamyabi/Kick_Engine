#pragma once

#include "Component.h"

namespace Kick_Engine
{
	class SoundEffectComponent final : public Component
	{
	public:
		SET_TYPE_ID(ComponentId::SoundEffect);

		void Initialize() override;
		void Terminate() override;
		void Deserialize(const rapidjson::Value& value) override;

		void DebugUI() override;

		void Play();
		void Stop();

	private:
		std::string mFileName;
		bool mLooping = false;
		Audio::SoundId mSoundId;
	};
}