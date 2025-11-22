#pragma once
#include "./lowerLayer/ResourceContainer/ResourceContainer.h"

class TextureDataManager;

class M
{
	//一度だけ初期化
	bool initOnlyOnce = true;
	ResourceContainer resourceContainer;

public:
	static M* GetInstance();
	void Init(TextureDataManager* textureDa2taManager_);

	//テクスチャのインデックスを得る
	int GetTexIndex(TextureTag tag_);


private:

	M() = default;
	~M() = default;

	// コピー・ムーブ禁止
	M(const M&) = delete;
	M& operator=(const M&) = delete;

};

