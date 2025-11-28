#pragma once
#include "../bufferAndMap.h"
#include "../../meshStructure/TransformMatrix/TransformMatrix.h"

struct TransformMatrixBuffer
{
	BufferAndMap<TransformMatrix> matrix;
};

