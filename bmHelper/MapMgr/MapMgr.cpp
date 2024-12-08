#include "MapMgr/MapMgr.h"

#include <fstream>
#define DEBUG_PRINT(fmt, ...) \
            do { \
                printf("[MapMgr.cpp][%s.%d]" fmt "\r\n", __func__, __LINE__, ##__VA_ARGS__); \
            } while(0);

using json = nlohmann::json;

BmMapMgr::BmMapMgr() : currentLevelName("未初始化")
{
    mapJsonData = std::make_shared<nlohmann::json>();
    
}


bool BmMapMgr::init(std::string jsonPath)
{

    std::ifstream file(jsonPath);
    if (!file.is_open()) {
        DEBUG_PRINT("Failed to open file: %s", jsonPath.c_str());
        return false;
    }

    try {
        file >> *mapJsonData.get();
    }
    catch (json::parse_error& err) {
        DEBUG_PRINT("JSON parsing error: %s", err.what());
        return false;
    }

    DEBUG_PRINT("jsonFile loaded successful.");

    for (const auto& mapUnit : *mapJsonData.get()) {
        int id = mapUnit["id"];
        int map = mapUnit["map"];
        std::string code = mapUnit["code"];
        std::string name = mapUnit["name"];


        std::vector<int> range_x = mapUnit["range_x"].get<std::vector<int>>();
        std::vector<int> range_y = mapUnit["range_y"].get<std::vector<int>>();
        std::vector<int> range_z = mapUnit["range_z"].get<std::vector<int>>();

        DEBUG_PRINT("ID: %d", id);
        DEBUG_PRINT("Map: %d", map);
        DEBUG_PRINT("Code: %s", code.c_str());
        DEBUG_PRINT("Name: %s", name.c_str());


        DEBUG_PRINT("Range X: [%d, %d]", range_x[0], range_x[1]);
        DEBUG_PRINT("Range Y: [%d, %d]", range_y[0], range_y[1]);
        DEBUG_PRINT("Range Z: [%d, %d]", range_z[0], range_z[1]);

        for (const auto& point : mapUnit["points"]) {
            std::string pointName = point["name"];
            std::string category = point["category"];
            int x = point["x"];
            int y = point["y"];
            int z = point["z"];

            DEBUG_PRINT("  Point Name: %s", pointName.c_str());
            DEBUG_PRINT("  Category: %s", category.c_str());
            DEBUG_PRINT("  Coordinates: (%d, %d, %d)", x, y, z);
        }

        DEBUG_PRINT("----------------------");
    }

    return true;

}




void BmMapMgr::updateCurrentMap(int mapId, double X, double Y, double Z)
{
    for (const auto& mapUnit : *mapJsonData.get()) {
        int id = mapUnit["id"];
        int map = mapUnit["map"];
        if(map != mapId)
            continue;

        std::vector<int> range_x = mapUnit["range_x"].get<std::vector<int>>();
        std::vector<int> range_y = mapUnit["range_y"].get<std::vector<int>>();
        std::vector<int> range_z = mapUnit["range_z"].get<std::vector<int>>();

        if(!(range_x[0] <= X && range_x[1] >= X && range_y[0] <= Y && range_y[1] >= Y && range_z[0] <= Z && range_z[1] > Z)) {
            continue;
        }

        DEBUG_PRINT("map updated successful, id: %d", mapId);
        currentLevelStorge.clear();

        std::string code = mapUnit["code"];
        std::string name = mapUnit["name"];

        this->currentLevelName = name;

        
        DEBUG_PRINT("ID: %d", id);
        DEBUG_PRINT("Map: %d", map);
        DEBUG_PRINT("Code: %s", code.c_str());
        DEBUG_PRINT("Name: %s", name.c_str());


        DEBUG_PRINT("Range X: [%d, %d]", range_x[0], range_x[1]);
        DEBUG_PRINT("Range Y: [%d, %d]", range_y[0], range_y[1]);
        DEBUG_PRINT("Range Z: [%d, %d]", range_z[0], range_z[1]);

        for (const auto& point : mapUnit["points"]) {
            std::string pointName = point["name"];
            std::string category = point["category"];
            int x = point["x"];
            int y = point["y"];
            int z = point["z"];
            pointVector_t pointVec = {x, y, z};
            levelStorge_t levelStorge = {pointName, pointVec};

            currentLevelStorge.emplace_back(std::move(levelStorge));

            DEBUG_PRINT("  Point Name: %s", pointName.c_str());
            DEBUG_PRINT("  Category: %s", category.c_str());
            DEBUG_PRINT("  Coordinates: (%d, %d, %d)", x, y, z);
        }
        break;
    }

}
