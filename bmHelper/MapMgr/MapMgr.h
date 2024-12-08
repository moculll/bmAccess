#pragma once
#include <memory>
#include "json/json.hpp"

class BmMapMgr {
public:
    BmMapMgr();
    ~BmMapMgr() {}
    bool init(std::string jsonPath);

private:
    std::shared_ptr<nlohmann::json> mapJsonData;
};