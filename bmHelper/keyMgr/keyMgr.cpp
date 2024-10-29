
#include "keyMgr.h"
#include <windows.h>
#include <iostream>
#include <stdio.h>


keyMgr::keyMgr() : listening(false)
{

    hHook = SetWindowsHookEx(WH_KEYBOARD_LL, keyboardProc, NULL, 0);
    if (hHook == NULL) {
        std::cerr << "Failed to install hook!" << std::endl;
        throw std::runtime_error("Failed to install hook");
    }
    startListening();
}

keyMgr::~keyMgr()
{
    stopListening();
    if (hHook) {
        UnhookWindowsHookEx(hHook);
    }
}

void keyMgr::bindKeys(const std::vector<int>& keys, const std::function<void(void*)>& func, void* arg)
{
    keyBindings[keys] = { func, arg };
}


LRESULT CALLBACK keyMgr::keyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    if (nCode >= 0) {
        if (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN) {
            KBDLLHOOKSTRUCT* pKeyBoard = (KBDLLHOOKSTRUCT*)lParam;
            std::vector<int> currentKeys;

            // 获取当前按下的所有修饰键
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

            // 查找并执行绑定的组合键处理函数
            auto it = keyBindings.find(currentKeys);
            if (it != keyBindings.end()) {
                const auto& keyBinding = it->second;
                keyBinding.func(keyBinding.arg);
            }
        }
    }
    return CallNextHookEx(hHook, nCode, wParam, lParam);
}

void keyMgr::startListening() {
   
    if (!listening) {
        listening = true;
        listenerFuture = std::async(std::launch::async, []() {
            MSG msg;
            while (GetMessage(&msg, NULL, 0, 0)) {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        });
    }
}

void keyMgr::stopListening() {
    if (listening) {
        listening = false;
        PostThreadMessage(GetCurrentThreadId(), WM_QUIT, 0, 0);
        if (listenerFuture.valid()) {
            listenerFuture.get();
        }
        printf("stop key");
    }
}