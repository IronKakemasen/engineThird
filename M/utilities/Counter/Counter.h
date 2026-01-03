#pragma once

struct Counter
{
	float count = 0.0f;
	float inv_Time;
	float speed = 1.0f;

	Counter(float performTime_);
	Counter(){}
	void Add(float deltaTime_);
	void Substract(float deltaTime_);
	void Initialize(float sumFrame_);
	bool IsEnd();
	static float GetNormalizedCount(float st_, float end_, float cur_Cnt_);

};

