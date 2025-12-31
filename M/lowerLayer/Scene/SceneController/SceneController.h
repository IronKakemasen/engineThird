#pragma once
#include "../../../utilities/benriTemplateFunc/benriTempFunc.h"
#include "./RunSpeedChanger/RunSpeedChanger.h"
#include "../FwdScenes.h"

class SceneController
{
public:
	enum SceneType
	{
		kSample,
		kInGame,
		kTitle,
		kCount
	};

private:
	std::unique_ptr<SampleScene> sampleScene;
	std::unique_ptr<InGameScene> inGameScene;
	std::unique_ptr<TitleScene> titleScene;

	//現在稼働しているシーン
	SceneType runningScene;
	//すべてのシーン
	SceneBehavior* allScene[SceneType::kCount];
	//処理間隔を調整する
	RunSpeedChanger runSpeedChanger;

public:
	void Update();
	void Init();

private:
	//稼働するシーンを切り替える
	void ChangeScene(SceneType startSceneType_);
	//シーンをインスタンス化する
	void InstantiateScenes();
	//シーンをセットする
	void SetScenesToArray();

};

