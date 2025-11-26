#include "DrawExecutor.h"
#include "../math/matrix/matrix.h"
#include "../engineCore/CommonDrawingSystem/CommonDrawSystem.h"


void DrawExecutor::Register(CommonDrawingSystem* dst_)
{
	drawDataContainer[curIndex] = dst_;

	curIndex++;
}

void DrawExecutor::Setter_ViewProjMat(Matrix4* viewProjectionMatrix_)
{
	viewProjectionMatrix = viewProjectionMatrix_;
}

void DrawExecutor::DrawRegistered()
{
	for (const auto& [id, data] : drawDataContainer) 
	{
		if (data->doDraw)
		{
			data->Draw(viewProjectionMatrix);
		}
	}
}

