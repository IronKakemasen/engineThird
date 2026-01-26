#include "PostEffects.h"
#include "../engineCore/textureDataManager/textureDataManager.h"
#include "../../M.h"


PostEffects::Bloom::Bloom(TextureDataManager* textureDataManager_, int numRequired_) :
	OffScreen(textureDataManager_, numRequired_) {
}

void PostEffects::Bloom::Update()
{

}

void PostEffects::Bloom::Init()
{

}


PostEffects::NoEffection::NoEffection(TextureDataManager* textureDataManager_, int numRequired_) :
	OffScreen(textureDataManager_, numRequired_) {
}

void PostEffects::NoEffection::Update()
{

}

void PostEffects::NoEffection::Init()
{
	
	shaderSetIndex = M::GetInstance()->
		GetShaderSetIndexFromFileName("NoEffection.VS", "NoEffection.PS");
}

PostEffects::GreyScale::GreyScale(TextureDataManager* textureDataManager_, int numRequired_) :
	OffScreen(textureDataManager_, numRequired_) {
}

void PostEffects::GreyScale::Update()
{

}

void PostEffects::GreyScale::Init()
{
	shaderSetIndex = M::GetInstance()->
		GetShaderSetIndexFromFileName("MonoChrome.VS", "MonoChrome.PS");

}

