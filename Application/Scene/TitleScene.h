#pragma once
#include "../../M/lowerLayer/Scene/SceneBehavior/SceneBehavior.h"

class TitleScene final : public SceneBehavior
{
public:
	TitleScene();

	virtual void Update() override;
	virtual void Draw() override;
	virtual void Reset() override;
	virtual void Debug() override;

private:

	virtual void Instantiate() override;
	virtual void Init() override;

};

