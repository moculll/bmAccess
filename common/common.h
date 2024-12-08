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
    EVENT_GAMESTATUS = 1 << 5,
    EVENT_SPEAKERINFO = 1 << 6,
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
struct gameInfo_t {
    event_t event;
    
    union {
        playerInfo_t playerInfo;
        SDK::FVector playerLocation;
        SDK::FVector targetPlayerLocation;
        enemyInfo_t enemyInfo;
        int gameInited;
        labelSpeakerInfo_t speakerInfo;
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
} /* CommonData */