#include "Enemy.h"
#include "imgui.h"

void Enemy::Update()
{
	//モデルの更新処理
	enemyModel->Update();

}

void Enemy::Init()
{
	// モデルの初期化
	enemyModel->Init(&trans);

	// identityTableにセットされている通りに、identityを定める
	// タグ、名前、衝突判定マスキング
	SetIdentity(Tag::kShikoutei);
	// 矩形コリジョンをアタッチ
	SetRectCollision(1.0f, 1.0f);
	// 衝突判定をするかどうか定める
	SwitchCollisionActivation(true);

	trans.pos.z = 1.0f;
}

void Enemy::Reset()
{
	// モデルのリセット
	enemyModel->Reset();
}

void Enemy::Draw(Matrix4* vpMat_)
{
	// モデルの描画
	enemyModel->Draw(vpMat_);
}

void Enemy::SetCollisionBackTable()
{

}

Enemy::Enemy()
{
	// モデルのインスタンス化
	enemyModel.reset(new ShikouteiModel);
}
