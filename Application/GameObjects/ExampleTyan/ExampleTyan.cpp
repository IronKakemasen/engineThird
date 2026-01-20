#include "ExampleTyan.h"

/*

//コリジョンバックテーブルを設定
void ExampleTyan::SetCollisionBackTable()
{
}



void ExampleTyan::Update()
{
	//モデルの更新処理（中身を書いていれば）
	shikoModel->Update();

}

void ExampleTyan::Init()
{
	//モデルの初期化
	shikoModel->Init(&trans);
	shikoModel->model->Getter_Appearance(0)->color = { 200,0,0,255 };

	//identityTableにセットされている通りに、identityを定める
	//タグ、名前、衝突判定マスキング
	SetIdentity(Tag::kExample);
	//円形コリジョンをアタッチ
	SetCircleCollision(1.0f);
	//衝突判定をするかどうか定める
	SwitchCollisionActivation(true);

	//位置
	trans.pos.z = 4.0f;

}

void ExampleTyan::Reset()
{
	//モデルのリセット（中身が書いてあれば）
	shikoModel->Reset();
}

void ExampleTyan::Draw(Matrix4* vpMat_)
{
	//モデルの描画
	shikoModel->Draw(vpMat_);
}


ExampleTyan::ExampleTyan()
{
	//モデルのインスタンス化
	shikoModel.reset(new ShikouteiModel);
}

*/