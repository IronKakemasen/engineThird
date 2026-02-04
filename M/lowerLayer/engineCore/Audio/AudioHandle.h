#pragma once
#include <array>
#include <string>
#include <memory>

// 音声ID
enum class AudioID
{
    // BGM
    bgm,
    AllyChain,
    AllyExplode,
    AllySet,
    AllySpawn,
    BulletPowerup,
    Cansel01,
    CountDown,
    DestroyEnemyObject,
    EnemyDamage,
    FactorySpawn,
    GameClear01,
    GameStart,
    ObjectExplode,
    OptionCansel,
    PauseButton,
    PauseCursol,
    PlayerShot,
    PlayerTowerDamage,
    SelectNegative,
    SelectPositive,

    count
};

// AudioIDとパスを紐付け
struct AudioDefinition
{
    AudioID id;
    const wchar_t* path;
};

class AudioHandle
{
public:
    static void Initialize();
    static int Get(AudioID id);  // AudioPlayerが管理する配列インデックスを返す

private:
    static constexpr std::array<AudioDefinition, static_cast<size_t>(AudioID::count)> audioDefinitions_ =
    {
        {
            { AudioID::bgm, L"resource/application/Sound/BGM/InGame/audiostock_199313.mp3" },
            { AudioID::AllyChain, L"resource/application/Sound/SE/InGame/AllyChain.mp3" },
            { AudioID::AllyExplode, L"resource/application/Sound/SE/InGame/AllyExplode.mp3" },
            { AudioID::AllySet, L"resource/application/Sound/SE/InGame/AllySet.mp3" },
            { AudioID::AllySpawn, L"resource/application/Sound/SE/InGame/AllySpawn.mp3" },
            { AudioID::BulletPowerup, L"resource/application/Sound/SE/InGame/BulletPowerup.mp3" },
            { AudioID::Cansel01, L"resource/application/Sound/SE/InGame/Cansel01.mp3" },
            { AudioID::CountDown, L"resource/application/Sound/SE/InGame/CountDown.mp3" },
            { AudioID::DestroyEnemyObject, L"resource/application/Sound/SE/InGame/DestroyEnemyObject.mp3" },
            { AudioID::EnemyDamage, L"resource/application/Sound/SE/InGame/EnemyDamage.mp3" },
            { AudioID::FactorySpawn, L"resource/application/Sound/SE/InGame/FactorySpawn.mp3" },
            { AudioID::GameClear01, L"resource/application/Sound/SE/InGame/GameClear01.mp3" },
            { AudioID::GameStart, L"resource/application/Sound/SE/InGame/GameStart.mp3" },
            { AudioID::ObjectExplode, L"resource/application/Sound/SE/InGame/ObjectExplode.mp3" },
            { AudioID::OptionCansel, L"resource/application/Sound/SE/InGame/OptionCansel.mp3" },
            { AudioID::PauseButton, L"resource/application/Sound/SE/InGame/PauseButton.mp3" },
            { AudioID::PauseCursol, L"resource/application/Sound/SE/InGame/PauseCursol.mp3" },
            { AudioID::PlayerShot, L"resource/application/Sound/SE/InGame/PlayerShot.mp3" },
            { AudioID::PlayerTowerDamage, L"resource/application/Sound/SE/InGame/PlayerTowerDamage.mp3" },
            { AudioID::SelectNegative, L"resource/application/Sound/SE/InGame/SelectNegative.mp3" },
            { AudioID::SelectPositive, L"resource/application/Sound/SE/InGame/SelectPositive.mp3" },

        }

    };

    static std::array<int, static_cast<size_t>(AudioID::count)> audioIndices_; // AudioPlayer内のID
    static bool initialized_;
};
