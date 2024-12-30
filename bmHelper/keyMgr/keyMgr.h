#pragma once
#include <vector>
#include <iostream>
#include <vector>
#include <map>
#include <functional>
#include <future>
#include <memory>
#include <tuple>
#include <windows.h>
#include <mutex>

class KeyBindingBase {
public:
    KeyBindingBase () {}
    ~KeyBindingBase() {}
    virtual void invoke() = 0;
};

template <typename... Args>
class KeyBindingWrapper : public KeyBindingBase {
public:
    std::function<void(Args ...)> callback;
    std::tuple<Args...> args;

    KeyBindingWrapper(std::function<void(Args ...)> srcFunc, Args&&... srcArgs) : callback(std::move(srcFunc)), args(std::forward<Args>(srcArgs)...) {}
    inline void invoke() override
    {
        std::apply(callback, args);
    }
};



class KeyMgr {
public:
    KeyMgr();
    ~KeyMgr();
    template <typename... Args>
    inline void bindKeys(const std::vector<int>& keys, std::function<void(Args...)> func, Args&&... args) {
        std::lock_guard<std::mutex> lock(vecMutex);
        auto newKeyWrapper = std::make_shared<KeyBindingWrapper<Args...>>(std::move(func), std::forward<Args>(args)...);
        keyBindings[keys].emplace_back(std::static_pointer_cast<KeyBindingBase>(newKeyWrapper));
    }

    inline static std::mutex vecMutex;
private:


    static LRESULT CALLBACK keyboardProc(int nCode, WPARAM wParam, LPARAM lParam);
    void startListening();
    void stopListening();

    inline static HHOOK hHook = NULL;
    inline static std::map<std::vector<int>, std::vector<std::shared_ptr<KeyBindingBase>>> keyBindings;
    bool listening;
    std::future<void> listenerFuture;
    DWORD listenerThreadId;
    std::future<void> manageFuture;
    
    inline static std::vector<std::future<void>> works; 
};