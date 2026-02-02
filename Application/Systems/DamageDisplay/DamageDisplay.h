#pragma once
#include "Sprite.h"
#include "../../M/utilities/Counter/Counter.h"

class DamageDisplay
{
	struct DamageNum
	{
		static float constexpr kMaxDamage = 10.0f;

		bool isActive = false;
		int onesPlace = 0;
		int tensPlace = 0;
		Counter cnt;

		Sprite t;
		Sprite o;
		DamageNum();

		void Set(float num_, Vector3 world_);
		void Update();
	};

	


};

