#include "ParticleMesh2DCommon.h"
#include <assert.h>

ParticleMesh2DCommon::ParticleMesh2DCommon()
{
	vertexCnt = 4;
	indexCnt = 6;
}

void ParticleMesh2DCommon::Init(uint16_t kMaxDraw_, float width_, float height_)
{
	kMaxDraw = kMaxDraw_;
	width = width_;
	height = height_;


}



void ParticleMesh2DCommon::DetectOverDrawing(int sum_draw_)
{
	assert(sum_draw_ <= kMaxDraw);

}
