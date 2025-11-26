#pragma once
#include "../SceneBehavior/SceneBehavior.h"

class SampleScene final : public SceneBehavior
{
public:
	SampleScene();

	std::unique_ptr<MTriangle> triangle;

	virtual void Update() override;
	virtual void Draw() override;
	virtual void Reset() override;
	virtual void Debug() override;

protected:

	virtual void Instantiate() override;
	virtual void Init() override;

};

