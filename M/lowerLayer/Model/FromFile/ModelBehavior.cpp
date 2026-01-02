#include "ModelBehavior.h"

ModelBehavior::ModelBehavior()
{
}

void ModelBehavior::MakeAllPartsBeChildren(Transform* gameObject_)
{
	auto appearance = model->Getter_Appearance()->begin();
	for (; appearance != model->Getter_Appearance()->end(); ++appearance)
	{
		appearance->trans.BeChildren(gameObject_);
	}
}
