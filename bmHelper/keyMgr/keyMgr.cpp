
#include "KeyMgr.h"
#include <windows.h>
#include <iostream>
#include <stdio.h>

#define DEBUG_PRINT_ENABLE 1
#if DEBUG_PRINT_ENABLE
#define DEBUG_PRINT(fmt, ...) \
            do { \
                printf("[KeyMgr.cpp][%s.%d]" fmt "\r\n", __func__, __LINE__, ##__VA_ARGS__); \
            } while(0);
#else
#define DEBUG_PRINT(fmt, ...)
#endif
keyMgr::keyMgr() : listening(false)
{
    startListening();

}

keyMgr::~keyMgr()
{
    stopListening();
    if (hHook) {
        UnhookWindowsHookEx(hHook);
    }
}


LRESULT CALLBACK keyMgr::keyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
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
                auto keyBinding = it->second;
                auto newWork = std::async(std::launch::async, [keyBinding]() {
                    keyBinding->invoke();
                });
                works.emplace_back(std::move(newWork));
                
            }
        }
    }
    return CallNextHookEx(hHook, nCode, wParam, lParam);
}

void keyMgr::startListening() {

    if (!listening) {
        listening = true;
        listenerFuture = std::async(std::launch::async, [this]() {
            hHook = SetWindowsHookEx(WH_KEYBOARD_LL, keyboardProc, NULL, 0);
            if (hHook == NULL) {
                DEBUG_PRINT("KeyMgr failed to install hook, check!");
                throw std::runtime_error("Failed to install hook");
            }
            MSG msg;
            while (GetMessage(&msg, NULL, 0, 0)) {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
                
            }
        });
        DEBUG_PRINT("KeyMgr start listening.");
    }
}

void keyMgr::stopListening() {
    if (listening) {
        listening = false;
        PostThreadMessage(GetCurrentThreadId(), WM_QUIT, 0, 0);
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
        if (listenerFuture.valid()) {
            listenerFuture.get();
        }


        DEBUG_PRINT("KeyMgr stop listening.");
    }
}

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
    private:
        int insideVal;

    };
    std::shared_ptr<keyMgr> keyManager = std::make_shared<keyMgr>();
    test testClass(10086);
    keyManager->bindKeys({ VK_F1 }, std::function(test::func_0), testClass);
    keyManager->bindKeys({ VK_F2 }, std::function(test::func_1), 151, float(24841.614), 151.161165464, false);

}