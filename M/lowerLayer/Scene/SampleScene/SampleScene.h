#pragma once
#include "../SceneBehavior/SceneBehavior.h"
#include "../../Particle/2D/TestParticle/TestParticle.h"

class SampleScene final : public SceneBehavior
{
public:
	SampleScene();

	std::unique_ptr<MTriangle> triangle;
	std::unique_ptr<MQuad> quad;
	std::unique_ptr<TestParticle> particles;


	virtual void Update() override;
	virtual void Draw() override;
	virtual void Reset() override;
	virtual void Debug() override;

protected:

	virtual void Instantiate() override;
	virtual void Init() override;

};

