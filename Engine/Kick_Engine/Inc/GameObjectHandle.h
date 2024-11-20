#pragma once

namespace Kick_Engine
{
	class GameObjectHandle
	{
	public:
		~GameObjectHandle() = default;

	private:
		friend class GameWorld;
		int mIndex = -1;
		int mGeneration = -1;
	};
}