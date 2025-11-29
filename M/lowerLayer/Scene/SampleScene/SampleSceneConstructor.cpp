#include "SampleScene.h"
#include "../../engineCore/Render/CommonDrawingSystem/CommonDrawSystem.h"

SampleScene::SampleScene()
{
	Instantiate();
	Init();
}

void SampleScene::Instantiate()
{
	triangle.reset(new MTriangle);
	quad.reset(new MQuad);
	//particles.reset(new TestParticle);
}

void SampleScene::Init()
{
	mainCamera->trans.translate = { 0.0f,0.0f,-1.0f };
	triangle->Initialize(1.0f, 1.0f, {}, M::GetInstance()->GetTexIndex(TextureTag::kWhite2x2));
	quad->Initialize(1.0f, 1.0f, {}, M::GetInstance()->GetTexIndex(TextureTag::kWhite2x2));
	//particles->Init();

	RegisterForDrawExecutor(quad.get());
	RegisterForDrawExecutor(triangle.get());

}
