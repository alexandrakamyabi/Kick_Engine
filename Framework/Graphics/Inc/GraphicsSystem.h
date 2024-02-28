#include "GraphicsType_D3D11.h"
#define D3D11

namespace Kick_Engine::Graphics
{
	class GraphicsSystem final
	{
	public:
		static void StaticInitialize(HWND window, bool fullscreen);
		static void StaticTerminate();
#ifdef D3D11
		static Graphics_D3D11* Get();
#else
		static GraphicsType* Get();
#endif

	private:
		static LRESULT CALLBACK GraphicsSystemMessageHandler(HWND window, UINT message, WPARAM wParam, LPARAM lParam);
	};
}