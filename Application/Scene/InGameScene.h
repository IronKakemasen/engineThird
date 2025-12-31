#pragma once
#include "../../M/lowerLayer/Scene/SceneBehavior/SceneBehavior.h"

class InGameScene final : public SceneBehavior
{
public:
	InGameScene();

	virtual void Update() override;
	virtual void Draw() override;
	virtual void Reset() override;
	virtual void Debug() override;

private:

	virtual void Instantiate() override;
	virtual void Init() override;

};

