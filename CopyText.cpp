// CopyText
// Created by: Alex Zhu
// Date: 2024-04-02
 
#include <Windows.h>
#include <iostream>
#include <string>

bool g_bMouseHookRunning = true;

HHOOK mouseHook = NULL;

LRESULT CALLBACK MouseHookProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode >= 0 && wParam == WM_LBUTTONDOWN) {
        MSLLHOOKSTRUCT* mouseStruct = (MSLLHOOKSTRUCT*)lParam;
        HWND targetWindow = WindowFromPoint(mouseStruct->pt);
        if (targetWindow != NULL) {
            DWORD processId;
            GetWindowThreadProcessId(targetWindow, &processId);

            HANDLE processHandle = OpenProcess(PROCESS_VM_READ, FALSE, processId);
            if (processHandle != NULL) {
                POINT clickedPoint = mouseStruct->pt;
                ScreenToClient(targetWindow, &clickedPoint);

                // Get window handles and control handles for click positions
                HWND clickedControl = ChildWindowFromPoint(targetWindow, clickedPoint);
                if (clickedControl != NULL) {
                    DWORD controlId = GetDlgCtrlID(clickedControl);
                    std::cout << "Clicked control ID: " << controlId << std::endl;

                    // Get text length in control 
                    int textLength = SendMessage(clickedControl, WM_GETTEXTLENGTH, 0, 0);
                    if (textLength > 0) {
                        char* textBuffer = new char[textLength + 1];
                        SendMessage(clickedControl, WM_GETTEXT, textLength + 1, (LPARAM)textBuffer);
                        
                        // Print text to command line window
                        std::cout << "Text in clicked control: \n\n" << textBuffer << std::endl<<std::endl;

                        // Put text into system clipboard
                        if (OpenClipboard(NULL)) {
                            EmptyClipboard();
                            HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, textLength + 1);
                            if (hMem != NULL) {
                                char* clipData = (char*)GlobalLock(hMem);
                                strcpy(clipData, textBuffer);
                                GlobalUnlock(hMem);
                                SetClipboardData(CF_TEXT, hMem);
                            }
                            CloseClipboard();
                        }

                        delete[] textBuffer;
                    }
                }

                CloseHandle(processHandle);
            }
        }
    }

    return CallNextHookEx(NULL, nCode, wParam, lParam);
}


void registerMouseHook(){
	if(g_bMouseHookRunning){
		if (mouseHook){
			UnhookWindowsHookEx(mouseHook);
			mouseHook = NULL;
		} 
		mouseHook = SetWindowsHookEx(WH_MOUSE_LL, MouseHookProc, NULL, 0);		
	} else {
		if (mouseHook){
			UnhookWindowsHookEx(mouseHook);
			mouseHook = NULL;
		}
	}
	std::cerr << "Current Mouse Capture: " << (g_bMouseHookRunning ? "ON": "OFF")<< std::endl;  
}


LRESULT CALLBACK KeyboardHookProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode >= 0 && wParam == WM_KEYDOWN) {
        KBDLLHOOKSTRUCT* kbStruct = (KBDLLHOOKSTRUCT*)lParam;
        
//        std::cout << "Get code:" << (kbStruct->vkCode) << std::endl;
        
        if (kbStruct->vkCode == VK_ESCAPE) {
            g_bMouseHookRunning = !g_bMouseHookRunning;
            registerMouseHook();          
        } else {
        	if (kbStruct->vkCode == VK_F9) {        		
        		PostQuitMessage(0);
			}
		}
        
    }
    return CallNextHookEx(NULL, nCode, wParam, lParam);
}


int main() {
	
	std::cout << "Copy Text from Other Windows. Created by Alex Zhu 2024.4.2\nUsage:\n  Escape to turn on/off mouse click exactration function.\n  F9 to exit the program.\nThe collected text also sent to clipboard! Good Luck!\n" << std::endl; 
	
	registerMouseHook();
    HHOOK keyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardHookProc, NULL, 0);

    MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    
	if(mouseHook){	
		UnhookWindowsHookEx(mouseHook);
	}
    UnhookWindowsHookEx(keyboardHook);
    
    std::cout<<"Good Bye!" << std::endl;
    return 0;
}


