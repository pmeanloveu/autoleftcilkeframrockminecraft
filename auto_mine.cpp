#include <windows.h>
#include <iostream>

#define MY_HOTKEY_ID 1

bool is_running = false;
void startprogramaction() {
    std::cout << "Program started\n";
                    INPUT inputdown = {};
                inputdown.type = INPUT_MOUSE;
                inputdown.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
                SendInput(1, &inputdown, sizeof(INPUT));
}

void stopprogramaction() {
    std::cout << "Program stop\n";
                    INPUT inputup = {};
                inputup.type = INPUT_MOUSE;
                inputup.mi.dwFlags = MOUSEEVENTF_LEFTUP;
                SendInput(1, &inputup, sizeof(INPUT));
}

int main() {
    if (RegisterHotKey(NULL, MY_HOTKEY_ID, MOD_ALT | MOD_NOREPEAT, 'K')) {
        std::cout << "Hotkey registered (Alt+K). made by pmeanl\n";
    } else {
        std::cerr << "Failed to register Hotkey.\n";
        return 1;
    }

    MSG msg = {0};
    while (GetMessage(&msg, NULL, 0, 0) != 0) {
        if (msg.message == WM_HOTKEY && msg.wParam == MY_HOTKEY_ID) {

             if (!is_running) {

                startprogramaction();
                is_running = true;
            } else {

                stopprogramaction();
                is_running = false;
            }
        }
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    UnregisterHotKey(NULL, MY_HOTKEY_ID);
    return 0;
}

