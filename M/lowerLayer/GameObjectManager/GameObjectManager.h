#pragma once
#include <vector>

struct Matrix4;
struct GameObject;

class GameObjectManager
{
	std::vector< GameObject* > objContainer;

public:
	void Init();
	void Update();
	void Render(Matrix4* vpMat_);
	void Reset();

	template<typename... objPointer>
	void RegisterForContainer(objPointer... pointers_)
	{
		uint8_t length = sizeof...(pointers_);
		GameObject* pointers[] = { pointers_... };

		for (int i = 0; i < length; i++)
		{
			objContainer.emplace_back(pointers[i]);
		}
	}

	void RegisterForContainer(GameObject* dst_);


};

