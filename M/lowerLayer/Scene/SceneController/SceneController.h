#pragma once
#include "../../../utilities/benriTemplateFunc/benriTempFunc.h"
#include "./RunSpeedChanger/RunSpeedChanger.h"
#include "../FwdScenes.h"

class SceneController
{
public:
	enum SceneType
	{
		kShikouteiScene,
		kInGame,
		kTitle,
		kCount
	};

private:
	std::unique_ptr<ShikouteiScene> shikoScene;

	//現在稼働しているシーン
	SceneType runningScene;
	//すべてのシーン
	SceneBehavior* allScene[SceneType::kCount];
	//処理間隔を調整する
	RunSpeedChanger runSpeedChanger;

#ifdef _DEBUG
	struct ForDebug
	{
		//グリッド線を描画するかどうか
		bool doDrawGridLine = true;
	};

	ForDebug forDebug;
#endif // _DEBUG


public:
	void Update();
	void Init();
	void Reset();
	SceneController();

private:
	//稼働するシーンを切り替える
	void ChangeScene(SceneType startSceneType_);
	//シーンをインスタンス化する
	void InstantiateScenes();
	//シーンをセットする
	void SetScenesToArray();
	std::string GetName();
	void Debug();


};

