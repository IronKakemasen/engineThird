#pragma once
#include <vector>
#include <unordered_map>

struct Matrix4;
struct CommonDrawingSystem;

class DrawExecutor
{
	int curIndex = 0;
	std::unordered_map<int , CommonDrawingSystem*> drawDataContainer;

public:
	void Register(CommonDrawingSystem* dst_);
	void DrawRegistered(Matrix4* vpMat_);

};

