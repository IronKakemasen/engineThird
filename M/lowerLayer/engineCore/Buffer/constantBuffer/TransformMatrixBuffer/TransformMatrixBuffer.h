#pragma once
#include "../bufferAndMap.h"
#include "../../../Mesh/meshStructure/TransformMatrix/TransformMatrix.h"

struct TransformMatrixBuffer
{
	BufferAndMap<TransformMatrix> matrix;
};

