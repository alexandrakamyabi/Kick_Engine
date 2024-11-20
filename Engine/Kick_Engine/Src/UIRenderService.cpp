#include "Precompiled.h"
#include "UIRenderService.h"

#include "UIComponent.h"
using namespace Kick_Engine;
using namespace Kick_Engine::Graphics;

void UIRenderService::Initialize()
{	 
}	 
	 
void UIRenderService::Terminate()
{	 
	mUIComponents.clear();
}	 
	 
void UIRenderService::Update(float deltaTime)
{	 
	for (UIComponent* uiComponent : mUIComponents)
	{
		uiComponent->Update(deltaTime);
	}
}	 
	 
void UIRenderService::Render()
{	 
	UISpriteRenderer::Get()->BeginRender();
	for (UIComponent* uiComponent : mUIComponents)
	{
		uiComponent->Render();
	}
	UISpriteRenderer::Get()->EndRender();
}	 
	 
void UIRenderService::Register(UIComponent* uiComponent)
{	 
	auto iter = std::find(mUIComponents.begin(), mUIComponents.end(), uiComponent);
	if (iter == mUIComponents.end())
	{
		mUIComponents.push_back(uiComponent);
	}
}	 
	 
void UIRenderService::Unregister(UIComponent* uiComponent)
{
	auto iter = std::find(mUIComponents.begin(), mUIComponents.end(), uiComponent);
	if (iter != mUIComponents.end())
	{
		mUIComponents.erase(iter);
	}
}
