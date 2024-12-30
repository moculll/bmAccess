
#include "KeyMgr.h"
#include <windows.h>
#include <iostream>
#include <stdio.h>

#define DEBUG_PRINT_ENABLE 0
#if DEBUG_PRINT_ENABLE
#define DEBUG_PRINT(fmt, ...) \
            do { \
                printf("[KeyMgr.cpp][%s.%d]" fmt "\r\n", __func__, __LINE__, ##__VA_ARGS__); \
            } while(0);
#else
#define DEBUG_PRINT(fmt, ...)
#endif
KeyMgr::KeyMgr() : listening(false), listenerThreadId(0)
{
    startListening();

}

KeyMgr::~KeyMgr()
{
    stopListening();
    if (hHook) {
        UnhookWindowsHookEx(hHook);
    }
}


LRESULT CALLBACK KeyMgr::keyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    if (nCode >= 0) {
        if (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN) {
            KBDLLHOOKSTRUCT* pKeyBoard = (KBDLLHOOKSTRUCT*)lParam;
            std::vector<int> currentKeys;

            if (GetAsyncKeyState(VK_CONTROL) & 0x8000) {
                currentKeys.push_back(VK_CONTROL);
            }
            if (GetAsyncKeyState(VK_SHIFT) & 0x8000) {
                currentKeys.push_back(VK_SHIFT);
            }
            if (GetAsyncKeyState(VK_MENU) & 0x8000) {
                currentKeys.push_back(VK_MENU);
            }
            currentKeys.push_back(pKeyBoard->vkCode);

            auto it = keyBindings.find(currentKeys);
            if (it != keyBindings.end()) {
                auto keyBindingVector = it->second;
                for (auto keyBinding : keyBindingVector) {
                    auto newWork = std::async(std::launch::async, [keyBinding]() {
                        keyBinding->invoke();
                    });
                    std::lock_guard<std::mutex> lock(KeyMgr::vecMutex);
                    works.emplace_back(std::move(newWork));
                }
                
                
            }
        }
    }
    return CallNextHookEx(hHook, nCode, wParam, lParam);
}

void KeyMgr::startListening() {

    if (!listening) {
        listening = true;
        listenerFuture = std::async(std::launch::async, [this]() {
            DEBUG_PRINT("KeyMgr start listening.");
            hHook = SetWindowsHookEx(WH_KEYBOARD_LL, keyboardProc, NULL, 0);
            if (hHook == NULL) {
                DEBUG_PRINT("KeyMgr failed to install hook, check!");
                throw std::runtime_error("Failed to install hook");
            }
            listenerThreadId = GetThreadId(GetCurrentThread());
            DEBUG_PRINT("thread id: %d", listenerThreadId);
            MSG msg;
            while (GetMessage(&msg, NULL, 0, 0)) {
                if (msg.message == WM_QUIT) {
                    DEBUG_PRINT("exit get message");
                    break;
                }
                DEBUG_PRINT("exit get message");
                TranslateMessage(&msg);
                DispatchMessage(&msg);
                
            }
        });
        

        manageFuture = std::async(std::launch::async, [this]() {
            DEBUG_PRINT("KeyMgr start managing, listening: %d", listening ? 1 : 0);
            while (listening) {
                for (auto it = works.begin(); it != works.end(); ) {
                    DEBUG_PRINT("cycle in works.");
                    if (it->wait_for(std::chrono::milliseconds(0)) == std::future_status::ready) {
                        it->get();
                        std::lock_guard<std::mutex> lock(KeyMgr::vecMutex);
                        it = works.erase(it);
                        DEBUG_PRINT("erased work.");
                    }
                    else {
                        ++it;
                    }
                }
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }
           
        });
        

    }
}

void KeyMgr::stopListening() {
    if (listening) {
        listening = false;

        while (!listenerThreadId);
        PostThreadMessage(listenerThreadId, WM_QUIT, 0, 0);
        if (listenerFuture.valid()) {
            listenerFuture.get();
        }
        if (!works.empty()) {
            for (auto &work : works) {
                if (work.valid()) {
                    work.get();
                }
            }
        }
        if (manageFuture.valid()) {
            manageFuture.get();
        }


        DEBUG_PRINT("KeyMgr stop listening.");

    }
}
/*
int main(int argc, char* argv[])
{
    class test {
    public:
        test(int src) : insideVal(src) {}
        static void func_0(test &obj)
        {
            DEBUG_PRINT("insideVal: %d", obj.insideVal);
        }
        static void func_1(int a, float b, double c, bool d)
        {
            DEBUG_PRINT("a: %d, b:%f, c:%lf, d:%d", a, b, c, d ? 1 : 0);
        }

        void func_2(const std::shared_ptr<KeyMgr>& keyManager)
        {
            keyManager->bindKeys({ VK_F3 }, std::function<void()>([this]() {
                DEBUG_PRINT("inside val: %d", insideVal);
            }));
        }

    private:
        int insideVal;

    };
    std::shared_ptr<KeyMgr> keyManager = std::make_shared<KeyMgr>();
    test testClass(10086);
    keyManager->bindKeys({ VK_F1 }, std::function(test::func_0), testClass);
    keyManager->bindKeys({ VK_F2 }, std::function(test::func_1), 151, float(24841.614), 151.161165464, false);

    testClass.func_2(keyManager);
    
    keyManager->bindKeys({ VK_F3 }, std::function<void()>([]() {
        DEBUG_PRINT("outside val: %d", 1);
    }));
    while (1);
}
*/