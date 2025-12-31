#include "LightManager.h"
#include "../../Buffer/StructuredBuffer/PointLightStructuredBuffer/PointLightStructuredBuffer.h"
#include "../../Buffer/constantBuffer/DirectionalLightBuffer/DirectionalLightBuffer.h"
#include "../../../../commonVariables.h"


void LightManager::Update()
{	
	int sum = (int)pointLights.size();
	for (int i = 0; i < sum; ++i)
	{
		if (!pointLights[i]->IsActive())
		{
			continue;
		}

		pointLights[i]->Update();
	}

	directionalLight->Update();

	Batch();

}


LightManager::LightManager()
{
	pointLightID = 0;
}

void LightManager::Init(ExclusiveDraw* exclusiveDraw_, ID3D12Device* device_,
	StructuredBufferSrvCreator* srvCreator_)
{
	static bool onlyOnce = 1;
	if (onlyOnce)
	{
		lightCreator.Init(exclusiveDraw_, device_, srvCreator_);
		Fetch();

		int sum = (int)pointLights.size();
		for (int i = 0; i < sum; ++i)
		{
			pointLights[i]->Init();
		}

		directionalLight->Init();

		onlyOnce = 0;
	}
}

void LightManager::Fetch()
{
	directionalLight = lightCreator.Getter_DirLight();
	auto* pLightContainer = lightCreator.Getter_PointLightContainer();
	pointLightStructuredBuffer = lightCreator.Getter_PointLightStructuredBuffer();
	dirLightBuffer = lightCreator.Getter_DirLightBuffer();

	for (auto itr = pLightContainer->begin(); itr != pLightContainer->end(); ++itr)
	{
		pointLights.emplace_back((*itr).get());
	}
}

DirectionalLight* LightManager::ExportDirectionalLight()
{
	return directionalLight;
}

PointLight* LightManager::ExportPointLight()
{
	auto* pLightContainer = lightCreator.Getter_PointLightContainer();
	int limit = (int)pLightContainer->size();
	assert(pointLightID < limit);

	return pointLights[pointLightID++];
}

void LightManager::Batch()
{
	//PointLights
	int sum = (int)pointLights.size();
	for (int i = 0; i < sum; ++i)
	{
		auto *para = pointLights[i]->Getter_Para();
		pointLightStructuredBuffer->pLight.buffMap[i].isActive = para->isActive;

		if (!para->isActive)
		{
			continue;
		}

		Vector3 color_ = para->color * CommonV::inv_255;
		float invsqrtRadius = 1.0f / (para->invSqrRadius * para->invSqrRadius);

		pointLightStructuredBuffer->pLight.buffMap[i].color = color_;
		pointLightStructuredBuffer->pLight.buffMap[i].intensity = para->intensity;
		pointLightStructuredBuffer->pLight.buffMap[i].pos = para->pos;
		pointLightStructuredBuffer->pLight.buffMap[i].invSqrRadius = invsqrtRadius;
	}

	//DirectionalLight
	auto* para = directionalLight->Getter_Para();
	Vector3 color_ = para->color * CommonV::inv_255;

	dirLightBuffer->dirLight.buffMap->color = color_;
	dirLightBuffer->dirLight.buffMap->intensity = para->intensity;
	dirLightBuffer->dirLight.buffMap->pos = para->pos;
	dirLightBuffer->dirLight.buffMap->isActive = para->isActive;
}
