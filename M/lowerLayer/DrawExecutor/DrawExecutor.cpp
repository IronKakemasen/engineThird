#include "DrawExecutor.h"
#include "../math/matrix/matrix.h"
#include "../engineCore/CommonDrawingSystem/CommonDrawSystem.h"


void DrawExecutor::Register(CommonDrawingSystem* dst_)
{
	drawDataContainer[curIndex] = dst_;

	curIndex++;
}

void DrawExecutor::DrawRegistered(Matrix4* vpMat_)
{
	for (const auto& [id, data] : drawDataContainer) 
	{
		if (data->doDraw)
		{
			data->Draw(vpMat_);
		}
	}
}

