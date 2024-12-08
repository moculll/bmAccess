#pragma once
#include <map>
#pragma warning(push)
#pragma warning(disable: 4309)
#pragma warning(disable: 4369)
#pragma warning(disable: 4099)
#pragma warning(disable: 4244)
#pragma warning(disable: 4018)
#pragma warning(disable: 4267)
#pragma warning(disable: 4390)
#pragma warning(disable: 4244)
#pragma warning(disable: 4018)
#include "SDK.hpp"
#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>
#pragma warning(pop)
namespace CommonData {

enum class event_t {
    EVENT_NONE = 0,
    EVENT_PLAYER_INFO = 1 << 0,
    EVENT_PLAYER_LOCATION = 1 << 1,
    EVENT_PLAYER_LOCATION_SET = 1 << 2,
    EVENT_PLAYER_HP_SET = 1 << 3,
    EVENT_ENEMY_MAP = 1 << 4,
    EVENT_GAMEINITED_RESULT = 1 << 5,
    EVENT_SPEAKERINFO = 1 << 6,
    EVENT_LEVELINFO = 1 << 7,
};


enum class mmap_t {
    LYS_paintingworld_01 = 31, // 如意画轴-六六村
    HFS01_PersistentLevel = 10, // 黑风山
    HFS01_Old_GYCY_YKX_PersistentLevel = 11, // 隐·旧观音禅院
    HFS_WoodDragon = 12, // 黑风山-尺木间
    HFM02_PersistentLevel = 20, // 黄风岭
    HFM_DuJiaoXian_Persist = 25, // 隐·斯哈里国
    HFM_DustDragon_01 = 24, // 黄风岭-藏龙洞
    LYS_PersistentLevel = 30, // 小西天
    PSD_PersistentLevel = 40, // 盘丝岭
    ZYS01_persistentlevel = 80, // 隐·紫云山
    HYS_PersistentLevel = 50, // 火焰山
    BYS_persistentlevel = 98, // 花果山
    BSD02_persistentlevel = 70 // 隐·壁水洞
};


bool operator | (event_t a, event_t b) {
    return (static_cast<int>(a) | static_cast<int>(b));
}

bool operator & (event_t a, event_t b) {
    return (static_cast<int>(a) & static_cast<int>(b));
}

struct playerInfo_t {
    float playerHp;
    float playerMp;
    float playerFreeze;
    float playerBurn;
    float playerPoison;
    float playerThunder;
    float playerBloodButton;
    float playerEnergy;
    float playerStamina;
    float playerStaminaRecover;

};

struct enemyInfo_t {
    float playerHp;
    float playerMp;
    float playerFreeze;
    float playerBurn;
    float playerPoison;
    float playerThunder;
    float playerBloodButton;
    float playerEnergy;
    float playerStamina;
    float playerStaminaRecover;
    float enemyDelta;
};

struct labelSpeakerInfo_t {
    wchar_t label[100];
    uint16_t length;
};

struct levelInfo_t {
    int levelId;
};

struct gameInfo_t {
    event_t event;
    
    union {
        playerInfo_t playerInfo;
        SDK::FVector playerLocation;
        SDK::FVector targetPlayerLocation;
        enemyInfo_t enemyInfo;
        int gameInited;
        labelSpeakerInfo_t speakerInfo;
        levelInfo_t levelInfo;
    };
    ~gameInfo_t() {

    }
    gameInfo_t()
    {
        /* we don't have a vtable, so just make it empty */
        memset(this, 0, sizeof(gameInfo_t)); 
    }

	gameInfo_t(event_t _event)
    {
        this->event = _event;
        if (_event == event_t::EVENT_PLAYER_INFO) {
            this->playerInfo = { 0 };
        }
        else if (_event == event_t::EVENT_PLAYER_LOCATION_SET) {
            this->targetPlayerLocation = { 0, 0, 0 };
        }
        else if (_event == event_t::EVENT_PLAYER_LOCATION){
            this->playerLocation = { 0, 0, 0 };
        }
    }

    

};

inline static gameInfo_t infoBuffer;
inline static gameInfo_t enemyInfo;
inline static gameInfo_t locationBuffer;
inline static gameInfo_t config;
inline static gameInfo_t gameStatus;
inline static gameInfo_t speakerInfo;
inline static gameInfo_t levelInfoBuffer;
} /* CommonData */