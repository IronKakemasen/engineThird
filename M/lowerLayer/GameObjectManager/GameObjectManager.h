#pragma once
#include <vector>

struct Matrix4;
struct GameObject;

class GameObjectManager
{
	std::vector< GameObject* > objContainer;
	int createNum = 0;
	//ゲームオブジェクトすべての当たり判定をとる
	void ChackAllCollision(GameObject* thisObj_);

public:
	void Init();
	void Update();
	void Render(Matrix4* vpMat_);
	void Reset();
	void Debug();

	template<typename... objPointer>
	void RegisterForContainer(objPointer... pointers_)
	{
		uint8_t length = sizeof...(pointers_);
		GameObject* pointers[] = { pointers_... };

		for (int i = 0; i < length; i++)
		{
			pointers[i]->SetNumber(createNum++);
			objContainer.emplace_back(pointers[i]);
		}
	}

	void RegisterForContainer(GameObject* dst_);
};

