#pragma once
#include <stdint.h>

class PipelineSet;


struct PrimitiveMeshCommon
{
	PipelineSet* pipelineSet = nullptr;
	uint16_t cur_drawIndex = 0;
	uint16_t kMaxDraw = 0;


	void Init(PipelineSet* pipelineSet_, uint16_t kMaxDraw_);
	void DrawIndexReset();
	void DetectOverDrawing();

};

