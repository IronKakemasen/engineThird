#include "InGameConfig.h"
#include "../../utilities/Json/Json.h"
#include "imgui.h"

InGameConfig::InGameConfig()
{}

InGameConfig::~InGameConfig()
{}

void InGameConfig::Load()
{

	Json::LoadParam(path, "/player/MaxHP", playerMaxHP);
	Json::LoadParam(path, "/playerTower/MaxHP", playerTowerMaxHP);
	Json::LoadParam(path, "/enemy/MaxHP", enemyMaxHP);
	Json::LoadParam(path, "/enemyFactory/MaxHP", enemyFactoryMaxHP);
	Json::LoadParam(path, "/enemyTower/MaxHP", enemyTowerMaxHP);
	Json::LoadParam(path, "/player/bullet/lifeTime", playerBulletLifeTime);

	Json::LoadParam(path, "/player/speed", playerSpeed);
	Json::LoadParam(path, "/enemy/speed", enemySpeed);
	Json::LoadParam(path, "/player/bullet/speed", playerBulletSpeed);

	Json::LoadParam(path, "/player/defaultAttackPower1", playerAttack1Power);
	Json::LoadParam(path, "/player/defaultAttackPower2", playerAttack2Power);
	Json::LoadParam(path, "/player/defaultAttackPower3", playerAttack3Power);
	Json::LoadParam(path, "/player/allyPowerBonus", playerAllyPowerBonus);
	Json::LoadParam(path, "/player/allySizeBonus", playerAllySizeBonus);
	Json::LoadParam(path, "/enemy/defaultAttackPower", enemyAttackPower);

	Json::LoadParam(path, "/enemy/spawnInterval", enemySpawnInterval);
	Json::LoadParam(path, "/enemy/knockBackPowerToAlly", enemyKnockBackPowerToAlly);
	Json::LoadParam(path, "/enemy/knockBackPowerToBullet1", enemyKnockBackPowerToBullet1);
	Json::LoadParam(path, "/enemy/knockBackPowerToBullet2", enemyKnockBackPowerToBullet2);
	Json::LoadParam(path, "/enemy/knockBackPowerToBullet3", enemyKnockBackPowerToBullet3);
	Json::LoadParam(path, "/enemy/knockBackPowerToPTower", enemyKnockBackPowerToPlayerTower);

	Json::LoadParam(path, "/player/allyDelayFramesToAlly", allyToAllyDelayFrames);
	Json::LoadParam(path, "/player/allyDelayFramesToPlayer", playerToAllyDelayFrames);
	Json::LoadParam(path, "/player/attackGaugeRecoverSpeed", playerAttackGaugeRecoverSpeed);
	Json::LoadParam(path, "/player/attackGaugeRecoverInterval", playerAttackGaugeRecoverInterval);
}

void InGameConfig::Save()
{
	Json::SaveParam(path, "/player/MaxHP", playerMaxHP);
	Json::SaveParam(path, "/playerTower/MaxHP", playerTowerMaxHP);
	Json::SaveParam(path, "/enemy/MaxHP", enemyMaxHP);
	Json::SaveParam(path, "/enemyFactory/MaxHP", enemyFactoryMaxHP);
	Json::SaveParam(path, "/enemyTower/MaxHP", enemyTowerMaxHP);
	Json::SaveParam(path, "/player/bullet/lifeTime", playerBulletLifeTime);

	Json::SaveParam(path, "/player/speed", playerSpeed);
	Json::SaveParam(path, "/enemy/speed", enemySpeed);
	Json::SaveParam(path, "/player/bullet/speed", playerBulletSpeed);

	Json::SaveParam(path, "/player/attak1Power", playerAttack1Power);
	Json::SaveParam(path, "/player/attak2Power", playerAttack2Power);
	Json::SaveParam(path, "/player/attak3Power", playerAttack3Power);
	Json::SaveParam(path, "/player/allyPowerBonus", playerAllyPowerBonus);
	Json::SaveParam(path, "/player/allySizeBonus", playerAllySizeBonus);
	Json::SaveParam(path, "/enemy/defaultAttackPower", enemyAttackPower);

	Json::SaveParam(path, "/enemy/spawnInterval", enemySpawnInterval);
	Json::SaveParam(path, "/enemy/knockBackPowerToAlly", enemyKnockBackPowerToAlly);
	Json::SaveParam(path, "/enemy/knockBackPowerToBullet1", enemyKnockBackPowerToBullet1);
	Json::SaveParam(path, "/enemy/knockBackPowerToBullet2", enemyKnockBackPowerToBullet2);
	Json::SaveParam(path, "/enemy/knockBackPowerToBullet3", enemyKnockBackPowerToBullet3);
	Json::SaveParam(path, "/enemy/knockBackPowerToPTower", enemyKnockBackPowerToPlayerTower);

	Json::SaveParam(path, "/player/allyDelayFramesToAlly", allyToAllyDelayFrames);
	Json::SaveParam(path, "/player/allyDelayFramesToPlayer", playerToAllyDelayFrames);
	Json::SaveParam(path, "/player/attackGaugeRecoverSpeed", playerAttackGaugeRecoverSpeed);
	Json::SaveParam(path, "/player/attackGaugeRecoverInterval", playerAttackGaugeRecoverInterval);

	Json::Save(path);
}

void InGameConfig::DebugDraw()
{
	ImGui::PushItemWidth(150.0f);

	if (ImGui::Button("Save Config"))
	{
		Save();
	}

	ImGui::Text("---------------------HP----------------------\n");
	ImGui::DragFloat("Player	MaxHP", &playerMaxHP, 1.0f, 0.0f, 100.0f);
	ImGui::DragFloat("PTower	MaxHP", &playerTowerMaxHP, 1.0f, 0.0f, 200.0f);
	ImGui::DragFloat("Enemy		MaxHP", &enemyMaxHP, 1.0f, 0.0f, 100.0f);
	ImGui::DragFloat("EFactory	MaxHP", &enemyFactoryMaxHP, 1.0f, 0.0f, 100.0f);
	ImGui::DragFloat("ETower	MaxHP", &enemyTowerMaxHP, 1.0f, 0.0f, 100.0f);
	ImGui::DragFloat("Bullet	LifeTime", &playerBulletLifeTime, 0.1f, 0.0f, 10.0f);
	ImGui::Text("---------------------Speed--------------------\n");
	ImGui::DragFloat("Player	speed", &playerSpeed, 0.01f, 0.0f, 1.0f);
	ImGui::DragFloat("Enemy		speed", &enemySpeed, 0.01f, 0.0f, 1.0f);
	ImGui::DragFloat("Bullet	speed", &playerBulletSpeed, 0.01f, 0.0f, 5.0f);
	ImGui::Text("---------------------Power--------------------\n");
	ImGui::DragFloat("Player	attack1Power", &playerAttack1Power, 0.1f, 0.0f, 50.0f);
	ImGui::DragFloat("Player	attack2Power", &playerAttack2Power, 0.1f, 0.0f, 50.0f);
	ImGui::DragFloat("Player	attack3Power", &playerAttack3Power, 0.1f, 0.0f, 50.0f);
	ImGui::DragFloat("Player	allyPowerBonus", &playerAllyPowerBonus, 0.1f, 0.0f, 20.0f);
	ImGui::DragFloat("Player	allySizeBonus", &playerAllySizeBonus, 0.01f, 0.0f, 10.0f);
	ImGui::DragFloat("Enemy		attackPower", &enemyAttackPower, 0.1f, 0.0f, 50.0f);
	ImGui::Text("-------------EnemyKnockBackPower--------------\n");
	ImGui::DragFloat("Enemy		toAlly", &enemyKnockBackPowerToAlly, 0.1f, 0.0f, 20.0f);
	ImGui::DragFloat("Enemy 	toBullet1", &enemyKnockBackPowerToBullet1, 0.1f, 0.0f, 20.0f);
	ImGui::DragFloat("Enemy 	toBullet2", &enemyKnockBackPowerToBullet2, 0.1f, 0.0f, 20.0f);
	ImGui::DragFloat("Enemy 	toBullet3", &enemyKnockBackPowerToBullet3, 0.1f, 0.0f, 20.0f);
	ImGui::DragFloat("Enemy 	toPTower", &enemyKnockBackPowerToPlayerTower, 0.1f, 0.0f, 20.0f);
	ImGui::Text("---------------------Player-------------------\n");
	ImGui::DragInt("Ally		A-A delayFrames", &allyToAllyDelayFrames, 1, 0, 120);
	ImGui::DragInt("Ally		P-A delayFrames", &playerToAllyDelayFrames, 1, 0, 120);
	ImGui::DragFloat("Player	attackGaugeRecoverSpeed", &playerAttackGaugeRecoverSpeed, 0.01f, 0.0f, 1.0f);
	ImGui::DragFloat("Player	attackGaugeRecoverInterval", &playerAttackGaugeRecoverInterval, 0.01f, 0.0f, 5.0f);
	ImGui::Text("---------------------Factory-------------------\n");
	ImGui::DragFloat("Enemy		spawnInterval", &enemySpawnInterval, 0.1f, 0.0f, 20.0f);

}