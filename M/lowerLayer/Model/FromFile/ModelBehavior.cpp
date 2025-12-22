#include "ModelBehavior.h"

ModelBehavior::ModelBehavior()
{
	appearance.shaderSetIndex = M::GetInstance()->
		GetShaderSetIndexFromFileName("ModelSimple.VS", "ModelSimple.PS");
}
