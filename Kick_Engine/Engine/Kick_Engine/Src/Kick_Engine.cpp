#include "Precompiled.h"
#include "Kick_Engine.h"

Kick_Engine::App& Kick_Engine::MainApp()
{
	static App sApp;
	return sApp;
}