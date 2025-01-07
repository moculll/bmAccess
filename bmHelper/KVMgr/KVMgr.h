#pragma once
#include "json/json.hpp"

class KVMgr {
public:
    KVMgr() {}

    std::string get(std::string group, std::string key)
    {
        auto it = kvStorge.find(group);
        if (it == kvStorge.end()) {
            return "";
        }
        auto itd = kvStorge[group].find(key);
        if (itd == kvStorge[group].end())
            return "";
        return kvStorge[group][key];
    }

    bool updateStorge()
    {
        if (!kvJsonData)
            return false;
        if (kvJsonData->is_object()) {
            for (auto it = kvJsonData->begin(); it != kvJsonData->end(); ++it) {
                std::map<std::string, std::string> newKV;
                if (it.value().is_object()) {
                    for (auto itv = it.value().begin(); itv != it.value().end(); ++itv) {
                        if (itv.value().is_string()) {
                            newKV[itv.key()] = std::move(itv.value().get<std::string>());
                        }
                        else {
                            newKV[itv.key()] = std::move(itv.value().dump());
                        }

                    }
                }
                kvStorge[it.key()] = std::move(newKV);

            }
        }


        return kvStorge.size() ? true : false;
    }

    bool init(std::string jsonPath);

    static std::string transfer(const std::string& input, const std::vector<std::string>& replacements, const std::string keyCode = "%%") {
        std::string result = input;
        size_t pos = 0;
        int index = 1;
        while ((pos = result.find(keyCode + std::to_string(index), pos)) != std::string::npos) {
            if (index - 1 < replacements.size()) {
                result.replace(pos, 2 + std::to_string(index).length(), replacements[index - 1]);
                pos += replacements[index - 1].length();
            }
            index++;
        }

        return result;
    }

    void debug_print();

    static void testFunc();
private:
    std::shared_ptr<nlohmann::json> kvJsonData;
    std::map<std::string, std::map<std::string, std::string>> kvStorge;
};