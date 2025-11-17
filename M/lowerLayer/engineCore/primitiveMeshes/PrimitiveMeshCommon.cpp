#include "PrimitiveMeshCommon.h"
#include <assert.h>
#include "../allPipelineSet/pipelineSet/pipelineSet.h"

void PrimitiveMeshCommon::Init(PipelineSet* pipelineSet_, uint16_t kMaxDraw_)
{
	pipelineSet = pipelineSet_;
	kMaxDraw = kMaxDraw_;
}

void PrimitiveMeshCommon::DrawIndexReset()
{
	cur_drawIndex = 0;
}

void PrimitiveMeshCommon::DetectOverDrawing()
{
	assert(cur_drawIndex < kMaxDraw);
}
