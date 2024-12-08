#include "MapMgr/MapMgr.h"

#include <fstream>
#define DEBUG_PRINT(fmt, ...) \
            do { \
                printf("[MapMgr.cpp][%s.%d]" fmt "\r\n", __func__, __LINE__, ##__VA_ARGS__); \
            } while(0);

using json = nlohmann::json;

BmMapMgr::BmMapMgr()
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
        // 获取每个条目的 ID 和其他字段
        int id = mapUnit["id"];
        int map = mapUnit["map"];
        std::string code = mapUnit["code"];
        std::string name = mapUnit["name"];


        // 获取 range_x, range_y, range_z
        auto range_x = mapUnit["range_x"];
        auto range_y = mapUnit["range_y"];
        auto range_z = mapUnit["range_z"];

        // 输出这些数据
        DEBUG_PRINT("ID: %d", id);
        DEBUG_PRINT("Map: %d", map);
        DEBUG_PRINT("Code: %s", code.c_str());
        DEBUG_PRINT("Name: %s", name.c_str());


        DEBUG_PRINT("Range X: [%d, %d]", range_x[0], range_x[1]);
        DEBUG_PRINT("Range Y: [%d, %d]", range_y[0], range_y[1]);
        DEBUG_PRINT("Range Z: [%d, %d]", range_z[0], range_z[1]);

        // 访问每个点的信息
        for (const auto& point : mapUnit["points"]) {
            std::string pointName = point["name"];
            std::string category = point["category"];
            int x = point["x"];
            int y = point["y"];
            int z = point["z"];

            // 输出点的信息
            DEBUG_PRINT("  Point Name: %s", pointName.c_str());
            DEBUG_PRINT("  Category: %s", category.c_str());
            DEBUG_PRINT("  Coordinates: (%d, %d, %d)", x, y, z);
        }

        DEBUG_PRINT("----------------------");
    }

    return true;

}

