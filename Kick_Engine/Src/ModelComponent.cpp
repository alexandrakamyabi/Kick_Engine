#include "Precompiled.h"
#include "ModelComponent.h"

using namespace Kick_Engine;
using namespace Kick_Engine::Graphics;

void ModelComponent::Initialize()
{
	ModelManager* mm = ModelManager::Get();
	mModelId = mm->GetModelId(mFileName);
	if (mm->GetModel(mModelId) == nullptr)
	{
		mModelId = mm->LoadModel(mFileName);
		for (const std::string& fileName : mAnimationFileNames)
		{
			mm->AddAnimation(mModelId, fileName);
		}
	}

	ASSERT(mm->GetModel(mModelId) != nullptr, "ModelComponent: model is null");
	RenderObjectComponent::Initialize();
}

void ModelComponent::Terminate()
{
	RenderObjectComponent::Terminate();
}

void ModelComponent::Deserialize(const rapidjson::Value& value)
{
	RenderObjectComponent::Deserialize(value);
	if (value.HasMember("FileName"))
	{
		mFileName = value["FileName"].GetString();
	}
	if (value.HasMember("Animations"))
	{
		mAnimationFileNames.clear();
		auto animations = value["Animations"].GetArray();
		for (auto& animation : animations)
		{
			mAnimationFileNames.push_back(animation.GetString());
		}

	}
}

Graphics::ModelId Kick_Engine::ModelComponent::GetModelId() const
{
	return mModelId;
}

const Graphics::Model& ModelComponent::GetModel() const
{
	return *ModelManager::Get()->GetModel(mModelId);
}
