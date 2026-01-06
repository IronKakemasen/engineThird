#pragma once
#include "../M/lowerLayer/GameObject/GameObjectBehavior.h"

struct CameraPara;

struct InGameCamera
{
private :
	Vector3 const fstLook = { -0.6f,-0.472f,0.646f};
	CameraPara* cameraPara = nullptr;
	Vector3* playerPos = nullptr;
	Vector3 const adjustDir = { 0,0,3.0f};
	Vector3 const adjustPos = { 0,4.0f,-2.5f };
	Counter perfectCnt;

	void Enter();
	void Playable();
	void WhenPerfect();
public:
	void Init(CameraPara* cameraPara_, Vector3* playerPos_);
	void Update();
	void Reset();

};

