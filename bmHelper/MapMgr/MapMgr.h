#pragma once
#include <memory>
#include "json/json.hpp"

class BmMapMgr {
public:
    BmMapMgr();
    ~BmMapMgr() {}
    bool init(std::string jsonPath);

    void updateCurrentMap(int mapId, double X, double Y, double Z);
private:
    std::shared_ptr<nlohmann::json> mapJsonData;

    struct pointVector_t {
        int X;
        int Y;
        int Z;
    };
    struct levelStorge_t {
        std::string pointName;
        pointVector_t point; 
    };

    std::string currentLevelName;
    std::vector<levelStorge_t> currentLevelStorge;


};