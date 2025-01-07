#include "KVMgr/KVMgr.h"
#include <Windows.h>
#include <fstream>
#define DEBUG_PRINT_ENABLE 1
#if DEBUG_PRINT_ENABLE
#define DEBUG_PRINT(fmt, ...) \
            do { \
                printf("[KVMgr.cpp][%s.%d]" fmt "\r\n", __func__, __LINE__, ##__VA_ARGS__); \
            } while(0);
#else
#define DEBUG_PRINT(fmt, ...)
#endif
void KVMgr::testFunc()
{
    SetConsoleOutputCP(CP_UTF8);

    std::shared_ptr<KVMgr> kvmgr = std::make_shared<KVMgr>();
    kvmgr->init("test.json");
    kvmgr->debug_print();
    std::vector<std::string> replacements = { "Ctrl", "Alt", "Del", "Esc", "F4" };
    DEBUG_PRINT("get value: %s", kvmgr->get("test1", "initTips").c_str());
    std::string replacedTips = KVMgr::transfer(kvmgr->get("test1", "initTips").c_str(), replacements, "%%");
    DEBUG_PRINT("replacedTips: %s", replacedTips.c_str());
    system("pause");
}

bool KVMgr::init(std::string jsonPath)
{
    kvJsonData = std::make_shared<nlohmann::json>();

    std::ifstream file(jsonPath);
    if (!file.is_open()) {
        DEBUG_PRINT("Failed to open file: %s", jsonPath.c_str());
        return false;
    }

    try {
        file >> *kvJsonData.get();
    }
    catch (nlohmann::json::parse_error& err) {
        DEBUG_PRINT("JSON parsing error: %s", err.what());
        return false;
    }



    return updateStorge();
}

void KVMgr::debug_print()
{
    for (auto const& it : kvStorge) {
        for (auto const& itd : it.second) {
            DEBUG_PRINT("key: %s, value: %s", itd.first.c_str(), itd.second.c_str());

        }
    }
}