#pragma once
#include "ModelBehavior.h"
#include "../../utilities/Json/Json.h"

class PlayerModel :public ModelBehavior
{

	void Load();
	void Idle();
	void Run();
	void IdleInGame();

	float idleDelta = 0.0f;
	float runDelta = 0.0;
	Counter headRotateCnt;
public:

	void Save();

	std::unique_ptr<ModelSimple> head;
	std::unique_ptr<ModelSimple> body;
	std::unique_ptr<ModelSimple> hand_L;
	std::unique_ptr<ModelSimple> hand_R;
	std::unique_ptr<ModelSimple> leg_L;
	std::unique_ptr<ModelSimple> leg_R;
	std::unique_ptr<ModelSimple> cannon;

	std::vector<ModelSimple*> models;

	std::string path = "./resource/application/json/PlayerModel/PlayerModel.json";

	PlayerModel();
	virtual void Update(int mode_ = 0, float count_ = 0.0f)override;
	virtual void Draw(Matrix4* vpMat_)override;
	virtual void Init(Transform* gameObjectTrans_)override;
	virtual void Reset()override;

};

