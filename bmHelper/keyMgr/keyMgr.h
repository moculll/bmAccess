#pragma once
#include <vector>
#include <iostream>
#include <vector>
#include <map>
#include <functional>
#include <future>
#include <memory>

#include <windows.h>
struct KeyBinding {
    std::function<void(void*)> func;
    void* arg;
};
class keyMgr {
public:
    keyMgr();
    ~keyMgr();
    void bindKeys(const std::vector<int>& keys, const std::function<void(void*)>& func, void* arg);
private:
    

    static LRESULT CALLBACK keyboardProc(int nCode, WPARAM wParam, LPARAM lParam);
    void startListening();
    void stopListening();

    inline static HHOOK hHook = NULL;
    inline static std::map<std::vector<int>, KeyBinding> keyBindings;
    bool listening;
    std::future<void> listenerFuture;
};