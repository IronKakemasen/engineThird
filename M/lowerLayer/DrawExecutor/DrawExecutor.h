#pragma once
#include <vector>
#include <unordered_map>

struct Matrix4;
struct CommonDrawingSystem;

class DrawExecutor
{
	int curIndex = 0;
	Matrix4* viewProjectionMatrix = nullptr;
	std::unordered_map<int , CommonDrawingSystem*> drawDataContainer;

public:
	void Setter_ViewProjMat(Matrix4* viewProjectionMatrix_);
	void Register(CommonDrawingSystem* dst_);
	void DrawRegistered();

};

