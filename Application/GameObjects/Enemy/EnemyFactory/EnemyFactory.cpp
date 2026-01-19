#include "EnemyFactory.h"

EnemyFactory::EnemyFactory()
{
	//モデルのインスタンス化
	model.reset(new EnemyFactoryModel);
	//必須でない
	auto* appearance = model->model->Getter_Appearance(0);

	appearance->metalic = 0.72f;
	appearance->roughness = 0.4f;
	appearance->color = { 255,0,0,255 };
}

void EnemyFactory::Init()
{
	// モデルの初期化
	model->Init(&trans);

	// identityTableにセットされている通りに、identityを定める
	// タグ、名前、衝突判定マスキング
	SetIdentity(Tag::EnemyFactory);
	// 円形コリジョンをアタッチ
	SetCircleCollision(1.0f);

	// 衝突判定をするかどうか定める
	SwitchCollisionActivation(true);

	// collisionBackToPlayerBulletの初期化
	collisionBackToPlayerBullet.Init(this);
}

void EnemyFactory::Update()
{
	model->Update();
}

void EnemyFactory::Draw(Matrix4 * vpMat_)
{
	//モデルの描画
	model->Draw(vpMat_);
}


void EnemyFactory::SetCollisionBackTable()
{
	// タグ：PlayerBulletと衝突したときのコリジョンバックを登録
	SetCollisionBack(Tag::PlayerBullet, collisionBackToPlayerBullet);
}

void EnemyFactory::CollisionBackToPlayerBullet::operator()()
{
	me->SetStatus(Status::kInActive);
}


void EnemyFactory::Reset()
{
	//モデルのリセット（中身が書いてあれば）
	model->Reset();
}

