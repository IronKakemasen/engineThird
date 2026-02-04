#pragma once
#include "Sprite.h"
#include "../../M/utilities/Counter/Counter.h"

class DamageDisplay
{
	class DamageNum
	{
		Matrix4* vpMat;
		int onesPlace = 0;
		int tensPlace = 0;
		Counter cnt;
		Vector3 world;
		Vector3 moveOffset;
		Vector2 defaultSize = { 25 , 25 };
		float scale = 1.0f;
		Sprite t;
		Sprite o;
	public:
		bool isActive = false;

		DamageNum();

		void Set(float num_, Vector3 world_,float scale_,Vector3 color_);
		void Update();
		void Draw(Matrix4* pMat_);
		void Init(Matrix4* vpMat_);
	};

	int const kMaxGenerate = 600;
	std::vector<DamageNum> damageNumSprites;

public:
	void Update();
	void Draw(Matrix4* pMat_);
	void Activate(float num_, Vector3 world_, float scale_, Vector3 color_);
	void Init(Matrix4* vpMat_);
	DamageDisplay();
	static DamageDisplay* Get();
};

