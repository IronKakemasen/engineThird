#include "PrimitiveMeshCommon.h"
#include <assert.h>

void PrimitiveMeshCommon::Init(uint16_t kMaxDraw_, UINT vertexCnt_, UINT indexCnt_)
{
	vertexCnt = vertexCnt_;
	indexCnt = indexCnt_;
	materialBuffer.resize(kMaxDraw_);
	worldMatrixBuffer.resize(kMaxDraw_);
	wvpMatrixBuffer.resize(kMaxDraw_);
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

