// MouseHook.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <Windows.h>
#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <conio.h>

LRESULT CALLBACK MouseHookProg(int nCode, WPARAM wparam, LPARAM lparam);
void keepRunning();

HHOOK mouseHook;
HACCEL hAccelTable;
UINT_PTR timer;

int main() {
	std::cout << "Trying to hook the mouse" << std::endl;
	mouseHook = SetWindowsHookEx(WH_MOUSE_LL, MouseHookProg, GetModuleHandle(NULL), 0);
	if (mouseHook == NULL)
		std::cout << "Hook Error! Couldn't hook the mouse" << std::endl;
	else {
		std::cout << "The mouse was hooked" << std::endl;
		timer = SetTimer(NULL, 333, 15000, NULL);
		MSG msg;
		while (GetMessage(&msg, nullptr, 0, 0) > 0)
		{
			if (msg.message == WM_TIMER && msg.wParam == timer)
				break;
			if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		std::cout << "Timeout! The hook was removed" << std::endl;
		UnhookWindowsHookEx(mouseHook);
	}

	return 0;
}

LRESULT CALLBACK MouseHookProg(int nCode, WPARAM wparam, LPARAM lparam) {
	PKBDLLHOOKSTRUCT k = (PKBDLLHOOKSTRUCT)(lparam);
	POINT p;
	if (wparam == WM_RBUTTONDOWN) {
		GetCursorPos(&p);
		std::cout << "Right mouse button clicked at position: ";
		std::cout << p.x;
		std::cout << ", ";
		std::cout << p.y << std::endl;
		KillTimer(NULL, 333);
		timer = SetTimer(NULL, 333, 15000, NULL);
	}
	else if (wparam == WM_LBUTTONDOWN) {
		GetCursorPos(&p);
		std::cout << "Left mouse button clicked at position: ";
		std::cout << p.x;
		std::cout << ", ";
		std::cout << p.y << std::endl;
		KillTimer(NULL, 333);
		timer = SetTimer(NULL, 333, 15000, NULL);
	}
	return CallNextHookEx(mouseHook, nCode, wparam, lparam);
}

void keepRunning() {
	while (_getch() != 27) {}
}

